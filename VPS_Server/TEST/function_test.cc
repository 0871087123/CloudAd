/*********************************************************
*	File Name   : function_test.cc
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月26日 星期六 18时46分58秒
*	Description : function模块UT测试
*	              
**********************************************************/
/* 系统头文件 */
#include <gtest/gtest.h>

/* 自有头文件 */
#include "stub/stub.h"
#include "../include/basetype.h"
#include "../include/log.h"
#include "../include/stream.h"
#include "../include/function.h"

/*********************************************************
*	Test ID     : server_001
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月26日 星期六 19时11分59秒
*	Description : 测试是否能正常读出配置文件
*	              
**********************************************************/
TEST(server, 001)
{
	int ret = -1;
	server *tmp = NULL;
	logserver log("null", false);
	tmp = new server("./config");
	delete(tmp);
}

/*********************************************************
*	Test ID     : server_002
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月26日 星期六 19时23分58秒
*	Description : 文件不存在的情况下直接退出
*	              
**********************************************************/
TEST(server, 002)
{
	int ret = -1;
	server *tmp = NULL;
	logserver log("null", false);
	tmp = new server("./NotExist");
	delete(tmp);
}
