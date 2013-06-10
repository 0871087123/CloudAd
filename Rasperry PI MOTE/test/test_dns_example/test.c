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
#include <arpa/inet.h>

#ifdef __cplusplus
}
#endif

int main(int argc, char *argv[])
{
	struct hostent *host;
	char addr[30];
	int i;
	if (2 != argc)
	{
		printf("Param Error!\n");
		return -1;
	}

	host = gethostbyname(argv[1]);

	for (i = 0; host->h_addr_list[i] != NULL; i++)
	{
	inet_ntop(AF_INET, host->h_addr_list[i], addr, sizeof(addr));
	printf("%s\n", addr);
	}

	return 0;
}
