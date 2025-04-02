#include <iostream>
#include <Windows.h>
#include "include\MiniDictionaryOperations.h"


struct  Args
{
	std::string file;
};

Args ParseArgs(int argc, char** argv)
{
	Args args;
	if (argc == 2)
	{
		args.file = argv[1];
	}
	else
	{
		throw std::invalid_argument("Invalid input\n");
	}
	return args;
}

int main(int argc, char** argv)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	try
	{
		Args args = ParseArgs(argc, argv);
		Dictionary dictionary = LoadDictionary(args.file);
		UseDictionary(dictionary, args.file);
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	return 0;
}