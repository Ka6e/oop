#include <iostream>
#include <string>
#include "include\URLParserOperations.h"

int main()
{	
	std::string url, host, document;
	Protocol protocol;
	int port;

	while (std::getline(std::cin, url))
	{
		if (!ParseURL(url, protocol, port,host,document))
		{
			std::cout << "ERROR" << std::endl;
			break;
		}
		PrintInfo(url, port, host, document);
	}

	return 0;
}
