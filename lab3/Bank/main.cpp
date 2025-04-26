#include <iostream>
#include <string>
#include "include/Simulation.h"

struct Args
{
	int steps;
};

Args Parse(int argc, char** argv)
{
	Args args;
	if (argc == 1)
	{
		std::cin >> args.steps;
	}
	else 
	{
		try
		{
			args.steps = std::stoi(argv[1]);
			if (args.steps < 0)
			{
				throw std::invalid_argument("Invalid number of steps");
			}
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
 		}
	}
	return args;
}

int main(int argc, char** argv)
{
	Args args = Parse(argc, argv);

	try
	{
		Simulation sim(11000);
		sim.Run(args.steps);
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}

}
