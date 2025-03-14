#include "DecodeOperations.h"


std::string HtmlDecode(std::string const& html)
{
	std::string result;
	result.reserve(html.size());

	for (size_t i = 0; i < html.size(); i++)
	{
		if (html[i] == '&')
		{
			bool isFound = false;
			//переписать и разделить на подфункции
			for (const auto& [entity, symbol] : htmlEntities)
			{
				//копить эл в отдельную строку потом плюсовать
				if (html.substr(i, entity.size()) == entity)
				{
					result += symbol;
					i += entity.size() - 1;
					isFound = true;
					break;
				}
			}
			if (!isFound)
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