#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

template<typename T>
class Queue
{
private:
    static int s_maxQueueLength;
	static int s_queueLength;
	static int s_queueLengthAccum;
    static int s_queueMovement;

	T* memberPtr;
	Queue<T>* nextMemberPtr;

public:
	Queue();
	~Queue();

	void enqueue();
	void dequeue();
	void printQueue() const;
    T* get_clientPtr();
    
    static int getMaxQueueLength();
    static float getAvgQueueLength();
    static bool isEmpty();
};

template<typename T>
int Queue<T>::s_maxQueueLength = 0;

template<typename T>
int Queue<T>::s_queueLength = -1;

template<typename T>
int Queue<T>::s_queueLengthAccum = 0;

template<typename T>
int Queue<T>::s_queueMovement = 0;

template<typename T>
inline Queue<T>::Queue()
{
    if (s_queueLength == -1)
    {
	    memberPtr = nullptr;
	    nextMemberPtr = nullptr;
        s_queueLength = 0;
    }
    else
    {
        memberPtr = new T();

        // Error check
        if (!memberPtr)
        {
            std::cout << "Error creating new Client for Queue node.\n";
        }

        s_queueLength += 1;
        nextMemberPtr = nullptr;
    }    

    // For max Queue length
    if (s_queueLength > s_maxQueueLength)
    {
        s_maxQueueLength = s_queueLength;
    }
}

template<typename T>
inline Queue<T>::~Queue()
{
	s_queueLength -= 1;
    delete memberPtr;
}

template<typename T>
inline void Queue<T>::enqueue()
{
    Queue<T>* newQueueNode = new Queue<T>();

    // Error check
    if (!newQueueNode)
    {
        std::cout << "Error creating new Queue node.\n";
    }

    // If Queue is empty
    if (!nextMemberPtr)
    {
        nextMemberPtr = newQueueNode;
        return;
    }
    
    Queue<T>* temp = nextMemberPtr;

    // Traversing to end of Queue
    while (temp->nextMemberPtr != nullptr)
    {
        temp = temp->nextMemberPtr;
    }

    // Adding new Queue node
    temp->nextMemberPtr = newQueueNode;

    // For avg queue length
    s_queueLengthAccum += s_queueLength;
    s_queueMovement += 1;
}

template<typename T>
inline void Queue<T>::dequeue()
{
    Queue<T>* queueNodeToRemove = nextMemberPtr;

    // Check for empty Queue
    if (!nextMemberPtr)
    {
        std::cout << "Queue is empty, no more clients to remove.\n";
        return;
    }

    // Queue head node points to next node
    nextMemberPtr = queueNodeToRemove->nextMemberPtr;

    // Deleting node
    delete queueNodeToRemove;

    // For avg queue length
    s_queueLengthAccum += s_queueLength;
    s_queueMovement += 1;
}

template<typename T>
inline void Queue<T>::printQueue() const
{
    Queue<T>* temp = nextMemberPtr;

    // If Queue is empty
    if (!nextMemberPtr)
    {
        std::cout << "Queue is empty.\n";
        return;
    }

    // Traverse and print the queue
    std::cout << "Printing Queue:\n";

    while (temp != nullptr)
    {
        std::cout << "ClientID: " << temp->memberPtr->get_clientID() << '\n';
        
        temp = temp->nextMemberPtr;
    }

    std::cout << '\n';
}

template<typename T>
inline T* Queue<T>::get_clientPtr()
{
    Queue<T>* temp = nextMemberPtr;

    return temp->memberPtr;
}

template<typename T>
inline int Queue<T>::getMaxQueueLength()
{
    return s_maxQueueLength;
}

template<typename T>
inline float Queue<T>::getAvgQueueLength()
{
    return (float) s_queueLengthAccum / s_queueMovement;
}

template<typename T>
inline bool Queue<T>::isEmpty()
{
    if (s_queueLength == 0)
    {
        return true;
    }

    return false;
}

#endif // !QUEUE_H