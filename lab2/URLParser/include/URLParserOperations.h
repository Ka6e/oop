#pragma once
#include <string>

enum class Protocol
{
    HTTP,
    HTTPS,
    FTP
};

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document);
void PrintInfo(const std::string& url, int port, const std::string& host, const std::string& document);
