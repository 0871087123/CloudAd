/*********************************************************
*	File Name   : stream_test.cc
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月25日 星期五 15时46分06秒
*	Description : 简单测试流控制器
*	              
**********************************************************/
/* 系统头文件 */
#include <gtest/gtest.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

/* 自有头文件 */
#include "stub/stub.h"
#include "../include/basetype.h"
#include "../include/log.h"
#include "../include/stream.h"

/* 桩函数需要使用的全局变量 */


/* 这里是桩函数 */


/*********************************************************
*	Func Name   : stub_pre
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月25日 星期五 15时48分25秒
*	Description : 进行所有打桩操作
*	              
**********************************************************/
void stub_pre()
{
}

/*********************************************************
*	Func Name   : stub_fin
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月25日 星期五 15时49分26秒
*	Description : 去除所有桩的痕迹
*	              
**********************************************************/
void stub_fin()
{
}

/*********************************************************
*	Test ID     : stream_manager_001
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月25日 星期五 15时54分40秒
*	Description : 正常工作测试
*	              
**********************************************************/
TEST(stream_manager, 001)
{
	int ret = -1;
	pid_t serv = 0;
	int sockfd1 = -1;
	int sockfd2 = -1;
	char buf1[MAX_DATALEN] = {0};
	char buf2[MAX_DATALEN] = {0};
	struct sockaddr_in serveradd;

	serv = fork();

	if (0 == serv)
	{
		/* 子进程中创建服务器 */
		/* 创建log */
		logserver logs("log", false);
		stream_manager io(10, 10, "./data.pub", 10);
		io.start();
		LOG("SERVER TERMINATED");
		exit(0);
	}
	else
	{
		/* 主进程中创建客户端进行操作 */
		/* 等待服务器启动，估计需要时间10秒 */
		sleep(10);

		/* 单客户端连接并操作 */
		serveradd.sin_family = AF_INET;
		serveradd.sin_port = htons(AD_PORT);
		ret = inet_pton(AF_INET, "127.0.0.1", &(serveradd.sin_addr));
		EXPECT_EQ(1, ret);
		sockfd1 = socket(AF_INET, SOCK_STREAM, 0);
		EXPECT_TRUE(0 <= sockfd1);
		ASSERT_TRUE(0 == connect(sockfd1, (struct sockaddr *)&serveradd, sizeof(sockaddr)));
		EXPECT_TRUE(0 < write(sockfd1, "GET", 4));
		EXPECT_TRUE(0 < read(sockfd1, buf1, MAX_DATALEN));
		EXPECT_TRUE(0 == strcmp(buf1, "test info"));

		EXPECT_TRUE(0 == kill(serv, 2));
	}
}
