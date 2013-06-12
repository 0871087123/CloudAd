#include <iostream>
#include "basetype.h"
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#ifdef __cplusplus
}
#endif

#include "dns.h"

STATIC struct timeval timeout;

//init rasp_connector
rasp_connector::rasp_connector()
{
	this->fd_sock = -1;
	this->wired = false;
	this->domainname[0] = '\0';

	timeout.tv_sec = 40;
	return;
}

rasp_connector::~rasp_connector()
{
	return;
}

void rasp_connector::wireto(const CHAR *hostname)
{
	struct hostent *host;
	struct sockaddr_in addr;
	struct sockaddr *sockaddr = (struct sockaddr *)&addr;
	int i = 0;
	int s_fd;

	memset(&addr, 0, sizeof(addr));

	host = gethostbyname(hostname);

	if (host->h_addrtype != AF_INET)
		return;

	while (host->h_addr_list[i] != NULL)
	i++;

	if (i > 0)
	{
		addr.sin_family = AF_INET;
		addr.sin_port = AD_PORT;
		memcpy(&(addr.sin_addr.s_addr), host->h_addr_list[i - 1], sizeof(addr.sin_addr.s_addr));
	}
	else 
	{
		//error , do nothing
		perror("HOST NAME:");
		return ;
	}

	s_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (s_fd < 0)
	{
		//error , do nothing
		perror("SOCKET:");
		return ;
	}

	if (setsockopt(s_fd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)))
	{
		perror("sockopt:SNTO");
		return;
	}

	if (setsockopt(s_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)))
	{
		perror("sockopt:RDTO");
		return;
	}

	this->fd_sock = s_fd;

	if (0 != connect(this->fd_sock, sockaddr, sizeof(sockaddr_in)))
	{
		perror("CONNECT:");
		this->fd_sock = -1;
		return;
	}

	this->wired = true;

	return;
}


ULONG rasp_connector::TX(UCHAR *buffer, ULONG bufsize)
{
	if (true != this->wired)
		return 0;

	return write(this->fd_sock, buffer, bufsize);
}


ULONG rasp_connector::RX(UCHAR *buffer, ULONG bufsize)
{
	if (true != this->wired)
		return 0;

	return read(this->fd_sock, buffer, bufsize);
}

bool rasp_connector::exchange(CHAR *hostname, UCHAR *buffer, ULONG bufsize)
{
	ULONG length;

	if (false != this->wired)
	{
		close(this->fd_sock);
	}	

	this->wireto(hostname);

	if (true != this->wired)
	{
		return false;
	}

	length = this->TX(buffer, bufsize);
	if (length <= 0)
	{
		perror("TX:");
		return false;
	}

	length = this->RX(buffer, bufsize);
	{
		perror("RX:");
		return false;
	}

	return true;
}
