/*********************************************************
*	File Name   : function.cpp
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月20日 星期日 15时23分58秒
*	Description : 这个文件包含守护进程的主要功能
*	              
**********************************************************/
/* 系统头文件 */
#include <string.h>

/* 自有头文件 */
#include "include/basetype.h"
#include "include/stream.h"
#include "include/function.h"

/*********************************************************
*	Func Name   : server::server
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月20日 星期日 15时32分00秒
*	Description : 服务端的构造函数
*	              
**********************************************************/
server::server(char *config, char *log)
{
	/* 初始化所有数据 */
	memset(this->data, 0, sizeof(this->data));
	memset(this->configfile, 0, sizeof(this->configfile));
	memset(this->logfile, 0, sizeof(this->logfile));
	this->controler = NULL;
	return;
}

/*********************************************************
*	Func Name   : server::~server
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月20日 星期日 15时34分09秒
*	Description : 服务端的析构函数
*	              
**********************************************************/
server::~server()
{
	/* 删除流控制器 */
	delete this->controler;
	return;
}

/*********************************************************
*	Func Name   : server::start
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月20日 星期日 15时35分11秒
*	Description : 启动服务器。
*	              
**********************************************************/
void server::start(bool status)
{
	return;
}
