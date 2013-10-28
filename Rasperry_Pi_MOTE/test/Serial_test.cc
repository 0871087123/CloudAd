/*********************************************************
*	File Name   : Serial_test.cc
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月28日 星期一 17时12分00秒
*	Description : 串口模块测试
*	              连接arduino后，对应1602lcd的显示进行测试
**********************************************************/
/* 系统头文件 */
#include <gtest/gtest.h>
#include <stdio.h>

/* 自有头文件 */
#include "../basetype.h"
#include "../Serial.h"
#include "../log.h"

/*********************************************************
*	Test ID     : serial_001
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月28日 星期一 17时16分13秒
*	Description : 正常对1602LCD进行数值写入并显示。
*	              
**********************************************************/
TEST(serial, 001)
{
	char data[MAX_DATALEN] = "test info";
	arduino_lcd *mylcd = new arduino_lcd("/dev/ttyACM0");
	logserver mylog("null", false);
	char check = 0;
	mylcd->post(9, data);
	using namespace std;
	cout << "Watch your 1602LCD and make sure it displays \"test info\" " << endl;
	cout << "Then press Y/N" << endl;
	check = getchar();
	EXPECT_TRUE(('Y' == check) || ('y' == check));
	getchar();
}
