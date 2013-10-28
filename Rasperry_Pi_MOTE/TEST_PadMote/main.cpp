#include <iostream>
#include <SerialPort.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int main()
{
	int i;
	int size = 0;
	int lgth = 0;
	unsigned char buffer[34] = {0};
	unsigned char tmp;
	
	/* 打开串口 */
	SerialPort myport("/dev/ttyACM0");
	myport.Open(SerialPort::BAUD_9600, SerialPort::CHAR_SIZE_8, SerialPort::PARITY_NONE, SerialPort::STOP_BITS_1, SerialPort::FLOW_CONTROL_HARD);
	//myport.SetDtr(true);
	//myport.SetRts(true);

	/* 测试数据 */
	size = 34;
	buffer[0] = 0x08;
	buffer[1] = 32;

	sleep(4);
	
	if (myport.IsOpen() == false)
	{
		cout << "error\n" << endl;
		myport.Close();
		return 0;
	}

	try{
			lgth = read(0, buffer + 2, 32);
			buffer[1] = lgth - 1;
			for (i = 0; i < lgth + 1; i++)
			{
				myport.WriteByte(buffer[i]);
			}
	}

	catch(SerialPort::NotOpen){
		printf("Not Open\n");
	}

	myport.Close();

	sleep(10);

	return 0;
}
