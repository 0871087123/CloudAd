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

void rasp_connector::wireto(CHAR *hostname)
{
	struct hostent *host;
	struct sockaddr_in addr;
	struct sockaddr *sockaddr = (struct sockaddr *)&addr;
	int s_fd;

	memset(&addr, 0, sizeof(addr));

	host = gethostbyname(hostname);

	if (host->h_addrtype != AF_INET)
		return;

	if (host->h_addr_list[0] != NULL)
	{
		addr.sin_family = AF_INET;
		addr.sin_port = AD_PORT;
		addr.sin_addr.s_addr = *(host->h_addr_list[0]);
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

	if (setsockopt(s_fd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(s_fd)))
	{
		perror("sockopt:SNTO");
		return;
	}

	if (setsockopt(s_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(s_fd)))
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


void rasp_connector::TX(UCHAR *buffer, ULONG bufsize)
{
	if (true != this->wired)
		return;

	write(this->fd_sock, buffer, bufsize);

	return;
}


void rasp_connector::RX(UCHAR *buffer, ULONG bufsize)
{
	if (true != this->wired)
		return ;

	read(this->fd_sock, buffer, bufsize);

	return;
}

bool rasp_connector::exchange(CHAR *hostname, CHAR *buffer, ULONG bufsize)
{
	return true;
}
