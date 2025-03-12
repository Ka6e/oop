#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

struct Args
{
	std::string input;
	std::string output;
	std::string search;
	std::string source;
	std::string replacement;
};

void PrintHelp()
{
	std::cout << "Usage reference\n"
			  << "With arguments: <input file> <output file> <search string> <replace string>\n"
			  << "If run without arguments: <search string> <replace string> <source string>\n";
}

Args ParseArguments(int argumentCount,char* argumentValue[])
{
	Args args;
	if (argumentCount == 1)
	{
		if (!std::getline(std::cin, args.search) || std::cin.eof())
		{
			throw std::runtime_error("Error: Failed to read search string from input.\n");
		}
		if (!std::getline(std::cin, args.replacement) || std::cin.eof())
		{
			throw std::runtime_error("Error: Failed to read replacement string from input.\n");
		}
		while (!std::getline(std::cin, args.source) || std::cin.eof())
		{
			throw std::runtime_error("Error: Failed to read source string from input.\n");
		}

		if (args.source.empty())
		{
			args.source = args.replacement;
			args.replacement = args.search;
			args.search.clear();
		}
	}
	else if (argumentCount == 2)
	{
		if (std::string(argumentValue[1]) == "-h")
		{
			PrintHelp();
			exit(0);
		}
		else
		{
			throw std::invalid_argument("Error: Invalid argument.Use -h for help.\n");
		}
	}
	else if (argumentCount == 5)
	{
		args.input = argumentValue[1];
		args.output = argumentValue[2];
		args.search = argumentValue[3];
		args.replacement = argumentValue[4];
	}
	else
	{
		throw std::runtime_error("Error: Incorrect number of arguments. Use -h for help.\n");
	}

	return args;
}



std::string ReplaceString(const std::string& subject, const std::string& searchString, const std::string& replacementString)
{
	if (searchString.empty())
	{
		return subject;
	}

	size_t pos = 0;

	std::string result;
	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);

		if (foundPos == std::string::npos)
		{
			result.append(subject.substr(pos));
			return result;
		}

		result.append(subject.substr(pos, foundPos - pos) + replacementString);
		pos = foundPos + searchString.length();
	}

	return result;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output, 
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;
	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << std::endl;

		if (!output.flush())
		{
			throw std::runtime_error("Failed to write data to output file\n");
		}
	}
	if (input.fail() && !input.eof())
	{
		throw std::runtime_error("Stream read error occured\n");
	}
	if (input.bad())
	{
		throw std::runtime_error("Failed read data from stream\n");
	}

}


void CopyFileWithReplacement(std::string& inputFile, std::string& outputFile, 
	const std::string& searchString, const std::string& replacementString) 
{
	std::ifstream input(inputFile);
	if (!input)
	{
		throw std::runtime_error("Failed to read data from \n");
	}
	if (input.bad())
	{
		throw std::runtime_error("Critical error input file\n");
	}
	std::ofstream output(outputFile);
	if (!output.is_open() || output.fail() || output.bad())
	{
		throw std::runtime_error("Failed to write data to\n");
	}
	CopyStreamWithReplacement(input, output, searchString, replacementString);
}

int main(int argc, char* argv[])
{
	try
	{
		Args args = ParseArguments(argc, argv);
		if (argc == 2)
		{
			std::istringstream stringStream(args.source);
			CopyStreamWithReplacement(stringStream, std::cout, args.search, args.replacement);
		}
		else if (argc == 5)
		{
			CopyFileWithReplacement(args.input, args.output, args.search, args.replacement);
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
		return 1;
	}	
	return 0;
}
