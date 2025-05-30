#pragma once
#include "IPreson.h"

class ITeacher : public IPerson
{
public:
	virtual std::string GetSubject() const = 0;
};
