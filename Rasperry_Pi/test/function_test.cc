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
#include "../log.h"

/* Need to be set to c */
extern "C" {
#include "stub/stub.h"
}

/* stub function declare */

/*********************************************************
*	Test ID     : deamon_001
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年09月01日 星期日 15时00分13秒
*	Description : 测试主循环控制器正常开始。
*	              
**********************************************************/
TEST(deamon_normal, 001)
{
	char check = 0;
	logserver mylog("null", false);
	deamon *myserver = new deamon(10, "/dev/ttyACM0", "kent.skyteacher.net");
	using namespace std;
	cout << "Make sure \n\tloop tim = 10 \n\tserial port = ttyACM0, \n\tserver name = kent.skyteacher.net." << endl;
	cout << "Then press Y/N to check this test" << endl;
	check = getchar();
	EXPECT_TRUE(('Y' == check) || ('y' == check));
	getchar();
}
