#pragma once
#include "IPreson.h"

class IPupil : public IPerson
{
public:
	virtual std::string GetSchool() const = 0;
	virtual std::string GetGrade() const = 0;
};
