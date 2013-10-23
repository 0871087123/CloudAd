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
		/* 需要发布给客户端的数据文件路径（绝对路径） */
		/* PS:每一定时间重新读取一次 */
		char data_path[FILE_NAME_LEN];
		/* 具体数据以及长度 */
		char data_pub[MAX_DATALEN];
		char data_len;
		/* 接入客户端文件描述符集合 */
		int epoll_set;
	private :
		/* 接入时读取请求超时时间 */
		int timeout_in_sec;
		/* 发送数据时请求超时时间 */
		int timeout_out_sec;
		/* 最大接入端数量 */
		int maxevent;
		/* 用于发送数据到接入的客户端 */
		int exchange(int fd_instance);
		/* 从文件设置流控制器需要发布的数据 */
		int get(int datalen, char *data);
	public :
		/* 构造时输入两个超时时间 */
		stream_manager(int ti, int to, char *path, int epoll_size);
		~stream_manager();
		/* 流控制器的启动函数 */
		void start();
		/* 定义友元类 */
		friend class server;
};
