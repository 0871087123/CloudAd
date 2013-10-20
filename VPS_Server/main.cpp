/*********************************************************
*	File Name   : main.cpp
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月20日 星期日 14时32分12秒
*	Description : 这个文件是服务器守护进程的主要部分，负责
*	              解析输入参数。
**********************************************************/
/* 系统头文件 */
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

/* 自有头文件 */
#include "include/basetype.h"
#include "include/stream.h"
#include "include/function.h"

struct config {
	bool help;
	bool debug;
	char configfile[FILE_NAME_LEN];
	char logfile[FILE_NAME_LEN];
};

/*********************************************************
*	Func Name   : printhelp
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月20日 星期日 14时31分58秒
*	Description : 打印帮助信息
*	              
**********************************************************/
void printhelp()
{
	using namespace std;
	cout << "Use like : VCloudd -debug -configfile=./config -logfile=./log\n" \
		 <<	"\t-debug : run as a consol process , will not create daemon process.\n"\
		 <<	"\t-configfile=YOUR_CONFIG_FILE_PATH\n"\
		 <<	"\t-logfile=YOUR_LOG__FILE_PATH\n"\
		 <<	"thank you for using this software.\n";
	return;
}

/*********************************************************
*	Func Name   : param_is_valid
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月20日 星期日 14时51分39秒
*	Description : 检查参数是否合法
*	              
**********************************************************/
bool param_is_valid(struct config *cfg)
{
	bool ret = true;

	/* 检查配置文件和日志文件 */
	if ('\0' == cfg->configfile[0])
	{
		ret = false;
	}
	if ('\0' == cfg->logfile[0])
	{
		ret = false;
	}
	if (true == cfg->help)
	{
		ret = true;
	}

	return ret;
}

/*********************************************************
*	Func Name   : parse_param
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月20日 星期日 14时12分45秒
*	Description : 解析参数
*	              
**********************************************************/
int parse_param(int argc, char *argv[], struct config *cfg)
{
	int i = 0;
	int err = 0;
	int ret = 0;

	if (argc > 1)
	{
		for (i = 1; i <argc; i++)
		{
			if ('-' == argv[i][0])
			{
				switch (argv[i][1])
				{
					/* 打印帮助 */
					case '-' : 
						{
							if (0 == strcmp(argv[i], "--help"))
							{
								printhelp();
								cfg->help = true;
							}
							else
							{
								goto exit;
							}
						}; break;
					case 'd' : 
						{
							if (0 == strcmp(argv[i], "-debug"))
							{
								cfg->debug = true;
							}
							else
							{
								goto exit;
							}
						}; break;
					case 'c' :
						{
							ret = 0;
							if (0 == strncmp(argv[i], "-configfile=", 12))
							{
								ret = sscanf(argv[i], "-configfile=%s", cfg->configfile);
							}
							if (0 >= ret)
							{
								goto exit;
							}
						}; break;
					case 'l' :
						{
							ret = 0;
							if (0 == strncmp(argv[i], "-logfile=", 9))
							{
								ret = sscanf(argv[i], "-logfile=%s", cfg->logfile);
							}
							if (0 >= ret)
							{
								goto exit;
							}
						}; break;
					default : goto exit;
				}
			}
		}
	}
	else
	{
		goto exit;
	}

	if (true == param_is_valid(cfg))
	{
		return 0;
	}

exit:
	return -1;
}

/*********************************************************
*	Func Name   : main
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月19日 星期六 17时47分19秒
*	Description : 主函数
*	              
**********************************************************/
int main(int argc, char *argv[])
{
	struct config cfg;
	int err = 0;
	pid_t spid = 0;
	server *server_process = NULL;

	/* 初始化参数结构 */
	memset(&cfg, 0, sizeof(cfg));

	/* 解析参数 */
	err = parse_param(argc, argv, &cfg);
	
	using namespace std;
	if (err != 0)
	{
		cout << "Invalid Param!" << endl;
		cout << "Please use \"--help\" to see Users' Guide." << endl;
		return 0;
	}

	/* 打印帮助则可以直接退出 */
	if (true == cfg.help)
	{
		return 0;
	}

	if (false == cfg.debug)
	{
		/* 创建守护进程 */
		spid = daemon(1,0);
		if (0 != spid)
		{
			cout << "Make Daemon Error!" << endl;
			return 0;
		}
	}

	server_process = new server(cfg.configfile, cfg.logfile);
	server_process->start(true);

	cout << "Function not realized!" << endl;
	return 0;
}
