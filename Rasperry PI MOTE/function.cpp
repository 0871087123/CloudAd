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
*	              in raspberry pi mod
**********************************************************/
using namespace std;
deamon::deamon()
{
	memset(this->advertise, 0, ADSIZE);
	this->ad_len = 0;
	this->connector = new rasp_connector();

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
	delete this->connector;
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
				if (0 == this->AD_down(flag_print, (char *)this->advertise))
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
	result = connector->exchange("kent.skyteacher.net", this->advertise, sizeof(this->advertise));

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

/*********************************************************
*	Func Name   : deamon::AD_down
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年08月18日 星期日 14时05分09秒
*	Description : push words to the ardrino
*	              
**********************************************************/
unsigned int deamon::AD_down(AD_flag flag, char *data)
{
	ar_serial *port = new ar_serial("");
	unsigned int post_len = 0;

	if (0 == this->ad_len)
	{
		return 0;
	}	
	post_len = port->post(this->ad_len, (char *)data);
	if (this->ad_len != post_len)
		return 0;
	else
		return post_len;
}
