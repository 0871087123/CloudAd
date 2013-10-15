#include <gtest/gtest.h>
#include <iostream>
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
#include <arpa/inet.h>
#include <setjmp.h>

#include "../dns.h"
#include "../Serial.h"
#include "../function.h"

/* Need to be set to c */
extern "C" {
#include "stub/stub.h"
}

/* stub function declare */
static struct fun_stub stru_stub[10] = {0};
static unsigned int cont = 0;
static char se_data[100] = "";
static jmp_buf * jmp_point = NULL;

static unsigned int stub_sleep(unsigned int seconds);
static unsigned int stub_exchange(char *hostname, unsigned char *buffer, unsigned long bufsize);
static unsigned int stub_AD_down(AD_flag flag, char *data);

/*********************************************************
*	Test ID     : deamon_001
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年09月01日 星期日 15时00分13秒
*	Description : 测试守护进程正常运行
*	              
**********************************************************/
TEST(deamon_normal, 001)
{
	bool i = false;
	int ret = 0;
	jmp_buf tmp_jump_point;
	char *arglist[2];

	arglist[0] = "work.skyteacher.net";
	arglist[1] = "/dev/null";
	memset(&tmp_jump_point, 0, sizeof(tmp_jump_point));

	cont = 1;

	deamon my_daemon(arglist);
	stub_set(&stru_stub[0], (void *)sleep, (void *)stub_sleep);
	//stub_set(&stru_stub[1], (void *)my_daemon.connector->exchange, (void *)stub_exchange);
	//stub_set(&stru_stub[2], (void *)my_daemon.AD_down, (void *)stub_AD_down);

	ret = setjmp(tmp_jump_point);
	jmp_point = &tmp_jump_point;
	if (false == i)
	{
		i = true;
		my_daemon.startdeamon();
	}
	else
	{
		EXPECT_NE(0 , ret);
		EXPECT_TRUE(0 == strncmp(se_data, "OK then", strlen("OK then")));
		EXPECT_EQ(my_daemon.ad_len, strlen("OK then"));
	}

	stub_reset(&stru_stub[0]);
	//stub_reset(&stru_stub[1]);
	//stub_reset(&stru_stub[2]);
}


/* stub function */
static unsigned int stub_sleep(unsigned int seconds)
{
	if (cont-- > 0)
	{
		return 0;
	}
	else
	{
		longjmp(*jmp_point, 0);
		return 0;
	}
}

static unsigned int stub_exchange(char *hostname, unsigned char *buffer, unsigned long bufsize)
{
	strncpy((char *)buffer, "OK then", bufsize);
	return sizeof("OK then");
}

static unsigned int stub_AD_down(AD_flag flag, char *data)
{
	strncpy(se_data, data, 100);
	return strlen(data);
}
