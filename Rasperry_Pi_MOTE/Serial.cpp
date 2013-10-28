/*********************************************************
*	File Name   : Serial.cpp
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年08月24日 星期六 14时15分48秒
*	Description : this file realize posting advertise to 
*	              arduino
**********************************************************/
/* 系统头文件 */
#include <unistd.h>
#include <string.h>
#include <SerialPort.h>
#include <stdio.h>

/* 自有头文件 */
#include "basetype.h"
#include "Serial.h"
#include "log.h"

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
	int i = 0;
	char type = 0x08;
	char length = data_len;
	
	/* 检查数据是否超出长度 */
	if (32 < data_len)
	{
		LOG("ERROR: Data over flow.\n");
		return 0;
	}

	/* 设置串口并且打开串口 */
	SerialPort myPort(this->portname);
	try 
	{
		myPort.Open(SerialPort::BAUD_9600, SerialPort::CHAR_SIZE_8, SerialPort::PARITY_NONE, SerialPort::STOP_BITS_1, SerialPort::FLOW_CONTROL_HARD);
	}
	catch(SerialPort::OpenFailed)
	{
		LOG("ERROR: SerialPort Open Failed\n");
		goto __exit;
	}
	if (myPort.IsOpen() == false)
	{
		LOG("ERROR: SerialPort Open Failed\n");
		goto __exit;
	}

	/* 等待arduino启动完成 */
	sleep(4);

	/* 写入数据 */
#ifdef __DEBUG__
	printf("Data is : %s\n", data);
#endif
	try
	{
		myPort.WriteByte(type);
		myPort.WriteByte(length);
		for (i = 0; i < data_len; i++)
		{
			myPort.WriteByte(data[i]);
		}
	}
	catch (SerialPort::NotOpen)
	{
		LOG("ERROR: SerialPort is Closed.\n");
		goto __exit;
	}

	LOG("Serial Comm OK\n");
#ifdef __DEBUG__
	printf("%s\n", data);
	printf("%d\n", data_len);
#endif

__exit:
	myPort.Close();
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
	strcpy(this->portname, Port_name);
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
