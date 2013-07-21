/*
#	这个文件主要包含运行在树莓派上的守护进程。
#	每隔一段时间，树莓派通过网络向服务器请求新的网络数据。
#	获取到新的网络数据之后，将文本传输至单片机。
#	单片机通过使用1602显示对文本进行显示。
#	头文件调用关系：
#		需要在之前调用dns.h
#		需要在之前引用Serial.h
*/

#incllude "basetype.h"

#define ADSIZE 100
class deamon
{
	private:
		UCHAR advertise[ADSIZE];				/* 用于保存post信息 */
		ULONG ad_len;							/* post信息的长度 */
		ULONG acquire();						/* 从服务器下载post信息 */
		ULONG AD_down(AD_flag, void *data);		/* 下传post信息到1602 */
		class *rasp_connector;					/* 需要一个和服务器的连接器 */

	public:
		deamon();								/* 创建deamon */
		~deamon();
};
