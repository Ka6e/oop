#pragma once
#include "../include/IShape.h"

class ISolidShape : public IShape
{
public:
	virtual uint32_t GetFillColor() const = 0;
	~ISolidShape() override = default;
};
