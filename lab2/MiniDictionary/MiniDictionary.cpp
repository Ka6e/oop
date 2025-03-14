#include <iostream>
#include <format>
#include <string>
#include <fstream>
#include <Windows.h>
#include <map>

const char DETERMINATOR = ' ';

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

std::multimap<std::string, std::string> FillMap(std::string file)
{	
	std::multimap<std::string, std::string> dictionary;
	std::ifstream input(file);
	if (!input)
	{
		return dictionary;
	}

	std::string line;
	std::pair<std::string, std::string> pair;
	size_t pos;
	while (std::getline(input, line))
	{
		pos = line.find(DETERMINATOR, 0);
		pair.first = line.substr(0, pos);
		pair.second = line.substr(pos + 1);
		dictionary.insert(pair);
	}
	if (!input.eof() || input.bad())
	{
		throw std::runtime_error("File reading failure\n");
	}
	return dictionary;
}


void UseDictionary(std::multimap<std::string, std::string> dictionary)
{
	std::string line;
	
	do
	{
		std::getline(std::cin, line);
		bool isFound = false;
		for (const auto& [key, value] : dictionary)
		{
			if (key == line)
			{
				std::cout << value << " ,";
				isFound = true;
			}
		}
		std::cout << std::endl;
		if (!isFound || line != "...")
		{
			std::cout << std::format("Неизвестное слово {}. Введите перевод или пустую строку для отказа.", line);
			std::string answer;
			std::getline(std::cin, answer);
			if (answer == "\n")
			{
				std::cout << std::format("Слово {} проигнорировано", line);
			}
			else
			{

			}
		}
	} while (line != "...");
}


int main(int argc, char** argv)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	try
	{
		Args args = ParseArgs(argc, argv);
		std::multimap dictionary = FillMap(args.file);
		std::cout << 1;
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	return 0;
}