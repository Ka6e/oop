#pragma once
#include "../include/IShape.h"
#include <memory>
#include <vector>
#include <string>

class ShapeManager
{
public:
	void ReadShape(std::istream& input);
	void ReadShape(const std::string& fileName);
	void PrintMaxAreaShape() const;
	void PrintMinPerimeterShape() const;
	std::vector<std::shared_ptr<IShape>> GetShapes() const;
private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
};
