#include "../include/CLineSegment.h"
#include <cmath>
#include <stdexcept>
#include <sstream>

CLineSegment::CLineSegment(const CPoint& startPoint, const CPoint& endPoint, uint32_t color):
	m_startPoint(startPoint),
	m_endPoint(endPoint),
	m_color(color)
{
	if (startPoint.x == endPoint.x && startPoint.y == endPoint.y)
	{
		throw std::invalid_argument("Invalid line segment points");
	}
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

void CLineSegment::Draw(std::shared_ptr<ICanvas> canvas)
{
	if (!canvas)
	{
		throw std::invalid_argument("Canvas is null");
	}
	canvas->DrawLine(m_startPoint, m_endPoint, m_color);
}

uint32_t CLineSegment::GetOutlineColor() const
{
	return m_color;
}

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	return std::sqrt(
		std::pow(m_endPoint.x - m_startPoint.x, 2) +
		std::pow(m_endPoint.y - m_startPoint.y, 2)
	);
}

std::string CLineSegment::ToString() const
{
	std::ostringstream oss;
	oss << "Line Segment: \n";
	oss << "Start Point: (" << m_startPoint.x << ", " << m_startPoint.y << ")\n";
	oss << "End Point: (" << m_endPoint.x << ", " << m_endPoint.y << ")\n";
	oss << "Length: " << GetPerimeter() << "\n";
	oss << "Area: " << GetArea() << "\n";
	oss << "Outline Color: " << std::hex << m_color << "\n";
	return oss.str();
}