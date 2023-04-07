#include "Functions.h"

void ReadingInputFile(struct InputData& in)
{
	std::array<int, 4> inputFileData = { 0 };
	std::fstream file;
	std::string filename;

	// Reading filename
	std::cout << "Please enter the input file you want to open (without .txt): ";
	std::cin >> filename;
	filename += ".txt";

	// Opening file in read mode
	file.open(filename, std::ios::in);

	if (!file.is_open())
	{
		std::cout << "Unable to open file. Exiting program . . .\n";
		exit(1);
	}

	// Reading input file line by line
	std::string line;
	int i = 0;

	while (getline(file, line))
	{
		try
		{
			inputFileData[i] = stoi(line);
			i += 1;
		}
		catch (std::invalid_argument const& ex)
		{
			std::cout << "std::invalid_argument::what(): " << ex.what() << '\n';
			std::cout << "Invalid stoi() argument. Exiting program . . .\n";

			exit(1);
		}
	}

	// Checking if input file is written correctly
	if (i != 4)
	{
		std::cout << "Input file '" << filename << "' is written incorrectly. Exiting program . . .\n";
		exit(1);
	}

	// Storing data to input data struct
	in.avgClientArrival = inputFileData[0];
	in.numOfRegisters = inputFileData[1];
	in.avgServiceTime = inputFileData[2];
	in.simulationTime = inputFileData[3];

	std::cout << "File '" << filename << "' was found and read correctly.\n";
	std::cout << '\n';

	// Closing file
	file.close();
}

void WritingOutputFile(const struct InputData& in, struct OutputData& out)
{
	int reg = 0;
	std::fstream file;
	std::string filename;

	// Naming file
	std::cout << "Please enter a name for the output file (without .txt): ";
	std::cin >> filename;
	filename += ".txt";
	
	// Opening file in write mode
	file.open(filename, std::ios::out);
	
	if (!file.is_open())
	{
	    std::cout << "Unable to open file. Exiting program . . .\n";
	    exit(1);
	}
	
	// Writing to the output file
	file << "Percentage of time of occupied registers:\n";
	for (const float& val : out.occupiedRegisterTimePrcntg)
	{
		reg += 1;
		file << "Register n. " << reg << ": " << val << '\n';
	}
	file << "\n";
	reg = 0;
	
	file << "Clients serviced for each register:\n";
	for (const int& val : out.clientsServicedPerReg)
	{
		reg += 1;
		file << "Register n. " << reg << ": " << val << '\n';
	}
	file << "\n";
	reg = 0;
	
	file << "Average queue length for each register:\n";
	for (const float& val : out.avgQueueLengthPerReg)
	{
		reg += 1;
		file << "Register n. " << reg << ": " << val << '\n';
	}
	file << "\n";
	reg = 0;
		
	file << "Maximum queue length for each register:\n";
	for (const int& val : out.maxQueueLengthPerReg)
	{
		reg += 1;
		file << "Register n. " << reg << ": " << val << '\n';
	}
	file << "\n";
	reg = 0;
		
	file << "Average queue waiting time for each register:\n";
	for (const float& val : out.avgQueueWaitingTimePerReg)
	{
		reg += 1;
		file << "Register n. " << reg << ": " << val << '\n';
	}
	file << "\n";
	reg = 0;
	
	// Closing file
	file.close();

	std::cout << "Successfully stored results in output file '" << filename << "'.\n";
}

void BankRegisterSim()
{
	EventList events;
	std::vector<int> t;
	struct InputData in = {};
	ReadingInputFile(in);
	struct OutputData out(in.numOfRegisters);
	
	// Calculating ARRIVAL Events in advance
	CalculateArrivals(in, t);

	// Pushing timed ARRIVAL Events in EventList
	for (const int& time : t)
	{
		events.enqueue(time, "ARRIVAL");
	}

	// Creating Bank object with 1 waiting Queue and simulating service
	Bank b1(in.numOfRegisters);
	b1.simulateService(in, out, events);

	// Writing results to output file
	WritingOutputFile(in, out);
}

void CalculateArrivals(const struct InputData& in, std::vector<int>& t)
{
	srand((unsigned)time(nullptr));

	t.reserve(in.simulationTime);
	int l = in.avgClientArrival;
	// float r = 0.0f;
	float r = (float)rand() / RAND_MAX;
	float cur_t = 0.0f;
	float prev_t = 0.0f;
	int res = 0;

	// 1st client at t0 = 0s
	t.push_back(res);

	// Calculating arrivals using Poisson distribution
	while (res <= in.simulationTime)
	{
		// r = (float)rand() / RAND_MAX;
		cur_t = (prev_t - log(r) / l);
		
		// Tried to get scattered times in minutes
		// For some reason (maybe rand()), i would get less clients as i run the program multiple times
		// So i would try different values, like 3.3f, 33.3f, 63.3f, no reasoning behind the numbers
		res = (int)ceil(cur_t * 3.3f);

		t.push_back(res);
		prev_t = cur_t;
	}

	// Removing last timestamp
	t.pop_back();
}