#include "Register.h"

Register::Register()
{
	clientPtr = nullptr;
	serviceTime = 0;
	timeAccum = 0;
	clientsServiced = 0;
}

Register::~Register()
{
	
}

void Register::set_clientPtr(Client* clientPtr)
{
	this->clientPtr = clientPtr;
}

void Register::set_serviceTime(int serviceTime)
{
	this->serviceTime = serviceTime;

	this->incClientsServiced();
	this->addTime(serviceTime);
}

Client* Register::get_clientPtr() const
{
	return clientPtr;
}

int Register::get_serviceTime() const
{
	return serviceTime;
}

void Register::addTime(int time)
{
	timeAccum += time;
}

void Register::incClientsServiced()
{
	clientsServiced += 1;
}

int Register::get_timeAccum() const
{
	return timeAccum;
}

int Register::get_clientsServiced() const
{
	return clientsServiced;
}

bool Register::isFree() const
{
	if (!clientPtr)
	{
		return true;
	}

	return false;
}