#include <gtest/gtest.h>

#include <iostream>
#include "../basetype.h"
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
#include <arpa/inet.h>

#include "stub/stub.h"

extern int connect(int sockfd,const struct sockaddr *addr, socklen_t addrlen);
#ifdef __cplusplus
}
#endif

#include "../dns.h"
#include "../log.h"

char address_p[20];
//need to be stub
int conect_t;

class UT_DNS : public ::testing::Test {
	public :
		struct fun_stub stub[10];

	protected:
		virtual void SetUp();
		virtual void TearDown();
};


int connect_stub(int sockfd, struct sockaddr *addr, socklen_t addrlen)
{
	PARAIGNORE(sockfd);
	PARAIGNORE(addrlen);
	
	conect_t += 1;
	inet_ntop(AF_INET, (void *)&((sockaddr_in *)addr)->sin_addr, address_p, 20);
	return 0;
}

void UT_DNS::SetUp()
{
	conect_t = 0;
	stub_set(&(this->stub[0]), (void *)connect, (void *)connect_stub);
	return;
}

void UT_DNS::TearDown()
{
	stub_reset(&(this->stub[0]));
	return;
}

TEST_F(UT_DNS, 001)
{
	rasp_connector myrasp;
	logserver mylog("Null", false);
	//检查初始化
	EXPECT_EQ(-1, myrasp.fd_sock);
	EXPECT_TRUE(false == myrasp.wired);

	//连接域名
	myrasp.wireto("git.skyteacher.net");

	//检查连接结果
	EXPECT_EQ(1, conect_t);
	EXPECT_EQ(0, strcmp(address_p, "192.168.0.102"));
	EXPECT_NE(-1, myrasp.fd_sock);
	EXPECT_EQ(true, myrasp.wired);
	close(myrasp.fd_sock);
}


/*********************************************************
*	Test ID     : DNS_002
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月28日 星期一 15时32分08秒
*	Description : 与已经部署完成的服务器进行搭配测试。
*	              
**********************************************************/
TEST(DNS, 002)
{
	rasp_connector myrasp;
	logserver mylog("Null", false);
	int ret = -1;
	char buf[MAX_DATALEN] = {0};
	//检查初始化
	EXPECT_EQ(-1, myrasp.fd_sock);
	EXPECT_TRUE(false == myrasp.wired);


	/* 进行数据通信测试 */
	strcpy(buf, "GET");
	ret = myrasp.exchange("kent.skyteacher.net", buf, MAX_DATALEN);
	EXPECT_TRUE(0 < ret);
	EXPECT_TRUE(0 == strncmp(buf, "test info", 9));

	return;
}
