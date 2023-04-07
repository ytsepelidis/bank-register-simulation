#ifndef EVENT_H
#define EVENT_H

#include <iostream>

class Event
{
private:
	int time;
	std::string eventType;

public:
	Event(int time, std::string eventType);
	~Event();

	void set_time(int time);
	void set_eventType(std::string eventType);
	int get_time() const;
	std::string get_eventType() const;
};

#endif // !EVENT_H