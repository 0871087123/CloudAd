#include "basetype.h"

class rasp_connector 
{
	private:
	INT fd_sock;
	bool wired;

	public:
	CHAR domainname[40];

	private:
		void wireto(const CHAR *hostname);
		ULONG TX(char *buffer, ULONG bufsize);
		ULONG RX(char *buffer, ULONG bufsize);
	public:
		rasp_connector();
		~rasp_connector();
		unsigned int exchange(CHAR *hostname, char *buffer, ULONG bufsize);
};
