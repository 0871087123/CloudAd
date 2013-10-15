/*********************************************************
*	File Name   : function.cpp
*	Project     : Cloud AD
*	Author      : Kent
*	Data        : 2013年08月06日 星期二 21时05分56秒
*	Description : This file contain main loop of ths deamon
*	              process
**********************************************************/
#include <iostream>
#include "basetype.h"
#include "dns.h"
#include "Serial.h"
#include "function.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>

typedef enum tagErrorNum {
	E_INVALID = 0,
	E_ACQINFO,
	E_DOWN,
	E_BUTT,
}ERRORNUM;

char *ERRORSTR[] = 
{
	"",		/* E_INVALID */
	"Can't acquire information\n",				/* E_ACQINFO */
	"Can't tranfer information to arduino",		/* E_DOWN */
	"",		/* E_BUTT */
};

/*********************************************************
*	Func Name   : deamon::deamon
*	Project     : Cloud AD
*	Author      : Kent
*	Data        : 2013年08月06日 星期二 21时04分17秒
*	Description : this function is main loop of deamon process
*	              in raspberry pi mod，输入一个参数，第一个
*	              为服务器名，第二个为本地串口路径
**********************************************************/
using namespace std;
deamon::deamon(char *arglist[])
{
	/* 数据初始化 */
	this->ad_len = 0;
	memset(this->advertise, 0, ADSIZE);
	memset(this->server_name, 0, SERVER_NAME_LEN);
	memset(this->serial_name, 0, PORTNAME_LEN);

	/* 存储配置数据 */
	strcpy(this->server_name, arglist[0]);
	strcpy(this->serial_name, arglist[1]);

	/* 创建各种连接 */
	this->connector = new rasp_connector();
	this->lcd_downloader = new arduino_lcd(arglist[1]);

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
void deamon::startdeamon()
{
	ERRORNUM error_code = E_INVALID;

	while(1){
		sleep(100);
		try {
			while (1)
			{
				if (0 == this->acquire())
				{
					throw E_ACQINFO;
				}
				if (0 == this->lcd_downloader->post(flag_print, (char *)this->advertise))
				{
					throw E_DOWN;
				}
			}
		}

		catch (ERRORNUM error_code){
			if (error_code < E_BUTT)
			{
				printf("%s : %s", "Error in process", ERRORSTR[error_code]);
			}
			else
			{
				printf("Error string load faild.\n");
			}
		}
	}

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
	strncpy((char *)this->advertise, "Get AD", sizeof(this->advertise));
	result = connector->exchange(this->server_name, this->advertise, sizeof(this->advertise));

	if (0 == result)
	{
		this->ad_len = 0;
	}
	else
	{
		this->ad_len = result;
	}

	return this->ad_len;
}

