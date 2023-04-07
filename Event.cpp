#include "Event.h"

Event::Event(int time, std::string eventType)
{
	this->time = time;
	this->eventType = eventType;
}

Event::~Event()
{
	time = 0;
	eventType.clear();
}

void Event::set_time(int time)
{
	this->time = time;
}

void Event::set_eventType(std::string eventType)
{
	this->eventType = eventType;
}

int Event::get_time() const
{
	return time;
}

std::string Event::get_eventType() const
{
	return eventType;
}