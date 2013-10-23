/*********************************************************
*	File Name   : log.h
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月22日 星期二 16时15分02秒
*	Description : 服务器的日志模块
*	              
**********************************************************/

/*********************************************************
*	Class Name  : logserver
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月22日 星期二 16时15分29秒
*	Description : 服务器日志模块头文件
*	              
**********************************************************/
class logserver {
	protected:
		/* 服务器的日志文件描述符 */
		FILE *log_fd;
		/* 服务器的日志文件绝对路径 */
		char log_path[FILE_NAME_LEN];
	private:
		
	public:
		/* 日志打印开关 */
		bool log_on;
		logserver(char *logfile, bool status);
		~logserver();
		void printlog(char *log);
};

/* 声明log服务器实例 */
extern logserver *log;
/* 简单打印日志的宏 */
#define LOG(a) log->printlog(a);
