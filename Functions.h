#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <fstream>
#include <cmath>

#include "EventList.h"
#include "Event.h"
#include "Client.h"
#include "Queue.h"
#include "Data.h"
#include "Bank.h"

void ReadingInputFile(struct InputData& in);
void WritingOutputFile(const struct InputData& in, struct OutputData& out);
void BankRegisterSim();
void CalculateArrivals(const struct InputData& in, std::vector<int>& t);

#endif // !FUNCTIONS_H