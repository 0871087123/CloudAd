/*********************************************************
*	File Name   : function.cpp
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月20日 星期日 15时23分58秒
*	Description : 这个文件包含守护进程的主要功能
*	              
**********************************************************/
/* 系统头文件 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

/* 自有头文件 */
#include "include/basetype.h"
#include "include/log.h"
#include "include/stream.h"
#include "include/function.h"

/* 定义宏 */
#define CONFIG_FILE_SIZE_MAX 1024

/*********************************************************
*	Func Name   : server::server
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月20日 星期日 15时32分00秒
*	Description : 服务端的构造函数
*	              
**********************************************************/
server::server(char *config)
{
	char configdata[CONFIG_FILE_SIZE_MAX] = {0};
	int cnf_fd = -1;
	int ret = 0;
	int ti = 30;
	int to = 30;
	int epoll_size = 10;
	char datapath[FILE_NAME_LEN] = "./data.pub";
	char *strtmp = NULL;

	/* 初始化所有数据 */
	memset(this->configfile, 0, sizeof(this->configfile));
	this->controler = NULL;
	strcpy(this->configfile, config);

	/* 检测配置文件是否可读 */
	if (0 != access(this->configfile, R_OK))
	{
		LOG("CONFIGFILE Access Failed.\n");
		goto __basestart;
	}

	/* 读取配置文件 */
	cnf_fd = open(this->configfile, O_RDONLY);
	if (0 > cnf_fd)
	{
		LOG("CONFIGFILE Open failed.\n");
		return;
	}	
	ret = read(cnf_fd, configdata, sizeof(configdata));
	close(cnf_fd);
	if (0 >= ret)
	{
		LOG("CONFIGFILE Read Error.\n");
		return;
	}

	/* 解析需要的参数 */
	strtmp = strcasestr(configdata, "in_timeout=");
	if (NULL != strtmp)
	{
		sscanf(strtmp, "in_timeout=%d", &ti);
	}
	strtmp = strcasestr(configdata, "out_timeout=");
	if (NULL != strtmp)
	{
		sscanf(strtmp, "out_timeout=%d", &to);
	}
	strtmp = strcasestr(configdata, "epoll_size=");
	if (NULL != strtmp)
	{
		sscanf(strtmp, "epoll_size=%d", &epoll_size);
	}
	strtmp = strcasestr(configdata, "datapath=");
	if (NULL != strtmp)
	{
		sscanf(strtmp, "datapath=%s", datapath);
	}
	
__basestart:
	/* 解析完成后创建服务器底层数据服务 */
	this->controler = new stream_manager(ti, to, datapath, epoll_size);
	LOG("Create Server Base Service.\n");
#ifdef __DEBUG__
	printf("ti : %d\nto : %d\n epoll_size : %d\ndatapath : %s\n", ti, to, epoll_size, datapath);
	write(1, configdata, ret);
#endif

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
	if (NULL == this->controler)
	{
		return;
	}
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
void server::start()
{
	if (NULL == this->controler)
	{
		LOG("Server Not Ready.\n");
		return;
	}

	/* 启动服务器 */
	LOG("Start Server.\n");
	this->controler->start();

	return;
}
