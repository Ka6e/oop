#include "../include/CTriangle.h"
#include <cmath>
#include <stdexcept>
#include <sstream>

CTriangle::CTriangle(const CPoint& point1, const CPoint& point2, const CPoint& point3, uint32_t outlineColor, uint32_t fillColor)
	:m_point1(point1),
	m_point2(point2),
	m_point3(point3),
	m_outlineColor(outlineColor),
	m_fillColor(fillColor)
{
	if ((point1.x == point2.x && point1.y == point2.y) ||
		(point2.x == point3.x && point2.y == point3.y) ||
		(point3.x == point1.x && point3.y == point1.y))
	{
		throw std::invalid_argument("Invalid triangle points: identical points");
	}
	double area = 0.5 * std::abs(point1.x * (point2.y - point3.y) +
		point2.x * (point3.y - point1.y) +
		point3.x * (point1.y - point2.y));
	if (area < 1e-10)
	{
		throw std::invalid_argument("Invalid triangle points: collinear points");
	}
	double a, b, c;
	CalculateLineLength(a, b, c);
	if ((a + b <= c) || (a + c <= b) || (b + c <= a))
	{
		throw std::invalid_argument("Invalid triangle points");
	}
}

double CTriangle::GetArea() const
{
	double a, b, c;
	CalculateLineLength(a, b, c);

	double p = (a + b + c) / 2;

	return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

CPoint CTriangle::GetVertex1() const
{
	return m_point1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_point2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_point3;
}

void CTriangle::Draw(std::shared_ptr<ICanvas> canvas)
{
	std::vector<CPoint> points = { m_point1, m_point2, m_point3 };
	canvas->FillPolygon(points, m_fillColor);
	canvas->DrawLine(m_point1, m_point2, m_outlineColor);
	canvas->DrawLine(m_point2, m_point3, m_outlineColor);
	canvas->DrawLine(m_point3, m_point1, m_outlineColor);
}

double CTriangle::GetPerimeter() const
{
	double a, b, c;
	CalculateLineLength(a, b, c);
	return (a + b + c);
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}

std::string CTriangle::ToString() const
{
	std::ostringstream oss;
	oss << "Trinagle: \n";
	oss << "Vertex 1: (" << m_point1.x << ", " << m_point1.y << ")\n";
	oss << "Vertex 2: (" << m_point2.x << ", " << m_point2.y << ")\n";
	oss << "Vertex 3: (" << m_point3.x << ", " << m_point3.y << ")\n";
	oss << "Perimetr: " << GetPerimeter() << "\n";
	oss << "Area: " << GetArea() << "\n";
	oss << "Outline color: " << std::hex << m_outlineColor << "\n";
	oss << "Fill color: " << std::hex << m_fillColor << "\n";

	return oss.str();
}

void CTriangle::CalculateLineLength(double& a, double& b, double& c) const
{
	a = sqrt(pow(m_point2.x - m_point1.x, 2) + pow(m_point2.y - m_point1.y, 2));
	b = sqrt(pow(m_point3.x - m_point1.x, 2) + pow(m_point3.y - m_point1.y, 2));
	c = sqrt(pow(m_point3.x - m_point2.x, 2) + pow(m_point3.y - m_point2.y, 2));
}

