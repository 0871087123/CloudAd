/*********************************************************
*	File Name   : function.h
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月19日 星期六 17时51分52秒
*	Description : 这个文件包含了守护进程的主要功能
*	              
**********************************************************/

/*********************************************************
*	Class Name  : server
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月19日 星期六 17时52分18秒
*	Description : 服务器可以接受请求，并且根据内存中的数据
*	              回应显示的数据
**********************************************************/
class server {
	protected:
	private:
		/* 服务器的流控制器 */
		stream_manager *controler;
		/* 服务器的配置文件位置与日志文件位置 */
		char configfile[FILE_NAME_LEN];
	public:
		/* 启动参数需要一个配置文件 */
		server(char *configfile);
		~server();
		/* 使用status控制服务器的开关 */
		void start();
};
