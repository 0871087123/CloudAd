#include "basetype.h"

class RaspConnector 
{
	int fd_sock;
	bool wired;
	private:
		void wireto(UCHAR *hostname);
		void TX(UCHAR *buffer, ULONG bufsize);
		void RX(UCHAR *buffer, ULONG bufsize);
	public:
		bool exchange(CHAR *hostname, CHAR *buffer, ULONG bufsize);
};
