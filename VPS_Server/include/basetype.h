#ifndef __BASET__
#define __BASET__

#ifndef __UT__
#define STATIC static
#else
#define STATIC
#endif

#ifdef __UT__
#define private public
#define protected public
#endif

#ifdef __UT__
//#error
#endif

typedef unsigned char UCHAR;
typedef unsigned long ULONG;
typedef unsigned int UINT;
typedef unsigned short USHORT;

typedef char CHAR;
typedef long LONG;
typedef int INT;
typedef short SHORT;

#ifndef AD_PORT 
#define AD_PORT 43212
#define MAX_DATALEN 65535
#endif

#ifndef ___PARAIGNORE 
#define PARAIGNORE(x) (void)x
#define ___PARAIGNORE
#endif

#ifndef ___FILENAMELEN
#define FILE_NAME_LEN 100
#define ___FILENAMELEN
#endif

struct tag_pack {
	USHORT type;
	USHORT length;
	UCHAR data[MAX_DATALEN];
};
typedef struct tag_pack pack;


#endif
