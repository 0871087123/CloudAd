/*********************************************************
*	File Name   : stream.cpp
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月20日 星期日 15时37分20秒
*	Description : 这个文件为服务器收发信息的底层数据控制器
*	              
**********************************************************/
/* 系统头文件 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/timerfd.h>

/* 自有头文件 */
#include "include/basetype.h"
#include "include/stream.h"
#include "include/log.h"

/* 自有状态位 */
static bool sv_on = false;

/*********************************************************
*	Func Name   : setnoblock
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月26日 星期六 15时00分51秒
*	Description : 设置客户端io为非阻塞io
*	              
**********************************************************/
int setnoblock(int fd_instance)
{
	return fcntl(fd_instance, F_SETFL, O_NONBLOCK);
}


/*********************************************************
*	Func Name   : exit_server
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月25日 星期五 16时02分12秒
*	Description : 接收信号退出服务器
*	              
**********************************************************/
void exit_server(int sig)
{
	if ((SIGRTMAX - 1) == sig)
	{
		sv_on = false;
	}

	return;
}

/*********************************************************
*	Func Name   : stream_manager::stream_manager
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月20日 星期日 15时38分31秒
*	Description : 构造流处理器。申请epoll等fd。
*	              并且存储数据文件路径。
**********************************************************/
stream_manager::stream_manager(int ti, int to, char *path, int epoll_size)
{
	int epollfd = -1;
	this->maxevent = 0;

	this->timeout_in_sec = ti;
	this->timeout_out_sec = to;
	strcpy(this->data_path, path);

	if (SIG_ERR == signal(SIGRTMAX - 1, exit_server))
	{
		LOG("ERROR: SIGNAL HANDLE ERROR\n");
#ifdef __DEBUG__
		perror("SIGNAL:");
#endif
		return;
	}

	epollfd = epoll_create(epoll_size);
	if (0 > epollfd)
	{
		LOG("ERROR: CREATE EPOLL FAILED\n");
#ifdef __DEBUG__
		perror("EPOLL CREATE:");
#endif
	}
	else
	{
		this->epoll_set = epollfd;
		this->maxevent = epoll_size;
	}

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
	if (0 < this->epoll_set)
	{
		close(this->epoll_set);
	}

	return;
}

/*********************************************************
*	Func Name   : stream_manager::exchange
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月20日 星期日 15时40分04秒
*	Description : 用于交换信息
*	              返回0代表操作成功，返回-1代表失败。
**********************************************************/
int stream_manager::exchange(int fd_instance)
{
	/* 定义缓冲区 */
	char buf[MAX_DATALEN] = {0};
	int ret = 0;
#ifdef __NOBLOCK__
	ret = setnoblock(fd_instance);
	if (0 > ret)
	{
		LOG("Set No Block Error.\n");
	}
#endif

#ifdef __DEBUG__
	printf("IO FD:%d\n", fd_instance);
	perror("SetNoBlock:\n");
#endif

	/* 从客户端读取请求 */
	ret = read(fd_instance, buf, sizeof(buf));
	if (0 > ret)
	{
		LOG("ERROR: data READ Error\n");
		return -1;
	}

	if (0 != strncmp(buf, "GET", 3))
	{
		LOG("ERROR: Invalid Client Request.\n");
#ifdef __DEBUG__
		printf("%d %d %d\n", buf[0], buf[1], buf[2]);
#endif
		return -1;
	}

	ret = write(fd_instance, this->data_pub, this->data_len);
	if (0 > ret)
	{
		LOG("ERROR: data Put Error\n");
		return -1;
	}

	return 0;
}

/*********************************************************
*	Func Name   : stream_manager::get
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月22日 星期二 16时12分41秒
*	Description : 从文件读取数据
*	              
**********************************************************/
int stream_manager::get()
{
	/* 文件描述符和返回值 */
	int fd = -1;
	int ret = 0;
	char buf[MAX_DATALEN] = {0};

	if (0 != access(this->data_path, R_OK))
	{
		LOG("ERROR: Data File can't read.\n");
		goto __exit;
	}

	fd = open(this->data_path, O_RDONLY);
	if (0 > fd)
	{
		LOG("ERROR: File Open Error!\n");
		goto __exit;
	}

	ret = read(fd, buf, 32);
	if (0 >= ret)
	{
		LOG("ERROR: Data File Read Error!\n");
		goto __exit;
	}
	/* 拷贝数据 */
	memcpy(this->data_pub, buf, ret);
	this->data_len = ret;

	/* 完成数据从文件获取 */
	return 0;

/* 出错则返回-1 */
__exit:
	return -1;
}

/*********************************************************
*	Func Name   : stream_manager::start
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月22日 星期二 16时13分19秒
*	Description : 控制器启动,进行监听，并且持续处理连接
*	              
**********************************************************/
void stream_manager::start()
{
	int n = 0;
	int on = 1;
	int ret = -1;
	int sockfd = -1;		/* socket描述符 */
	int fd = -1;			/* 当前需要进行io的文件描述符 */
	int timerfd = -1;		/* 定时器描述符 */
	struct epoll_event ev;	/* socket的epoll */
	struct epoll_event tmp;	/* 接入客户端的epoll */
	struct epoll_event *events = (struct epoll_event *)malloc(this->maxevent * sizeof(ev));	/* 接入事件块 */
	struct sockaddr_in hostaddr;
	struct itimerspec standard;
	struct itimerspec tmval;
	memset(&standard, 0, sizeof(standard));
	memset(&tmval, 0, sizeof(tmval));
	memset(events, 0, sizeof(events));

	/* 判断是否初始化完整 */
	if (0 > this->epoll_set)
	{
		LOG("ERROR: EPOLL Init Failed.\n");
		return;
	}

	/* 创建socket，并且进行端口重用 */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (0 > sockfd)
	{
		LOG("ERROR: SOCKET Create Failed.\n");
		goto __exit;
	}
	ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	if (0 > ret)
	{
		LOG("REUSE ADDR AND PORT ERROR.\n");
		goto __exit;
	}

	/* 设置IPv4本机地址 */
	memset(&hostaddr, 0, sizeof(hostaddr));
	hostaddr.sin_family = AF_INET;
	hostaddr.sin_port = htons(AD_PORT);
	/* 绑定socket */
	ret = bind(sockfd, (struct sockaddr *)&hostaddr, sizeof(hostaddr));
	if (0 > ret)
	{
		LOG("ERROR: BIND PORT ERROR.\n");
#ifdef __DEBUG__
		perror("BIND:");
#endif
		close(sockfd);
		goto __exit;
	}

	/* 开始监听端口 */
	ret = listen(sockfd, 20);
	if (0 > ret)
	{
		LOG("ERROR: LISTEN Failed.\n");
		close(sockfd);
		goto __exit;
	}

	/* 监听端口加入epoll */
	ev.events = EPOLLIN;
	ev.data.fd = sockfd;
	ret = epoll_ctl(this->epoll_set, EPOLL_CTL_ADD, sockfd, &ev);
	if (0 > ret)
	{
		LOG("ERROR: EPOLL ADD FAILED\n");
#ifdef __DEBUG__
		perror("ADD EPOLL:");
#endif
		close(sockfd);
		goto __exit;
	}

	/* 主循环 */
	/* 获取一次数据 */
	sv_on = true;
	ret = this->get();
	if (0 == ret)
	{
		LOG("DATA GET FROM FILE OK.\n");
	}

	/* 创建定时器 */
	timerfd = timerfd_create(CLOCK_REALTIME, 0);
	if (0 > timerfd)
	{
		LOG("ERROR: Timer fd create failed.\n");
		goto __exit;
	}
	standard.it_interval.tv_sec = this->timeout_in_sec;
	standard.it_value.tv_sec = this->timeout_in_sec;
	memcpy(&tmval, &standard, sizeof(tmval));
	if (0 >
			timerfd_settime(timerfd, 0, &tmval, NULL))
	{
		LOG("ERROR: Timer Set failed.\n");
	}
	/* 定时器加入epoll */
	memset(&tmp, 0, sizeof(tmp));
	tmp.events = EPOLLIN | EPOLLET;
	tmp.data.fd = timerfd;
	ret = epoll_ctl(this->epoll_set, EPOLL_CTL_ADD, timerfd, &tmp);
	if (0 > ret)
	{
		LOG("ERROR: EPOLL ADD timer FAILED\n");
#ifdef __DEBUG__
		perror("ADD timer:");
#endif
		close(sockfd);
		goto __exit;
	}
	LOG("Timer is Ready\n");
#ifdef __DEBUG__
	printf("Time is %d\n", tmval.it_interval.tv_sec);
#endif


	while (1)
	{
__epoll_wait:
		/* 检查是否需要进行退出操作 */
		if (true != sv_on)
		{
			close(sockfd);
			LOG("SERVER Received signal, now exiting.\n");
			this->~stream_manager();
			return;
		}

		/* 开始等待io */
		fd = epoll_wait(this->epoll_set, events, this->maxevent, -1);
		if (0 > fd)
		{
			close(sockfd);
			LOG("ERROR: EPOLL WAIT ERROR.\n");
#ifdef __DEBUG__
			perror("EPOLL WAIT:");
#endif
			goto __exit;
		}

#ifdef __DEBUG__
		printf("fds epoll in : %d\n", fd);
		printf("sockfd is:%d\n", sockfd);
		printf("epoll_set is : %d\n", this->epoll_set);
#endif
		/* 循环处理各种事件 */
		for(n = 0; n < this->maxevent; n++)
		{
			fd = events[n].data.fd;
			if (sockfd == fd)
			{
				/* 接受连接请求，不进行地址过滤等事项 */
				fd = accept(sockfd, NULL, NULL);
				if (0 > fd)
				{
					LOG("ERROR: ACCEPT ERROR!\n");
				}
				else
				{
					/* 监听端口加入epoll */
					memset(&tmp, 0, sizeof(tmp));
					tmp.events = EPOLLIN;
					tmp.data.fd = fd;
					ret = epoll_ctl(this->epoll_set, EPOLL_CTL_ADD, fd, &tmp);
					if (0 > ret)
					{
						LOG("ERROR: CLIENT ADD TO EPOLL FAILED\n");
						goto __exit;
					}
					else
					{
						LOG("CLIENT ACCEPT OK.\n");
					}
				}
			}
			else if (fd == timerfd)
			{
				ret = this->get();
				if (0 == ret)
				{
					LOG("DATA GET FROM FILE OK.\n");
				}
				memcpy(&tmval, &standard, sizeof(tmval));
				if (0 >
						timerfd_settime(timerfd, 0, &tmval, NULL))
				{
					LOG("ERROR: Timer Reset failed.\n");
				}
				goto __epoll_wait;
			}
			else if (0 < fd)
			{
				/* client data exchange */
				ret = this->exchange(fd);
				if (0 == ret)
				{
					LOG("CLIENT EXCHANGE DATA OK.\n");
				}
				tmp.events = EPOLLIN;
				tmp.data.fd = fd;
				ret = epoll_ctl(this->epoll_set, EPOLL_CTL_DEL, fd, &tmp);
				close(fd);
				if (0 > ret)
				{
					LOG("ERROR: CLIENT EXIT FAILED.\n");
#ifdef __DEBUG__
					perror("Client Exit:");
					printf("Client Event:%d", events[n].events);
					printf("Is Client HUP? :%d\n", events[n].events & EPOLLHUP);
#endif
				}
				else
				{
					LOG("CLIENT EXIT OK.\n");
				}
			}
		}

		LOG("EPOLL WAIT OK.\n");
	}

__exit:
	close(timerfd);
	close(this->epoll_set);
	this->epoll_set = -1;
	return;
}
