#ifndef __UT__
#define STATIC static
#else
#define STATIC
#endif

#ifdef __UT__
#define private public
#define protected public
#endif

typedef unsigned char UCHAR;
typedef unsigned long ULONG;
typedef unsigned int UINT;
typedef unsigned short USHORT;

typedef char CHAR;
typedef long LONG;
typedef int INT;
typedef short SHORT;

