#include "../include/CCircle.h"
#include "stdexcept"
#include <numbers>
#include <cmath>
#include <sstream>

CCircle::CCircle(const CPoint& center, double radius, uint32_t outlineColor, uint32_t fillcolor)
	: m_center(center),
	m_radius(radius),
	m_outlineColor(outlineColor),
	m_fillColor(fillcolor)
{
	if (radius <= 0)
	{
		throw std::invalid_argument("Invalid circle radius");
	}
}

double CCircle::GetArea() const
{
	return std::numbers::pi * std::pow(m_radius, 2);
}

double CCircle::GetPerimeter() const
{
	return 2 * std::numbers::pi * m_radius;
}

uint32_t CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
	return m_fillColor;
}

std::string CCircle::ToString() const
{
	std::ostringstream oss;

	oss << "Circle: \n";
	oss << "Center: (" << m_center.x << ", " << m_center.y << ")\n";
	oss << "Radius: " << m_radius << "\n";
	oss << "Area: " << GetArea() << "\n";
	oss << "Perimeter: " << GetPerimeter() << "\n";
	oss << "Outline Color: " << std::hex << m_outlineColor << "\n";
	oss << "Fill Color: " << std::hex << m_fillColor << "\n";
	
	return oss.str();
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

void CCircle::Draw(std::shared_ptr<ICanvas> canvas)
{
	if (!canvas)
	{
		throw std::invalid_argument("Canvas is null");
	}
	canvas->DrawCircle(m_center, m_radius, m_outlineColor);
	canvas->FillCircle(m_center, m_radius, m_fillColor);
}


