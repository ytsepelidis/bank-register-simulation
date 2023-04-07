#include "Functions.h"
#include "Data.h"

void InputData::printInputData() const
{
	std::cout << "Average time between each client arrival: " << avgClientArrival << '\n';
	std::cout << "Number of registers: " << numOfRegisters << '\n';
	std::cout << "Average service time: " << avgServiceTime << '\n';
	std::cout << "Total simulation time: " << simulationTime << '\n';
}

OutputData::OutputData(int numOfRegisters)
{
	occupiedRegisterTimePrcntg.reserve(numOfRegisters);
	clientsServicedPerReg.reserve(numOfRegisters);
	avgQueueLengthPerReg.reserve(numOfRegisters);
	maxQueueLengthPerReg.reserve(numOfRegisters);
	avgQueueWaitingTimePerReg.reserve(numOfRegisters);
}

void OutputData::PrintOutputData() const
{
	std::cout << "occupiedRegisterTimePrcntg: ";
	for (const float& x : occupiedRegisterTimePrcntg)
	{
		std::cout << x << "-";
	}
	std::cout << "\n";

	std::cout << "clientsServicedPerReg: ";
	for (const int& x : clientsServicedPerReg)
	{
		std::cout << x << "-";
	}
	std::cout << "\n";

	std::cout << "avgQueueLengthPerReg: ";
	for (const float& x : avgQueueLengthPerReg)
	{
		std::cout << x << "-";
	}
	std::cout << "\n";

	std::cout << "maxQueueLengthPerReg: ";
	for (const int& x : maxQueueLengthPerReg)
	{
		std::cout << x << "-";
	}
	std::cout << "\n";

	std::cout << "avgQueueWaitingTimePerReg: ";
	for (const float& x : avgQueueWaitingTimePerReg)
	{
		std::cout << x << "-";
	}
	std::cout << "\n";
}