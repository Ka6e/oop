#include "include\StringOperations.h"

State CompareStrings(std::string& str1)
{
	if (str1 == ENGINE_ON)
	{
		return State::ENGINE_ON;
	}
	else if (str1 == ENGINE_OFF)
	{
		return State::ENGINE_OFF;
	}
	else if (str1 == SET_GEAR)
	{
		return State::SET_GEAR;
	}
	else if (str1 == SET_SPEED)
	{
		return State::SET_SPEED;
	}
	else if (str1 == INFO)
	{
		return State::INFO;
	}
	else if (str1 == QUIT)
	{
		return State::QUIT;
	}
	return State::UNKNOWN;
}

void Trim(std::string& str1, std::string& str2)
{
	auto pos = str1.find(' ');
	if (pos == std::string::npos)
	{
		str2.clear();
		return;
	}

	str2 = str1.substr(pos + 1);
	str1 = str1.substr(0, pos);
}

std::string ToLower(std::string& line)
{
	std::transform(line.begin(), line.end(), line.begin(), tolower);
	return line;
}
