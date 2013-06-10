#include "basetype.h"

class rasp_connector 
{
	INT fd_sock;
	bool wired;
	CHAR domainname[40];

	private:
		void rasp_connector();
		void ~rasp_connector();
		void wireto(UCHAR *hostname);
		void TX(UCHAR *buffer, ULONG bufsize);
		void RX(UCHAR *buffer, ULONG bufsize);
	public:
		bool exchange(CHAR *hostname, CHAR *buffer, ULONG bufsize);
};
