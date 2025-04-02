#include "../include/DecodeOperations.h"


bool DecoceHtmlEntity(const std::string& html,size_t& i,  std::string& result)
{
	size_t end = html.find(';', i);
	if (end == std::string::npos || end - i < 2) 
	{
		return false;
	}

	std::string entity = html.substr(i, end - i + 1);
	auto it = htmlEntities.find(entity);
	if (it != htmlEntities.end()) 
	{
		result += it->second;      
		i = end;                
		return true;               
	}
	return false;
}


std::string HtmlDecode(std::string const& html)
{
	std::string result;
	result.reserve(html.size());

	for (size_t i = 0; i < html.size(); i++)
	{
		if (html[i] == '&')
		{
			if (!DecoceHtmlEntity(html, i, result))
			{
				result += html[i];
			}
		}
		else
		{
			result += html[i];
		}
	}

	return result;
}