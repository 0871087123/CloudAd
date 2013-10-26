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
#include <sys/wait.h>
#include <arpa/inet.h>
#include <stdlib.h>

/* 自有头文件 */
#include "stub/stub.h"
#include "../include/basetype.h"
#include "../include/log.h"
#include "../include/stream.h"

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
		sleep(5);

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
		EXPECT_TRUE(0 == strncmp(buf1, "test info", 9));
		close(sockfd1);

		/* 多路并行 */
		memset(buf1, 0, sizeof(buf1));
		memset(buf2, 0, sizeof(buf2));
		sockfd1 = socket(AF_INET, SOCK_STREAM, 0);
		sockfd2 = socket(AF_INET, SOCK_STREAM, 0);
		EXPECT_TRUE(0 <= sockfd1);
		EXPECT_TRUE(0 <= sockfd2);
		ASSERT_TRUE(0 == connect(sockfd1, (struct sockaddr *)&serveradd, sizeof(sockaddr)));
		ASSERT_TRUE(0 == connect(sockfd2, (struct sockaddr *)&serveradd, sizeof(sockaddr)));
		EXPECT_TRUE(0 < write(sockfd1, "GET", 4));
		EXPECT_TRUE(0 < read(sockfd1, buf1, MAX_DATALEN));
		EXPECT_TRUE(0 < write(sockfd2, "GET", 4));
		EXPECT_TRUE(0 < read(sockfd2, buf2, MAX_DATALEN));
		EXPECT_TRUE(0 == strncmp(buf1, "test info", 9));
		EXPECT_TRUE(0 == strncmp(buf2, "test info", 9));
		close(sockfd1);
		close(sockfd2);

		EXPECT_TRUE(0 == kill(serv, 63));
		EXPECT_TRUE(serv == wait(&ret));
	}
}


/*********************************************************
*	Test ID     : stream_manager_002
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月26日 星期六 14时54分46秒
*	Description : 正常工作中出现客户端异常退出
*	              
**********************************************************/
TEST(stream_manager, 002)
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
		sleep(5);

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
		EXPECT_TRUE(0 == strncmp(buf1, "test info", 9));
		close(sockfd1);

		/* 异常退出 */
		memset(buf1, 0, sizeof(buf1));
		sockfd1 = socket(AF_INET, SOCK_STREAM, 0);
		EXPECT_TRUE(0 <= sockfd1);
		ASSERT_TRUE(0 == connect(sockfd1, (struct sockaddr *)&serveradd, sizeof(sockaddr)));
		EXPECT_TRUE(0 < write(sockfd1, "GET", 4));
		close(sockfd1);

		/* 再次连接操作 */
		serveradd.sin_family = AF_INET;
		serveradd.sin_port = htons(AD_PORT);
		ret = inet_pton(AF_INET, "127.0.0.1", &(serveradd.sin_addr));
		EXPECT_EQ(1, ret);
		sockfd1 = socket(AF_INET, SOCK_STREAM, 0);
		EXPECT_TRUE(0 <= sockfd1);
		ASSERT_TRUE(0 == connect(sockfd1, (struct sockaddr *)&serveradd, sizeof(sockaddr)));
		EXPECT_TRUE(0 < write(sockfd1, "GET", 4));
		EXPECT_TRUE(0 < read(sockfd1, buf1, MAX_DATALEN));
		EXPECT_TRUE(0 == strncmp(buf1, "test info", 9));
		close(sockfd1);

		EXPECT_TRUE(0 == kill(serv, 63));
		EXPECT_TRUE(serv == wait(&ret));
	}
}
