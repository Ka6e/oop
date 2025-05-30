#pragma once
#include "IPreson.h"

class IAdvancedStudent : public IStudent
{
public:
	virtual std::string GetDissertationTopic() const = 0;
};
