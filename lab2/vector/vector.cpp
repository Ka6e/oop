#include "VectorOperations.h"
#include <iostream>

int main()
{
	try
	{
		DoubleVector vector = ReadNumbers();
		ProcessNumbers(vector);
		Sort(vector);
		PrintSortedNumbers(vector);
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	return 0;
}
