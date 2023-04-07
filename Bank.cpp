#include "Bank.h"

Bank::Bank(int numOfRegisters)
{
	bankRegister.reserve(numOfRegisters);

	for (int i = 0; i < numOfRegisters; i++)
	{
		bankRegister.emplace_back();
	}
}

void Bank::simulateService(const struct InputData in, struct OutputData& out, EventList& events)
{
	int freeRegPos = -1;
	int arbRegPos = -1;
	int regNum = 0;
	std::string regChar;

	events.printEventList();

	while (!events.isEmpty())
	{
		if (events.get_eventType() == "ARRIVAL")
		{
			std::cout << "Event is of type: " << events.get_eventType() << ".\n";

			// Pick register arbitrarily (1st free register)
			for (int i = 0; i < bankRegister.size(); i++)
			{
				if (bankRegister[i].isFree())
				{
					arbRegPos = i;
					break;
				}
				else
				{
					// Throwaway register position
					arbRegPos = 0;
				}
			}
			
			if (queue.isEmpty() && bankRegister[arbRegPos].isFree())
			{
				std::cout << "Queue is empty AND arbitrary register " << arbRegPos << " is free.\n";

				// Moving client to free register
				Client* client = new Client;

				// Error checking
				if (!client)
				{
					std::cout << "Error creating client to insert in free register.\n";
					exit(EXIT_FAILURE);
				}

				// Servicing new client
				serviceClient(in, events, client, arbRegPos);
			}
			else
			{
				std::cout << "Queue is not empty OR arbitrary register " << arbRegPos << " is not free.\n";

				// Enqueueing Client in Queue
				queue.enqueue();
			}

			std::cout << "About to remove '" << events.get_eventType() << "' event.\n";

			// Removing Event from EventList
			events.dequeue();
		}
		else
		{
			// SERVICE_COMPLETION_n Event type
			regChar = events.get_eventType().back();
			regNum = stoi(regChar);

			std::cout << "Event is of type: " << events.get_eventType() << " from register " << regNum << ".\n";

			// Removing client at correct register
			bankRegister[regNum].set_clientPtr(nullptr);

			// If queue isn't empty, next client in queue moves to the register
			if (!queue.isEmpty())
			{
				Client* client = queue.get_clientPtr();
				
				// Servicing new client
				serviceClient(in, events, client, regNum);

				// Dequeueing Client from Queue
				queue.dequeue();
			}

			std::cout << "About to remove '" << events.get_eventType() << "' event.\n";

			// Removing Event from EventList
			events.dequeue();
		}
		
		std::cout << '\n';
	}

	// Calculating results
	this->calculateResults(in, out);
}

void Bank::serviceClient(const struct InputData in, EventList& events, Client* client, int regPos)
{
	float r = 0.0f;
	int serviceTime = 0;
	std::string serviceCompStr = "SERVICE_COMPLETION_";
	std::string str;
	std::string strNum;
	std::stringstream ss;

	// Adding client at correct register
	bankRegister[regPos].set_clientPtr(client);

	// Calculating service time with exponential distribution
	r = (float)rand() / RAND_MAX;
	serviceTime = (int)ceil(-in.avgServiceTime * log(r));

	// Setting service time
	bankRegister[regPos].set_serviceTime(serviceTime);

	// Creating SERVICE_COMPLETION_n object
	ss << regPos;
	ss >> strNum;
	str = serviceCompStr + strNum;

	std::cout << "Created " << str << " event.\n";

	// Enqueueing SERVICE_COMPLETION_n Event
	events.enqueue(0, str);

	// Clearing strings and stringstream
	str.clear();
	strNum.clear();
	ss.clear();
}

void Bank::calculateResults(const struct InputData in, struct OutputData& out)
{
	int totalTimeAccum = 0;
	int totalClientsServiced = 0;

	for (const auto& reg : bankRegister)
	{
		out.occupiedRegisterTimePrcntg.push_back((float)reg.get_timeAccum() / in.simulationTime);
	}

	for (const auto& reg : bankRegister)
	{
		out.clientsServicedPerReg.push_back(reg.get_clientsServiced());
	}

	out.avgQueueLengthPerReg.push_back(queue.getAvgQueueLength());

	out.maxQueueLengthPerReg.push_back(queue.getMaxQueueLength());

	for (const auto& reg : bankRegister)
	{
		totalTimeAccum += reg.get_timeAccum();
		totalClientsServiced += reg.get_clientsServiced();
	}

	out.avgQueueWaitingTimePerReg.push_back((float)totalTimeAccum / totalClientsServiced);
}