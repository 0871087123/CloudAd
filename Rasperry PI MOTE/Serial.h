/*********************************************************
*	File Name   : Serial.h
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年08月24日 星期六 14时20分49秒
*	Description : 这个文件包含树莓派与arduino之间串口通信的程序模块。
*				  树莓派收到新AD之后，通过这个文件中的串口通信模块，
*				  将数据传输至arduino单片机。
**********************************************************/

/* only has 1 data transfer type now */
typedef enum tag_Flag {
	flag_default = 0,
	flag_print,
	flag_butt,
} AD_flag;

class ar_serial{
	public :
		ar_serial(char *Port_name);
		~ar_serial();
		unsigned int post(int data_len, char *data);
};

