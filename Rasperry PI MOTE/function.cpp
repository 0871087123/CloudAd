/*********************************************************
*	File Name   : function.cpp
*	Project     : Cloud AD
*	Author      : Kent
*	Data        : 2013年08月06日 星期二 21时05分56秒
*	Description : This file contain main loop of ths deamon
*	              process
**********************************************************/
#include <iostream.h>
#include "basetype.h"
#include "dns.h"
#include "function.h"
#include <string.h>
#include <unistd.h>

typedef enum tagErrorNum {
	E_INVALID = 0,
	E_ACQINFO,
	E_BUTT,
}ERRORNUM;

CHAR *ERRORSTR[] = 
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
	this->rasp_connector = new rasp_connector();

	try {
		while (1)
		{
			if (0 != this->acquire())
			{
				throw E_ACQINFO;
			}
			if (0 != this->AD_down(flag_print, this->))
			{
				throw E_DOWN;
			}
			sleep(10);
		}
	}

	catch (ERRORNUM){
		if (ERRORNUM < E_BUTT)
		{
			printf("%s : %s", "Error in process", ERRORSTR[ERRORNUM]);
		}
		else
		{
			printf("Error string load faild.\n");
		}
	}

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
~deamon::deamon()
{
	memset(this->advertise, 0, ADSIZE);
	this->ad_len = 0;
	delete this->rasp_connector;
}


