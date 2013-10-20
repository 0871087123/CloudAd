/*********************************************************
*	File Name   : stream.cpp
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月20日 星期日 15时37分20秒
*	Description : 这个文件为服务器收发信息的底层数据控制器
*	              
**********************************************************/
/* 系统头文件 */

/* 自有头文件 */
#include "include/basetype.h"
#include "include/stream.h"

/*********************************************************
*	Func Name   : stream_manager::stream_manager
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月20日 星期日 15时38分31秒
*	Description : 构造流处理器。申请epoll等fd。
*	              
**********************************************************/
stream_manager::stream_manager(int ti, int to)
{
	return;
}

/*********************************************************
*	Func Name   : stream_manager::~stream_manager
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月20日 星期日 15时39分11秒
*	Description : 析构函数。删除epoll等fd。
*	              
**********************************************************/
stream_manager::~stream_manager()
{
	return;
}

/*********************************************************
*	Func Name   : stream_manager::exchange
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月20日 星期日 15时40分04秒
*	Description : 用于交换信息
*	              
**********************************************************/
int stream_manager::exchange(int fd_instance)
{
	return -1;
}
