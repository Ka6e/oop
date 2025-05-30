#pragma once
#include <string>
class IPerson
{
public:
	virtual std::string GetFirstName() const = 0;
	virtual std::string GetSecondName() const = 0;
	virtual std::string GetPatronymic()  const = 0;
	virtual std::string GetAdress() const = 0;
	virtual ~IPerson() = default;
};
