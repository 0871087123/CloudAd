/*********************************************************
*	File Name   : function.cpp
*	Project     : Cloud AD
*	Author      : Kent
*	Data        : 2013年08月06日 星期二 21时05分56秒
*	Description : This file contain main loop of ths deamon
*	              process
**********************************************************/
/* 系统头文件 */
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

/* 自有头文件 */
#include "basetype.h"
#include "dns.h"
#include "Serial.h"
#include "function.h"
#include "log.h"

/*********************************************************
*	Func Name   : deamon::deamon
*	Project     : Cloud AD
*	Author      : Kent
*	Data        : 2013年08月06日 星期二 21时04分17秒
*	Description : this function is main loop of deamon process
*	              in raspberry pi mod，输入一个参数，第一个
*	              为服务器名，第二个为本地串口路径
**********************************************************/
deamon::deamon(int loop, char *serial, char *server)
{
	/* 数据初始化 */
	this->ad_len = 0;
	memset(this->advertise, 0, ADSIZE);
	memset(this->server_name, 0, SERVER_NAME_LEN);
	memset(this->serial_name, 0, PORTNAME_LEN);

	/* 存储配置数据 */
	strcpy(this->server_name, server);
	strcpy(this->serial_name, serial);
	this->loop_time = loop;

	/* 创建各种连接 */
	this->connector = new rasp_connector();
	this->lcd_downloader = new arduino_lcd(serial);

#ifdef __DEBUG__
	using namespace std;
	cout << "Loop time: " << this->loop_time << endl;
	cout << "serial port :" << this->serial_name << endl;
	cout << "Server Name :" << this->server_name << endl;
#endif

	return;
}

/*********************************************************
*	Func Name   : ~deamon::deamon
*	Project     : Cloud AD
*	Author      : Kent
*	Data        : 2013年08月06日 星期二 21时05分20秒
*	Description : this function delete reference of main loop
*	              in deamon process
**********************************************************/
deamon::~deamon()
{
	memset(this->advertise, 0, ADSIZE);
	this->ad_len = 0;
	if (NULL != this->connector)
		delete this->connector;
	if (NULL != this->lcd_downloader)
		delete this->lcd_downloader;

	return;
}

/*********************************************************
*	Func Name   : deamon::startdeamon
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年09月01日 星期日 14时57分26秒
*	Description : 启动守护进程
*	              
**********************************************************/
void deamon::start()
{
	LOG("Start Loop Processing.\n");

	while(1)
	{
		sleep(this->loop_time);
		this->acquire();
		/* 去除尾0 */
		if (0 == this->advertise[this->ad_len])
		{
			this->ad_len -= 1;
		}
		this->lcd_downloader->post(this->ad_len, (char *)this->advertise);
	}

	return;
}

/*********************************************************
*	Func Name   : deamon::acquire
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年08月18日 星期日 13时55分30秒
*	Description : pull words form server
*	              
**********************************************************/
unsigned long deamon::acquire()
{
	rasp_connector *connector = this->connector;
	unsigned int result = false;
	strncpy(this->advertise, "GET", sizeof(this->advertise));
	result = connector->exchange(this->server_name, this->advertise, sizeof(this->advertise));

	if (0 == result)
	{
		LOG("WARN : Can't get Data from server.\n");
		this->ad_len = 0;
	}
	else
	{
		LOG("Get Data from server OK.\n");
		this->ad_len = result;
	}

	return this->ad_len;
}

