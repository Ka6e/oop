#include "../include/ShapeManager.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "../include/ShapeFactory.h"

std::shared_ptr<IShape> FindMaxArea(const std::vector<std::shared_ptr<IShape>>& shapes)
{
	auto maxShape = shapes[0];
	double maxArea = maxShape->GetArea();

	for (const auto& shape : shapes)
	{
		if (shape->GetArea() > maxArea)
		{
			maxArea = shape->GetArea();
			maxShape = shape;
		}
	}
	return maxShape;
}

std::shared_ptr<IShape> FindMinPerimeter(const std::vector<std::shared_ptr<IShape>>& shapes)
{
	auto minShape = shapes[0];
	double minPerimeter = minShape->GetPerimeter();

	for (const auto& shape : shapes)
	{
		if (shape->GetPerimeter() < minPerimeter) 
		{
			minPerimeter = shape->GetPerimeter();
			minShape = shape;
		}
	}

	return minShape;
}

void ShapeManager::ReadShape(std::istream& input)
{
	std::string line;
	while (std::getline(input, line))
	{
		try
		{
			m_shapes.emplace_back(ShapeFactory::CreateShape(line));
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			continue;
		}
	}
}

void ShapeManager::ReadShape(const std::string& fileName)
{
	std::ifstream inputFile(fileName);

	if (!inputFile)
	{
		throw std::invalid_argument("Failed to open input file");
	}
	ReadShape(inputFile);
	if (inputFile.bad())
	{
		throw std::invalid_argument("Fatal error input file");
	}
}

void ShapeManager::PrintMaxAreaShape() const
{
	if (m_shapes.empty())
	{
		std::cout << "No Shapes" << std::endl;
		return;
	}
	auto maxShapeArea = FindMaxArea(m_shapes);
	std::cout << "Shape with max area:" << std::endl;
	std::cout << maxShapeArea->ToString();
}

void ShapeManager::PrintMinPerimeterShape() const
{
	if (m_shapes.empty())
	{
		std::cout << "No shapes" << std::endl;
		return;
	}

	auto minShapePerimeter = FindMinPerimeter(m_shapes);
	std::cout << "Shape with min perimeter:" << std::endl;
	std::cout << minShapePerimeter->ToString();
}

std::vector<std::shared_ptr<IShape>> ShapeManager::GetShapes() const
{
	return m_shapes;
}

