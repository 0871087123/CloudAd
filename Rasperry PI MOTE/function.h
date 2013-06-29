/*
#	这个文件主要包含运行在树莓派上的守护进程。
#	每隔一段时间，树莓派通过网络向服务器请求新的网络数据。
#	获取到新的网络数据之后，将文本传输至单片机。
#	单片机通过使用1602显示对文本进行显示。
#
*/

#incllude "basetype.h"

class deamon
{
	private:
		UCHAR advertise[100];
		ULONG ad_len;
		ULONG acquire();
		ULONG exchangeAD();

	public:
		deamon();
		~deamon();
};
