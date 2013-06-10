#include <iostream>
#include <SerialPort.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

int main()
{
	SerialPort myport("/dev/ttyACM0");
	myport.Open(SerialPort::BAUD_9600, SerialPort::CHAR_SIZE_8, SerialPort::PARITY_NONE, SerialPort::STOP_BITS_1, SerialPort::FLOW_CONTROL_HARD);
	myport.SetDtr(true);
	myport.SetRts(true);
	if (myport.IsOpen() == false)
	{
		cout << "error\n" << endl;
		myport.Close();
		return 0;
	}
	int i=0;
	char buf[100];
#if 1
	sleep(2);
	i = 0;
	myport.Write("c");
	try{
	for (i=0; i < 50; i++)
	{
		buf[i] = myport.ReadByte(10);
	}
	}
	catch(SerialPort::ReadTimeout){
		printf("%d\n", i);
	};;
	write(1, buf, i);
	myport.Close();
	cout << "\nDone" <<endl;
#endif
#if 0
	char ts;
	for (i = 0; i < 10; i++)
	{
		ts = myport.ReadByte();
		cout << ts;
	}
	cout << endl;
#endif

	return 0;

}
