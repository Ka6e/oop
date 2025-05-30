#include <iostream>
#include "./include/CDate.h"

int main()
{
	CDate date = CDate();
	while (true)
	{
		try
		{
			std::cin >> date;
		}
		catch (std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}
		std::cout << date << std::endl;
	}
	return 0;
}