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
		void wireto(CHAR *hostname);
		void TX(UCHAR *buffer, ULONG bufsize);
		void RX(UCHAR *buffer, ULONG bufsize);
	public:
		bool exchange(CHAR *hostname, CHAR *buffer, ULONG bufsize);
};
