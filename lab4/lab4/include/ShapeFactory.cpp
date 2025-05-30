#include "ShapeFactory.h"
#include "../include/CRectangle.h"
#include "../include/CCircle.h"
#include "../include/CTriangle.h"
#include "../include/CLineSegment.h"
#include <sstream>
#include <iostream>

const std::string TRIANGLE = "triangle";
const std::string CIRCLE = "circle";
const std::string LINESEGMENT = "line";
const std::string RECTANGLE = "rectangle";

std::shared_ptr<CLineSegment> CreateLine(const std::string& line)
{
	std::string name;
	std::istringstream iss(line);
	iss >> name;

	double fromX, fromY, toX, toY;
	if (!(iss >> fromX >> fromY >> toX >> toY))
	{
		throw std::invalid_argument("Invalid argiments for line");
	}
	uint32_t color;
	if (!(iss >> std::hex >> color))
	{
		throw std::invalid_argument("Invalid color argiment for line");
	}

	return std::make_shared<CLineSegment>(CPoint(fromX, fromY), CPoint(toX, toY), color);
}

std::shared_ptr<CCircle> CreateCircle(const std::string& line)
{
	std::string name;
	std::istringstream iss(line);
	iss >> name;

	double x, y, radius;
	if (!(iss >> x >> y >> radius))
	{
		throw std::invalid_argument("Invalid argument for circle");
	}

	uint32_t outlineColor, fillColor;
	if (!(iss >> std::hex >> outlineColor >> fillColor))
	{
		throw std::invalid_argument("Invalid color argument for circle");
	}

	return std::make_shared<CCircle>(CPoint(x, y), radius, outlineColor, fillColor);
}

std::shared_ptr<CTriangle> CreateTriangle(const std::string& line)
{
	std::string name;
	std::istringstream iss(line);
	iss >> name;

	double v1X, v1Y, v2X, v2Y, v3X, v3Y;
	if (!(iss >> v1X >> v1Y >> v2X >> v2Y >> v3X >> v3Y))
	{
		throw std::invalid_argument("Invalid arguments for triangle");
	}

	uint32_t outlineColor, fillColor;
	if (!(iss >> std::hex >> outlineColor >> fillColor))
	{
		throw std::invalid_argument("Invalid color for triangle");
	}

	return std::make_shared<CTriangle>(CPoint(v1X, v1Y), CPoint(v2X, v2Y),
		CPoint(v3X, v3Y), outlineColor, fillColor);
}


std::shared_ptr<CRectangle> CreateRectangle(const std::string& line)
{
	std::istringstream iss(line);
	std::string name;
	iss >> name;

	double leftTopX, leftTopY, rightBottomX, rightBottomY;
	if (!(iss>> leftTopX >> leftTopY >> rightBottomX >> rightBottomY))
	{
		throw std::invalid_argument("Invalid argiments for rectangle");
	}
	uint32_t outlineColor, fillColor;
	if (!(iss >> std::hex >>outlineColor >> fillColor))
	{
		throw std::invalid_argument("Invalid color argiment for rectangle");
	}

	return std::make_shared<CRectangle>(CPoint(leftTopX, leftTopY), CPoint(rightBottomX, rightBottomY), outlineColor, fillColor);
}


std::shared_ptr<IShape> ShapeFactory::CreateShape(const std::string& type)
{
	std::string shapeType;
	std::istringstream iss(type);
	iss >> shapeType;
	if (shapeType == LINESEGMENT)
	{
		return CreateLine(type);
	}
	else if (shapeType == TRIANGLE)
	{
		return CreateTriangle(type);
	}
	else if (shapeType == RECTANGLE)
	{
		return CreateRectangle(type);
	}
	else if(shapeType == CIRCLE)
	{
		return CreateCircle(type);
	}
	return nullptr;
}
