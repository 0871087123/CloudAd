/*	这个文件包含树莓派与arduino之间串口通信的程序模块。
 *	树莓派收到新AD之后，通过这个文件中的串口通信模块，
 *	将数据传输至arduino单片机。
 *	*/
#include "basetype.h"

/* only has 1 flag now */
typedef enum tag_Flag {
	flag_default = 0;
	flag_print;
	flag_butt;
} AD_flag;

class ar_serial{
	public :
		ULONG post();
};
