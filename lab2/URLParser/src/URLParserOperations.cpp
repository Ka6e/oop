#include "../include/URLParserOperations.h"
#include <iostream>
#include <regex>
#include <algorithm>

const int HTTP = 80;
const int HTTPS = 433;
const int FTP = 21;
const int MIN_PORT = 1;
const int MAX_PORT = 65535;

bool SetProtocol(const std::string& protocolStr, Protocol& protocol, int& port)
{
	if (protocolStr == "http" || protocolStr == "HTTP")
	{
		protocol = Protocol::HTTP;
		port = 80;
	}
	else if (protocolStr == "https" || protocolStr == "HTTPS")
	{
		protocol = Protocol::HTTPS;
		port = 443;
	}
	else if (protocolStr == "ftp" || protocolStr == "FTP")
	{
		protocol = Protocol::FTP;
		port = 21;
	}
	else
	{
		return false;
	}
	return true;
}

bool SetPort(const std::string& str, int& port)
{
	if (!str.empty())
	{
		try
		{
			port = std::stoi(str);
			if (port < 1 || port > 65535)
			{
				return false;
			}
		}
		catch (const std::exception&)
		{
			return false;
		}
	}
	return true;
}

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	std::regex urlRegex(R"(^([a-zA-Z]+)://([^:/]+)(?::(\d+))?(?:/(.*))?$)");
	std::smatch match;

	if (!std::regex_match(url, match, urlRegex) || match.size() < 2)
	{
		return false;
	}

	std::string protocolStr = match[1].str();
	host = match[2].str();
	document = match[4].matched ? match[4].str() : "";

	if (protocolStr.empty() && host.empty())
	{
		return false;
	}
	std::transform(protocolStr.begin(), protocolStr.end(), protocolStr.begin(), ::tolower);	
	if (!SetProtocol(protocolStr, protocol, port))
	{
		return false;
	}
	if (!SetPort(match[3].str(), port))
	{
		return false;
	}
	return true;
}

void PrintInfo(const std::string& url, int port, const std::string& host, const std::string& document)
{
	std::cout << url << std::endl
		<< "HOST: " << host << std::endl
		<< "PORT: " << port << std::endl
		<< "DOC: " << document << std::endl;
}
