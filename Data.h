#ifndef DATA_H
#define DATA_H

struct InputData
{
public:
	int avgClientArrival;
	int numOfRegisters;
	int avgServiceTime;
	int simulationTime;

public:
	InputData() = default;

	void printInputData() const;
};

struct OutputData
{
public:
	std::vector<float> occupiedRegisterTimePrcntg;
	std::vector<int> clientsServicedPerReg;
	std::vector<float> avgQueueLengthPerReg;
	std::vector<int> maxQueueLengthPerReg;
	std::vector<float> avgQueueWaitingTimePerReg;

public:
	OutputData(int numOfRegisters);

	void PrintOutputData() const;
};

#endif // !DATA_H