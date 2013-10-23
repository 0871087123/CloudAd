/*********************************************************
*	File Name   : log_test.cc
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月23日 星期三 14时57分14秒
*	Description : log模块的UT测试
*	              
**********************************************************/
/* 公用头文件 */
#include <gtest/gtest.h>
#include <stdio.h>
#include <string.h>

/* 自有头文件 */
#include "../include/basetype.h"
#include "../include/log.h"
#include "stub/stub.h"

/* 桩函数的外部数据 */
static char logpath[FILE_NAME_LEN];
static char filemod[FILE_NAME_LEN];
static char data[200];
static char *logstr = data;
static bool logtofile = false;

/* 桩函数 */
static FILE *stub_fopen(const char *path, const char *mod)
{
	strcpy(logpath, path);
	strcpy(filemod, mod);
	logtofile = true;

	return (FILE *)0xff;
}

static int stub_fprintf(FILE *stream, const char *format, ...)
{
	strcpy(logstr, format);
	logstr += strlen(format);
	return 0;
}

static int stub_printf(const char *format, ...)
{
	strcpy(logstr, format);
	logstr += strlen(format);
	return 0;
}

static int stub_fclose(FILE *stream)
{
	return 0;
}

/*********************************************************
*	Test ID     : logserver_001
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月23日 星期三 15时06分52秒
*	Description : 打印到终端的测试
*	              
**********************************************************/
TEST(logserver, 001)
{
	int ret;
	fun_stub test[4];

	stub_set(&test[0], (void *)fopen, (void *)stub_fopen);
	stub_set(&test[1], (void *)fclose, (void *)stub_fclose);
	stub_set(&test[2], (void *)fprintf, (void *)stub_fprintf);
	stub_set(&test[3], (void *)printf, (void *)stub_printf);

	logserver *testlog = new logserver("./log", true);
	EXPECT_TRUE(0 == strcmp("./log", logpath));
	EXPECT_TRUE(0 == strcmp("a+", filemod));
	LOG("testlogserver");
	EXPECT_TRUE(0 == strcmp("testlogserver", data));
	EXPECT_TRUE(true == logtofile);
	delete testlog;

	stub_reset(&test[0]);
	stub_reset(&test[1]);
	stub_reset(&test[2]);
	stub_reset(&test[3]);
}

/*********************************************************
*	Test ID     : logserver_002
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月23日 星期三 15时15分24秒
*	Description : 打印到终端的测试
*	              
**********************************************************/
TEST(logserver, 002)
{
	/* 初始化数据 */
	fun_stub test[4];
	logtofile = false;
	logstr = data;
	memset(logpath, 0, sizeof(logpath));
	memset(filemod, 0, sizeof(filemod));
	memset(data, 0, sizeof(data));
	
	stub_set(&test[0], (void *)fopen, (void *)stub_fopen);
	stub_set(&test[1], (void *)fclose, (void *)stub_fclose);
	stub_set(&test[2], (void *)fprintf, (void *)stub_fprintf);
	stub_set(&test[3], (void *)printf, (void *)stub_printf);

	logserver *testlog = new logserver("test", false);
	LOG("testlogserver");
	EXPECT_TRUE(0 == logpath[0]);
	EXPECT_TRUE(0 == filemod[0]);
	EXPECT_TRUE(false == logtofile);
	EXPECT_TRUE(0 == strcmp("testlogserver", data));
	delete testlog;

	stub_reset(&test[0]);
	stub_reset(&test[1]);
	stub_reset(&test[2]);
	stub_reset(&test[3]);
}
