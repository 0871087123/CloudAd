/*********************************************************
*	File Name   : log.cpp
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月22日 星期二 16时21分54秒
*	Description : 服务器的日志模块
*	              
**********************************************************/
/* 公共头文件 */
#include <string.h>

/* 自有头文件 */
#include "include/basetype.h"
#include "include/log.h"

/* 定义全局变量 */
logserver *log = NULL;
/*********************************************************
*	Func Name   : logserver::logserver
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月22日 星期二 16时22分36秒
*	Description : 处理输入参数，启动log模块
*	              
**********************************************************/
logserver::logserver(char *logfile, bool status)
{
	/* 数据初始化 */
	memset(this->log_path, 0, FILE_NAME_LEN);
	this->log_fd = -1;
	this->log_on = false;

	/* 处理输入参数 */
	this->log_on = status;

	return;
}

/*********************************************************
*	Func Name   : logserver::~logserver
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月22日 星期二 16时27分11秒
*	Description : 关闭log模块，销毁文件描述符
*	              
**********************************************************/
logserver::~logserver()
{
	return;
}

/*********************************************************
*	Func Name   : logserver::printlog
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月22日 星期二 16时27分44秒
*	Description : 打印日志到文件，或者终端。
*	              
**********************************************************/
void logserver::printlog(char *log, int len)
{
	return;
}
