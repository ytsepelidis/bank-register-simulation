#ifndef EVENTLIST_H
#define EVENTLIST_H

#include "Event.h"

class EventList
{
private:
	static int s_EventListLength;

	Event* eventPtr;
	EventList* nextEventPtr;

public:
	EventList();
	EventList(int time, std::string type);
	~EventList();

	void enqueue(int time, std::string type);
	void dequeue();
	void printEventList() const;
	std::string get_eventType() const;

	static int getEventListLength();
	static bool isEmpty();
};

#endif // !EVENTLIST_H