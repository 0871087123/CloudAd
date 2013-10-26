/*********************************************************
*	File Name   : main_test.cc
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月26日 星期六 19时52分30秒
*	Description : 服务器测试启动之后运行综合测试。
*	              启动指令需加入-debug
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
#include "../include/basetype.h"

/* 定义服务器ip地址 */
#define SERVERADDR "192.168.0.102"

/*********************************************************
*	Test ID     : main_test_001
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月26日 星期六 19时57分05秒
*	Description : 单客户端单进程连接
*	              
**********************************************************/
TEST(main_test, 001)
{
	int ret = -1;
	pid_t serv = 0;
	int sockfd1 = -1;
	char buf1[MAX_DATALEN] = {0};
	struct sockaddr_in serveradd;

	/* 单客户端连接并操作 */
	serveradd.sin_family = AF_INET;
	serveradd.sin_port = htons(AD_PORT);
	ret = inet_pton(AF_INET, SERVERADDR, &(serveradd.sin_addr));
	EXPECT_EQ(1, ret);
	sockfd1 = socket(AF_INET, SOCK_STREAM, 0);
	EXPECT_TRUE(0 <= sockfd1);
	ASSERT_TRUE(0 == connect(sockfd1, (struct sockaddr *)&serveradd, sizeof(sockaddr)));
	EXPECT_TRUE(0 < write(sockfd1, "GET", 4));
	EXPECT_TRUE(0 < read(sockfd1, buf1, MAX_DATALEN));
	EXPECT_TRUE(0 == strncmp(buf1, "test info", 9));
	close(sockfd1);
	
}

/*********************************************************
*	Test ID     : main_test_002
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月26日 星期六 19时59分26秒
*	Description : 多客户端并行连接
*	              
**********************************************************/
TEST(main_test, 002)
{
	int ret = -1;
	pid_t serv = 0;
	int sockfd1 = -1;
	char buf1[MAX_DATALEN] = {0};
	struct sockaddr_in serveradd;

	serv = fork();

	if (0 == serv)
	{
		/* 单客户端连接并操作 */
		serveradd.sin_family = AF_INET;
		serveradd.sin_port = htons(AD_PORT);
		ret = inet_pton(AF_INET, SERVERADDR, &(serveradd.sin_addr));
		EXPECT_EQ(1, ret);
		sockfd1 = socket(AF_INET, SOCK_STREAM, 0);
		EXPECT_TRUE(0 <= sockfd1);
		ASSERT_TRUE(0 == connect(sockfd1, (struct sockaddr *)&serveradd, sizeof(sockaddr)));
		EXPECT_TRUE(0 < write(sockfd1, "GET", 4));
		EXPECT_TRUE(0 < read(sockfd1, buf1, MAX_DATALEN));
		EXPECT_TRUE(0 == strncmp(buf1, "test info", 9));
		close(sockfd1);
		exit(0);
	}
	else
	{
		/* 单客户端连接并操作 */
		serveradd.sin_family = AF_INET;
		serveradd.sin_port = htons(AD_PORT);
		ret = inet_pton(AF_INET, SERVERADDR, &(serveradd.sin_addr));
		EXPECT_EQ(1, ret);
		sockfd1 = socket(AF_INET, SOCK_STREAM, 0);
		EXPECT_TRUE(0 <= sockfd1);
		ASSERT_TRUE(0 == connect(sockfd1, (struct sockaddr *)&serveradd, sizeof(sockaddr)));
		EXPECT_TRUE(0 < write(sockfd1, "GET", 4));
		EXPECT_TRUE(0 < read(sockfd1, buf1, MAX_DATALEN));
		EXPECT_TRUE(0 == strncmp(buf1, "test info", 9));
		close(sockfd1);
	}
}

/*********************************************************
*	Test ID     : main_test_003
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月26日 星期六 20时03分36秒
*	Description : 多路客户端接入过程中出现客户端错误退出的情况
*	              
**********************************************************/
TEST(main_test, 003)
{
	int ret = -1;
	pid_t serv = 0;
	int sockfd1 = -1;
	char buf1[MAX_DATALEN] = {0};
	struct sockaddr_in serveradd;


	/* 主进程中创建客户端进行操作 */
	/* 等待服务器启动，估计需要时间10秒 */
	sleep(5);

	/* 单客户端连接并操作 */
	serveradd.sin_family = AF_INET;
	serveradd.sin_port = htons(AD_PORT);
	ret = inet_pton(AF_INET, SERVERADDR, &(serveradd.sin_addr));
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
	ret = inet_pton(AF_INET, SERVERADDR, &(serveradd.sin_addr));
	EXPECT_EQ(1, ret);
	sockfd1 = socket(AF_INET, SOCK_STREAM, 0);
	EXPECT_TRUE(0 <= sockfd1);
	ASSERT_TRUE(0 == connect(sockfd1, (struct sockaddr *)&serveradd, sizeof(sockaddr)));
	EXPECT_TRUE(0 < write(sockfd1, "GET", 4));
	EXPECT_TRUE(0 < read(sockfd1, buf1, MAX_DATALEN));
	EXPECT_TRUE(0 == strncmp(buf1, "test info", 9));
	close(sockfd1);
}
