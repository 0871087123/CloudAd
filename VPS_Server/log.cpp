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
#include <stdio.h>
#include <error.h>

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
	FILE *file_p = NULL;

	/* 数据初始化 */
	memset(this->log_path, 0, FILE_NAME_LEN);
	this->log_fd = NULL;
	this->log_on = false;

	/* 处理输入参数 */
	this->log_on = status;
	strcpy(this->log_path, logfile);

	if (true == this->log_on)
	{
		/* 打开文件描述符 */
		file_p = fopen(this->log_path, "a+");
		if (NULL == file_p)
		{
			perror("OPEN LOGFILE:");
			this->log_on = false;
		}
		else
		{
			this->log_fd = file_p;
		}
	}

	/* 赋值全局变量 */
	log = this;
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
	if (true == this->log_on)
	{
		fclose(this->log_fd);
	}

	log = NULL;
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
void logserver::printlog(const char *logstring)
{
	int ret = 0;
	if (true == this->log_on)
	{
		fprintf(this->log_fd, logstring);
		ret = fflush(this->log_fd);
#ifdef __DEBUG__
		if (0 > ret)
		{
			perror("Flush File Stream:");
		}
#endif
	}
	else
	{
		printf(logstring);
	}
	return;
}
