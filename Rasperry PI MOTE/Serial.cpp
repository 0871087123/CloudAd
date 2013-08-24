/*********************************************************
*	File Name   : Serial.cpp
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年08月24日 星期六 14时15分48秒
*	Description : this file realize posting advertise to 
*	              arduino
**********************************************************/
#include <unistd.h>
#include <SerialPort.h>
#include "Serial.h"

/*********************************************************
*	Func Name   : ar_serial::post
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年08月24日 星期六 14时17分28秒
*	Description : posting advertise to arduino
*	              
**********************************************************/
unsigned int ar_serial::post(int data_len, char *data)
{
	return 0;
}

/*********************************************************
*	Func Name   : ar_serial::ar_serial
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年08月24日 星期六 14时18分46秒
*	Description : create a serial connection to 
*	              arduino
**********************************************************/
ar_serial::ar_serial(char *Port_name)
{
	return ;
}

/*********************************************************
*	Func Name   : ar_serial::~ar_serial
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年08月24日 星期六 14时19分31秒
*	Description : shutdown the connection to arduino
*	              
**********************************************************/
ar_serial::~ar_serial()
{
	return;
}
