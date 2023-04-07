#ifndef BANK_H
#define BANK_H

#include <vector>
#include <sstream>

#include "EventList.h"
#include "Register.h"
#include "Queue.h"
#include "Data.h"

class Bank
{
private:
	// Clock
	std::vector<Register> bankRegister;
	Queue<Client> queue;
	// Random data

public:
	Bank(int numOfRegisters);

	void simulateService(const struct InputData in, struct OutputData& out, EventList& events);
	void serviceClient(const struct InputData in, EventList& events, Client* client, int regPos);
	void calculateResults(const struct InputData in, struct OutputData& out);
};

#endif // !BANK_H