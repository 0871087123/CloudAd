/*********************************************************
*	File Name   : stream.cpp
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月19日 星期六 17时55分04秒
*	Description : 这个模块负责服务器与树莓派的通讯。
*	              使用TCP流通讯。
**********************************************************/

/* 这里进行宏定义 */

/*********************************************************
*	Class Name  : stream_manager
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月19日 星期六 17时58分27秒
*	Description : 
*	              
**********************************************************/
class stream_manager {
	protected :
		/* 接入客户端文件描述符集合 */
		int epoll_set;
		/* 接入时读取请求超时时间 */
		int timeout_in_sec;
		/* 发送数据时请求超时时间 */
		int timeout_out_sec;
	private :
		/* 最大接入端数量 */
		int maxevent;
	public :
		/* 构造时输入两个超时时间 */
		stream_manager(int ti, int to);
		~stream_manager();
		/* 用于发送数据到接入的客户端 */
		int exchange(int fd_instance);
};
