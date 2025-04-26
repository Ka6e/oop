#include <iostream>
#include "../Calculator/include/CalculatorManager.h"

int main()
{
	try
	{
		CalculatorManager handler;
		handler.RunCalculator();
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	return 0;
}

