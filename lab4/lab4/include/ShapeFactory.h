#pragma once
#include <memory>
#include "../include/IShape.h"

class ShapeFactory
{
public:
	static std::shared_ptr<IShape> CreateShape(const std::string& type);
};
