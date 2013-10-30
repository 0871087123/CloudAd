#include "global.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <error.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int set_Parity(int fd)
{ 
	struct termios options; 
	tcgetattr(fd, &options);
	options.c_cflag &= ~CSIZE;

	options.c_cflag |= CS8;

	options.c_cflag &= ~PARENB; 
	options.c_iflag &= ~INPCK; 

	options.c_cflag &= ~CSTOPB;

	options.c_cc[VTIME] = 150; /* 设置超时15 seconds*/   
	options.c_cc[VMIN] = 0; /* Update the options and do it NOW */
	

	/*set boad rates*/
	cfsetispeed(&options, B9600);
	cfsetospeed(&options, B9600);

	tcflush(fd, TCIFLUSH);
	if (tcsetattr(fd,TCSANOW,&options) != 0)   
	{ 
		perror("SetupSerial");   
		return (FALSE);  
	} 
	return (TRUE);  
}

int main()
{
	int fd;
	fd = open("/dev/ttyACM0",O_RDWR);
	if (fd < 0)
	{
		perror("No Such Port\n");
	}

	int ret;
	ret = set_Parity(fd);
	if (ret <= 0)
	{
		perror("set boad rates");
		return 0;
	}

	char buf[20]={0};
	tcflush(fd,TCIFLUSH);
	getchar();
	ret = write(fd, "c", 1);
	ret += write(fd, "\"\n", 2);
	if (ret <= 0)
		perror("echo serial");
	buf[18] = '\n';
	buf[19] = '\0';
	write(1, buf, 20);
	close(fd);
	printf("Succes! %d\n",ret);
}
