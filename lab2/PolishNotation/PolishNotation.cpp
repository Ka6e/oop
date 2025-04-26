#include "../PolishNotation/include/PolishNotationOperations.h"

int main()
{
	try
	{
		std::cout << Evaluate() << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}