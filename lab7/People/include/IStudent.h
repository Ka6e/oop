#pragma once
#include "IPreson.h"

class IStudent : public IPerson
{
public:
	virtual std::string GetUniversity() const = 0;
	virtual std::string GetStudentId() const = 0;
};

