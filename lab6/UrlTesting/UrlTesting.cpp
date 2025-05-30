#define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "../include/CHttpUrl.h"
#include "../include/CUrlParsingError .h"

TEST_CASE("Parse valid URL")
{
	CHttpUrl url("https://myexample.com:8080/path/to/doc");
	CHECK(url.GetProtocol() == Protocol::HTTPS);
	CHECK(url.GetDomain() == "myexample.com");
	CHECK(url.GetPort() == 8080);
	CHECK(url.GetDocument() == "/path/to/doc");
	CHECK(url.GetURL() == "https://myexample.com:8080/path/to/doc");
}

TEST_CASE("Parse valid URL without port")
{
	CHttpUrl url("http://myexample.com/document");
	CHECK(url.GetProtocol() == Protocol::HTTP);
	CHECK(url.GetDomain() == "myexample.com");
	CHECK(url.GetPort() == 80);
	CHECK(url.GetDocument() == "/document");
	CHECK(url.GetURL() == "http://myexample.com/document");

}
TEST_CASE("Constructor with 4 parameters")
{
	CHttpUrl url("example.com", "doc", Protocol::HTTP, 456);
	CHECK(url.GetDomain() == "example.com");
	CHECK(url.GetDocument() == "/doc");
	CHECK(url.GetProtocol() == Protocol::HTTP);
	CHECK(url.GetPort() == 456);
	CHECK(url.GetURL() == "http://example.com:456/doc");
}

TEST_CASE("Parse case-insensitive protocol")
{
	CHttpUrl url("HtTpS://myexample.com");
	CHECK(url.GetProtocol() == Protocol::HTTPS);
	CHECK(url.GetURL() == "https://myexample.com/");
}

TEST_CASE("Parse valid URL without document")
{
	CHttpUrl url("HtTpS://myexample.com");
	CHECK(url.GetDocument() == "/");
	CHECK(url.GetURL() == "https://myexample.com/");
}

TEST_CASE("Constructor with default protocol")
{
	CHttpUrl url("myexample.com", "doc");
	CHECK(url.GetDomain() == "myexample.com");
	CHECK(url.GetDocument() == "/doc");
	CHECK(url.GetProtocol() == Protocol::HTTP);
	CHECK(url.GetPort() == 80);
}

TEST_CASE("Constructor with custom port")
{
	CHttpUrl url("myexample.com", "doc", Protocol::HTTPS, 8080);
	CHECK(url.GetDomain() == "myexample.com");
	CHECK(url.GetDocument() == "/doc");
	CHECK(url.GetProtocol() == Protocol::HTTPS);
	CHECK(url.GetPort() == 8080);
	CHECK(url.GetURL() == "https://myexample.com:8080/doc");
}

TEST_CASE("Empty document adds slash")
{
	CHttpUrl url("myexample.com", "");
	CHECK(url.GetDocument() == "/");
}

TEST_CASE("Testing huge url")
{
	CHttpUrl url("http://example.com/page?query=1&lang=en#top");
	CHECK(url.GetDomain() == "example.com");
	CHECK(url.GetDocument() == "/page?query=1&lang=en#top");
	CHECK(url.GetProtocol() == Protocol::HTTP);
	CHECK(url.GetPort() == 80);
	CHECK(url.GetURL() == "http://example.com/page?query=1&lang=en#top");
}
	
TEST_CASE("Invalid URLS")
{ 
	SECTION("Invalid protocol")
	{
		CHECK_THROWS_AS(CHttpUrl("ftp://myurl.com"), CUrlParsingError);
		CHECK_THROWS_AS(CHttpUrl("http:/invalid.url"), CUrlParsingError);
	}
	SECTION("Invalid domain")
	{
		CHECK_THROWS_AS(CHttpUrl("", "doc"), CUrlParsingError);
		CHECK_THROWS_AS(CHttpUrl("--url", "doc", Protocol::HTTP), CUrlParsingError);
	}
	SECTION("Out of range port")
	{
		CHECK_THROWS_AS(CHttpUrl("example.com", "doc", Protocol::HTTP, 0), CUrlParsingError);
		CHECK_THROWS_AS(CHttpUrl("example.com", "doc", Protocol::HTTP, -15), CUrlParsingError);
		CHECK_THROWS_AS(CHttpUrl("example.com", "doc", Protocol::HTTP, 65536), CUrlParsingError);
		CHECK_THROWS_AS(CHttpUrl("http://example.com:65536/doc"), CUrlParsingError);
		CHECK_THROWS_AS(CHttpUrl("http://example.com:0/doc"), CUrlParsingError);
		CHECK_THROWS_AS(CHttpUrl("http://example.com:-45/doc"), CUrlParsingError);
	}
}