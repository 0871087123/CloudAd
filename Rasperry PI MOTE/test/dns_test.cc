#include <gtest/gtest.h>

#include "../dns.h"
#include "stub/stub.h"

//stub function


class UT_DNS : public ::testing::Test {
	public :
		int conect_t;
		char addr[20];

	protected:
		virtual void SetUp();
		virtual void TearDown();
};

void UT_DNS::SetUp()
{
	this->conect_t = 0;
}

void UT_DNS::TearDown()
{
	return;
}

TEST_F(UT_DNS, 001)
{
	rasp_connector myrasp;
	//检查初始化
	EXPECT_EQ(-1, myrasp.fd_sock);
	EXPECT_EQ(false, myrasp.wired);

	//连接域名
	myrasp.wireto("www.skyteacher.net");

	//检查连接结果
	EXPECT_EQ(1, this->conect_t);
	EXPECT_EQ(0, strcmp(this->addr, "192.168.1.101"));
	EXPECT_NE(-1, myrasp.fd_sock);
	EXPECT_EQ(true, myrasp.wired);
}

//void stub_socket;
