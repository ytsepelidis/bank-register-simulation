#ifndef REGISTER_H
#define REGISTER_H

#include "Client.h"

class Register
{
private:
	Client* clientPtr;
	int serviceTime;
	int timeAccum;
	int clientsServiced;

public:
	Register();
	~Register();

	void set_clientPtr(Client* clientPtr);
	void set_serviceTime(int serviceTime);
	Client* get_clientPtr() const;
	int get_serviceTime() const;

	void addTime(int time);
	void incClientsServiced();
	int get_timeAccum() const;
	int get_clientsServiced() const;
	bool isFree() const;
};

#endif // !REGISTER_H