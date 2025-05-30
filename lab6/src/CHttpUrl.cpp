#include "../include/CHttpUrl.h"
#include "../include/CUrlParsingError .h"
#include <regex>

CHttpUrl::CHttpUrl(std::string const& url) : m_url(url)
{
	ParseUrl(url);
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
{
	m_protocol = ValidateProtocol(protocol);
	m_domain = ValidateDomain(domain);
	m_document = ValidateDocument(document);
	m_port = GetDefaultPort(protocol);
	m_url = CollectUrl();
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, int port)
{
	m_domain = ValidateDomain(domain);
	m_document = ValidateDocument(document);
	m_protocol = ValidateProtocol(protocol);
	ValidatePort(port);
	m_port = port;
	m_url = CollectUrl();
}

std::string CHttpUrl::GetURL() const
{
	return m_url;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

void CHttpUrl::ValidatePort(int port) const
{
	if (port < minPort || port > maxPort)
	{
		throw CUrlParsingError("Port must be between 1 and 65535");
	}
}

Protocol CHttpUrl::ValidateProtocol(Protocol protocol)
{
	if (protocol == Protocol::HTTP)
	{
		return Protocol::HTTP;
	}
	if (protocol == Protocol::HTTPS)
	{
		return Protocol::HTTPS;
	}
	throw CUrlParsingError("Invalid protocol");
}

unsigned short CHttpUrl::GetDefaultPort(Protocol protocol) const 
{
	return protocol == Protocol::HTTP ? 80 : 443;
}

void CHttpUrl::ParseUrl(const std::string& url)
{
	std::regex urlRegex(R"(^([a-zA-Z]+)://([^:/]+)(?::(\d+))?(?:/(.*))?$)");
	std::smatch match;

	if (!std::regex_match(url, match, urlRegex) || match.size() < 2)
	{
		throw CUrlParsingError("Invalid URL format");
	}

	std::string protocol = match[1].str();
	std::string domain = match[2].str();
	std::string port = match[3].str();
	std::string document = match[4];

	m_protocol = ValidateProtocol(protocol);
	m_domain = ValidateDomain(domain);
	m_document = ValidateDocument(document);
	if (port.empty())
	{
		m_port = GetDefaultPort(m_protocol);
	}
	else
	{
		try
		{
			m_port = static_cast<unsigned short>(std::stoi(port));
			ValidatePort(m_port);
		}
		catch (const std::exception&)
		{
			throw CUrlParsingError("Invalid port");
		}
	}
	m_url = CollectUrl();
}

Protocol CHttpUrl::ValidateProtocol(const std::string& protocol)
{
	std::string lowerCaseProtocol = protocol;
	std::transform(lowerCaseProtocol.begin(), lowerCaseProtocol.end(), lowerCaseProtocol.begin(), ::tolower);

	if (lowerCaseProtocol == "http")
	{
		return Protocol::HTTP;
	}
	if (lowerCaseProtocol == "https")
	{
		return Protocol::HTTPS;
	}

	throw CUrlParsingError("Invalid protocol");
}

std::string CHttpUrl::ValidateDomain(const std::string& domain)
{
	if (domain.empty())
	{
		throw CUrlParsingError("Domain cannot be empty");
	}
	if (domain.size() > 253)
	{
		throw CUrlParsingError("Domain name too long");
	}
	std::regex domainRegex(R"(^([a-zA-Z0-9]([a-zA-Z0-9\-]{0,61}[a-zA-Z0-9])?\.)+[a-zA-Z]{2,63}$)");

	if (!std::regex_match(domain, domainRegex))
	{
		throw CUrlParsingError("Invalid domain format");
	}
	return domain;
}

std::string CHttpUrl::ValidateDocument(const std::string& document)
{
	if (document.empty())
	{
		return "/";
	}
	else if (document[0] != '/')
	{
		return "/" + document;
	}
}

std::string CHttpUrl::CollectUrl() const
{
	std::string url = (m_protocol == Protocol::HTTP ? "http://" : "https://");
	url += m_domain;
	if (m_port != GetDefaultPort(m_protocol))
	{
		url += ":" + std::to_string(m_port);
	}
	url += m_document;
	return url;
}

