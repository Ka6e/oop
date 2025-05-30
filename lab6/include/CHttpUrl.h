#pragma once
#include <string>

enum class Protocol
{
	HTTP,
	HTTPS
};

class CHttpUrl
{
public:
	CHttpUrl(std::string const& url);
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP);
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		int port);
	std::string GetURL()const;
	std::string GetDomain()const;
	std::string GetDocument()const;
	Protocol GetProtocol()const;
	unsigned short GetPort()const;

private:
	std::string m_url;
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;
	std::string CollectUrl() const;
	void ValidatePort(int port) const;
	Protocol ValidateProtocol(Protocol protocol);
	Protocol ValidateProtocol(const std::string& protocol);
	std::string ValidateDomain(const std::string& domain);
	std::string ValidateDocument(const std::string& document);
	unsigned short GetDefaultPort(Protocol protocol) const;
	void ParseUrl(const std::string& url);
	static const unsigned short minPort = 1;
	static const unsigned short maxPort = 65535;
};