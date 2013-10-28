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
*	Func Name   : arduino_lcd::post
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年08月24日 星期六 14时17分28秒
*	Description : posting advertise to arduino
*	              
**********************************************************/
unsigned int arduino_lcd::post(int data_len, char *data)
{
	return 0;
}

/*********************************************************
*	Func Name   : arduino_lcd::arduino_lcd
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年08月24日 星期六 14时18分46秒
*	Description : create a serial connection to 
*	              arduino
**********************************************************/
arduino_lcd::arduino_lcd(char *Port_name)
{
	return ;
}

/*********************************************************
*	Func Name   : arduino_lcd::~arduino_lcd
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年08月24日 星期六 14时19分31秒
*	Description : shutdown the connection to arduino
*	              
**********************************************************/
arduino_lcd::~arduino_lcd()
{
	return;
}
