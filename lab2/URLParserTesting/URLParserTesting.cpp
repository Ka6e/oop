#define CATCH_CONFIG_MAIN
#include "../URLParser/include/URLParserOperations.h"
#include "../../Catch2/catch.hpp"

void CheckParseUrl(const std::string& url, bool expectedResult, Protocol expectedProtocol, 
	int expectedPort, const std::string& expectedHost, const std::string& expectedDocument)
{
	std::string host, document;
	Protocol protocol;
	int port;

	CHECK(ParseURL(url, protocol, port, host, document) == expectedResult);
	if (expectedResult)
	{
		CHECK(host == expectedHost);
		CHECK(protocol == expectedProtocol);
		CHECK(port == expectedPort);
		CHECK(document == expectedDocument);
	}
}

TEST_CASE("Valid URLs without port")
{
	CheckParseUrl("http://example.com", true, Protocol::HTTP, 80, "example.com", "");
	CheckParseUrl("https://my.site.org", true, Protocol::HTTPS, 443, "my.site.org", "");
	CheckParseUrl("ftp://ftp.example.net", true, Protocol::FTP, 21, "ftp.example.net", "");

}

TEST_CASE("Valid URLs with explicit port")
{
	CheckParseUrl("http://example.com/index.html", true, Protocol::HTTP, 80, "example.com", "index.html");
	CheckParseUrl("https://site.org/docs/report.pdf", true, Protocol::HTTPS, 443, "site.org", "docs/report.pdf");
	CheckParseUrl("ftp://ftp.example.com/files/archive.zip", true, Protocol::FTP, 21, "ftp.example.com", "files/archive.zip");
}

TEST_CASE("Valid URLs with query parameters and fragments")
{
	CheckParseUrl("http://example.com/page?query=1&lang=en#top", true, Protocol::HTTP, 80, "example.com", "page?query=1&lang=en#top");
	CheckParseUrl ("https://secure.site.org/search?q=test#results", true, Protocol::HTTPS, 443, "secure.site.org", "search?q=test#results");
}

TEST_CASE("Invalid URLs") 
{
	CheckParseUrl("htp://wrongprotocol.com", false, Protocol::HTTP, 0, "", "");
	CheckParseUrl("http//missingcolon.com", false, Protocol::HTTP, 0, "", "");
	CheckParseUrl("http:/missing_slash.com", false, Protocol::HTTP, 0, "", "");
	CheckParseUrl("://missing_protocol.com", false, Protocol::HTTP, 0, "", "");
	CheckParseUrl("http://", false, Protocol::HTTP, 0, "", "");
	CheckParseUrl("http://:8080", false, Protocol::HTTP, 0, "", "");
	CheckParseUrl("http://invalid.com:-1", false, Protocol::HTTP, 0, "", "");
	CheckParseUrl("http://invalid.com:70000", false, Protocol::HTTP, 0, "", "");
}