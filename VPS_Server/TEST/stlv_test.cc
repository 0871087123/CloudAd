#include <gtest/gtest.h>
#include <arpa/inet.h>
#include <string.h>
#include "../include/stlv.h"

/*********************************************************
*	Test ID     : stlv_set_001
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月22日 星期二 22时18分14秒
*	Description : TLV包正常封装测试
*	              
**********************************************************/
TEST(stlv_set, 001)
{
	int ret = 0;

	/* 定义包 */
	char data[STLV_BUF_LEN_MIN];
	char buf[STLV_BUF_LEN_MIN + 10];
	STLV pack;
	
	/* 数据初始化 */
	memset(data, 0, STLV_BUF_LEN_MIN);
	memset(buf, 0, sizeof(buf));

	pack.data = data;
	pack.len = 10;
	pack.type = 12;
	strcpy(data, "aaaaaaaaa");

	ret = stlv_set(buf, STLV_BUF_LEN_MIN + 10, &pack);

	EXPECT_TRUE(14 == ret);
	EXPECT_TRUE(0 == strcmp(buf + 4, "aaaaaaaaa"));
	EXPECT_EQ(htons(12), *(unsigned short *)buf);
	EXPECT_EQ(htons(10), *(unsigned short *)(buf + 2));
}

/*********************************************************
*	Test ID     : stlv_set_002
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月22日 星期二 22时38分12秒
*	Description : 数据包buf不够长度
*	              
**********************************************************/
TEST(stlv_set, 002)
{
	int ret = 0;

	/* 定义包 */
	char data[STLV_BUF_LEN_MIN];
	char buf[STLV_BUF_LEN_MIN + 10];
	STLV pack;
	
	/* 数据初始化 */
	memset(data, 0, STLV_BUF_LEN_MIN);
	memset(buf, 0, sizeof(buf));

	pack.data = data;
	pack.len = 100 + STLV_BUF_LEN_MIN;
	pack.type = 12;
	strcpy(data, "aaaaaaaaa");

	ret = stlv_set(buf, STLV_BUF_LEN_MIN + 10, &pack);

	EXPECT_TRUE(-1 == ret);
	EXPECT_EQ(0, *(unsigned short *)buf);
	EXPECT_EQ(0, *(unsigned short *)(buf + 2));
	EXPECT_EQ(0, *(unsigned short *)(buf + 12));
}

/*********************************************************
*	Test ID     : stlv_get_001
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月22日 星期二 22时40分30秒
*	Description : 正常解包测试
*	              
**********************************************************/
TEST(stlv_get, 001)
{
	int ret = 0;

	/* 定义包 */
	char data[STLV_BUF_LEN_MIN];
	char buf[STLV_BUF_LEN_MIN + 10];
	STLV pack;
	
	/* 数据初始化 */
	memset(data, 0, STLV_BUF_LEN_MIN);
	memset(buf, 0, sizeof(buf));

	pack.data = data;
	pack.len = 10;
	pack.type = 12;
	strcpy(data, "aaaaaaaaa");

	ret = stlv_set(buf, STLV_BUF_LEN_MIN + 10, &pack);

	EXPECT_TRUE(14 == ret);
	EXPECT_TRUE(0 == strcmp(buf + 4, "aaaaaaaaa"));
	EXPECT_EQ(htons(12), *(unsigned short *)buf);
	EXPECT_EQ(htons(10), *(unsigned short *)(buf + 2));

	memset(&pack, 0, sizeof(pack));
	pack.data = data;
	ret = stlv_get(&pack, sizeof(data), buf, ret);
	EXPECT_EQ(10, ret);
	EXPECT_EQ(12, pack.type);
	EXPECT_EQ(10, pack.len);
	EXPECT_TRUE(0 == strcmp((char *)pack.data, "aaaaaaaaa"));
}

/*********************************************************
*	Test ID     : stlv_get_002
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月22日 星期二 22时52分24秒
*	Description : 缓冲区长度不够的测试
*	              
**********************************************************/
TEST(stlv_get, 002)
{
	int ret = 0;

	/* 定义包 */
	char data[STLV_BUF_LEN_MIN];
	char buf[STLV_BUF_LEN_MIN + 10];
	STLV pack;
	
	/* 数据初始化 */
	memset(data, 0, STLV_BUF_LEN_MIN);
	memset(buf, 0, sizeof(buf));

	pack.data = data;
	pack.len = 10;
	pack.type = 12;
	strcpy(data, "aaaaaaaaa");

	ret = stlv_set(buf, STLV_BUF_LEN_MIN + 10, &pack);

	EXPECT_TRUE(14 == ret);
	EXPECT_TRUE(0 == strcmp(buf + 4, "aaaaaaaaa"));
	EXPECT_EQ(htons(12), *(unsigned short *)buf);
	EXPECT_EQ(htons(10), *(unsigned short *)(buf + 2));

	memset(&pack, 0, sizeof(pack));
	memset(data, 0, sizeof(data));
	pack.data = data;
	ret = stlv_get(&pack, 7, buf, ret);
	EXPECT_EQ(-1, ret);
	EXPECT_EQ(0, pack.type);
	EXPECT_EQ(0, pack.len);
	EXPECT_EQ(0, ((char *)pack.data)[0]);
	EXPECT_EQ(0, ((char *)pack.data)[6]);
}

/*********************************************************
*	Test ID     : stlv_get_003
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月22日 星期二 22时56分01秒
*	Description : 非法包的测试(接收数据包不全的测试)
*	              
**********************************************************/
TEST(stlv_get, 003)
{
	int ret = 0;

	/* 定义包 */
	char data[STLV_BUF_LEN_MIN];
	char buf[STLV_BUF_LEN_MIN + 10];
	STLV pack;
	
	/* 数据初始化 */
	memset(data, 0, STLV_BUF_LEN_MIN);
	memset(buf, 0, sizeof(buf));

	pack.data = data;
	pack.len = 10;
	pack.type = 12;
	strcpy(data, "aaaaaaaaa");

	ret = stlv_set(buf, STLV_BUF_LEN_MIN + 10, &pack);

	EXPECT_TRUE(14 == ret);
	EXPECT_TRUE(0 == strcmp(buf + 4, "aaaaaaaaa"));
	EXPECT_EQ(htons(12), *(unsigned short *)buf);
	EXPECT_EQ(htons(10), *(unsigned short *)(buf + 2));

	memset(&pack, 0, sizeof(pack));
	memset(data, 0, sizeof(data));
	pack.data = data;
	ret = stlv_get(&pack, 7, buf, ret - 2);
	EXPECT_EQ(-1, ret);
	EXPECT_EQ(0, pack.type);
	EXPECT_EQ(0, pack.len);
	EXPECT_EQ(0, ((char *)pack.data)[0]);
	EXPECT_EQ(0, ((char *)pack.data)[6]);
}
