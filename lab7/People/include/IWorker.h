#pragma once
#include "IPreson.h"

class IWorker : public IPerson
{
public:
	virtual std::string GetSpecialization() const = 0;
};
