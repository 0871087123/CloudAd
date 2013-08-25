#include "basetype.h"

class rasp_connector 
{
	private:
	INT fd_sock;
	bool wired;

	public:
	CHAR domainname[40];

	private:
		rasp_connector();
		~rasp_connector();
		void wireto(const CHAR *hostname);
		ULONG TX(UCHAR *buffer, ULONG bufsize);
		ULONG RX(UCHAR *buffer, ULONG bufsize);
	public:
		unsigned int exchange(CHAR *hostname, UCHAR *buffer, ULONG bufsize);
};
