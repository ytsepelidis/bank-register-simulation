#include "Event.h"
#include "EventList.h"

int EventList::s_EventListLength = 0;

EventList::EventList()
{
	eventPtr = nullptr;
	nextEventPtr = nullptr;
}

EventList::EventList(int time, std::string type)
{
	eventPtr = new Event(time, type);

    // Error check
	if (!eventPtr)
	{
		std::cout << "Error creating new Event for EventList node.\n";
	}

    s_EventListLength += 1;
	nextEventPtr = nullptr;
}

EventList::~EventList()
{
    s_EventListLength -= 1;
	delete eventPtr;
}

void EventList::enqueue(int time, std::string type)
{
    EventList* newEventNode = new EventList(time, type);

    // Error check
    if (!newEventNode)
    {
        std::cout << "Error creating new EventList node.\n";
    }

    // If EventList is empty
    if (!nextEventPtr)
    {
        nextEventPtr = newEventNode;
        return;
    }

    EventList* temp = nextEventPtr;

    // Traversing to end of EventList
    while (temp->nextEventPtr != nullptr)
    {
        temp = temp->nextEventPtr;
    }

    // Adding new EventList node
    temp->nextEventPtr = newEventNode;
}

void EventList::dequeue()
{
    EventList* eventNodeToRemove = nextEventPtr;

    // Check for empty EventList
    if (!nextEventPtr)
    {
        std::cout << "EventList is empty, no more events to remove.\n";
        return;
    }

    // EventList head node points to next node
    nextEventPtr = eventNodeToRemove->nextEventPtr;

    // Deleting node
    delete eventNodeToRemove;
}

void EventList::printEventList() const
{
    EventList* temp = nextEventPtr;

    // If EventList is empty
    if (!nextEventPtr)
    {
        std::cout << "EventList is empty.\n";
        return;
    }

    // Traverse and print the EventList
    std::cout << "Printing EventList:\n";

    while (temp != nullptr)
    {
        std::cout << "Time: " << temp->eventPtr->get_time() << ", Type: " << temp->eventPtr->get_eventType() << '\n';
        
        temp = temp->nextEventPtr;
    }

    std::cout << '\n';
}

std::string EventList::get_eventType() const
{
    // Check for empty EventList
    if (!nextEventPtr)
    {
        std::cout << "EventList is empty, no more events.\n";
        return "EMPTY";
    }

    EventList* eventNode = nextEventPtr;

    return eventNode->eventPtr->get_eventType();
}

int EventList::getEventListLength()
{
    return s_EventListLength;
}

bool EventList::isEmpty()
{
    if (s_EventListLength == 0)
    {
        return true;
    }

    return false;
}