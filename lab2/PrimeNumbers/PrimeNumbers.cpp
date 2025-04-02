#include "include\PrimeNumbersOperations.h"
#include <iostream>
#include <chrono>

struct Args
{
	int number;
};

Args ParseArgs(int argc, char** argv)
{
	Args args;
	if (argc != 2)
	{
		throw std::invalid_argument("Invalid count of arguments\n");
	}
	try
	{
		args.number = std::stoi(argv[1]);
	}
	catch (const std::exception& ex)
	{
		throw std::invalid_argument("Invalid argument\n");
	}

	return args;
}


int main(int argc, char** argv)
{
	Args args;
	std::set<int> primes{};
	try
	{
		args = ParseArgs(argc, argv);
		primes = GeneratePrimeNumbersSet(args.number);
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	return 0;
}
