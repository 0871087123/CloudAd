/*********************************************************
*	File Name   : stlv.h
*	Project     : PUBLIC
*	Author      : Kent
*	Data        : 2013年10月22日 星期二 15时41分36秒
*	Description : 实现数据包封装解封装的功能
*	              需要在此头文件之前引用string.h和arpa/inet.h
**********************************************************/
#ifndef ___STLV
#define ___STLV

/* 这里定义各种长度的宏 */
#define STLV_BUF_LEN_MAX 65531
#define STLV_BUF_LEN_MIN 255

/* 定义数据结构 */
typedef struct tag_struct_STLV {
	unsigned short type;
	unsigned short len;
	void *data;
} STLV;

/*********************************************************
*	Func Name   : stlv_set
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月22日 星期二 15时45分03秒
*	Description : 对TLV包进行封装
*	              不进行基本的输入参数是否合法的判断。
**********************************************************/
static inline int stlv_set(char *buf, int buflen, STLV *pack)
{
	/* 对数据进行定义 */
	unsigned short *prefix_p = (unsigned short *) buf;

	/* 判断缓冲区是否足够 */
	if (buflen < (pack->len + 4))
	{
		return -1;
	}

	/* 数据处理 */
	*prefix_p = htons(pack->type);
	*(prefix_p + 1) = htons(pack->len);
	memcpy(buf + 4, (char *)pack->data, pack->len);

	return pack->len + 4;
}


/*********************************************************
*	Func Name   : stlv_get
*	Project     : Cloud_AD
*	Author      : Kent
*	Data        : 2013年10月22日 星期二 15时56分57秒
*	Description : 对TLV包进行解封装
*	              不进行输入参数的合法性判断
**********************************************************/
static inline int stlv_get(STLV *pack, int data_len, char *buf, char buf_len)
{
	/* 初始化需要的参数 */
	unsigned short *prefix_p = (unsigned short *) buf;
	unsigned short packlen = 0;

	/* 判断缓冲区是否足够 */
	if ((buf_len < 4) || (data_len < (buf_len - 4)))
	{
		return -1;
	}

	/* 判断包是否合法(接收数据不全) */
	packlen = ntohs(*(prefix_p + 1));
	if (buf_len < packlen + 4)
	{
		return -1;
	}

	/* 数据处理 */
	pack->type = ntohs(*prefix_p);
	pack->len = ntohs(*(prefix_p + 1));
	memcpy(pack->data, buf + 4, pack->len);

	return pack->len;
}

#endif
