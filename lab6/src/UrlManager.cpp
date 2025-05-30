#include "../include/UrlManager.h"
#include "../include/CUrlParsingError .h"

void UrlManager::ReadUrls()
{
	std::string url;
	while (std::getline(std::cin, url))
	{
		try 
		{
			m_urls.push_back(std::make_shared<CHttpUrl>(url));
		}
		catch(const CUrlParsingError& e)
		{
			std::cout << e.what() << std::endl;
			continue;
		}
	}
}

void UrlManager::PrintUrls() const
{
	for (const auto& url: m_urls)
	{
		std::cout << "URL: " << url->GetURL() << std::endl
			<< "Protocol: " << (url->GetProtocol() == Protocol::HTTP ? "http" : "https") << std::endl
			<< "Domain: " << url->GetDomain() << std::endl
			<< "Port: " << url->GetPort() << std::endl
			<< "Document: " << url->GetDocument() << std::endl;
		std::cout << std::endl;
	}
}

