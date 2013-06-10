#include <stream>
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#ifdef __cplusplus
}
#endif

#include "dns.h"

//init rasp_connector
void rasp_connector::rasp_connector()
{
	this->fd_sock = -1;
	this->wired = false;
	this->domainname[0] = '\0';
}

void rasp_connector::~rasp_connector()
{
	return;
}

void rasp_connector::wireto(UCHAR *hostname)
{
}


void rasp_connector::TX(UCHAR *buffer, ULONG bufsize)
{
}


void rasp_connector::RX(UCHAR *buffer, ULONG bufsize)
{
}

bool rasp_connector::exchange(CHAR *hostname, CHAR *buffer, ULONG bufsize)
{
}
