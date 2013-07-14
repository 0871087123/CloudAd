#include "basetype.h"
#include "dns.h"
#include "function.h"
#include <string.h>

void deamon::deamon()
{
	memset(this->advertise, 0, ADSIZE);
	this->ad_len = 0;
	this->rasp_connector = new rasp_connector();

	return;
}

void deamon::deamon()
{
	memset(this->advertise, 0, ADSIZE);
	this->ad_len = 0;
	delete this->rasp_connector;
}
