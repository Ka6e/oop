#include "../include/CRectangle.h"
#include <stdexcept>
#include <sstream>

CRectangle::CRectangle(const CPoint& topLeft, const CPoint& bottomRight, uint32_t outlineColor, uint32_t fillColor)
	: m_topLeft(topLeft),
	m_bottomRight(bottomRight),
	m_outlineColor(outlineColor),
	m_fillColor(fillColor)
{
	if (m_bottomRight.x <= m_topLeft.x || m_bottomRight.y <= m_topLeft.y)
	{
		throw std::invalid_argument("Invalid rectangle coordinates");
	}
}

CPoint CRectangle::GetTopLeft() const
{
	return m_topLeft;
}

CPoint CRectangle::GetBottomRight() const
{
	return m_bottomRight;
}

double CRectangle::GetArea() const
{
	return GetHeight() * GetWidth();
}

double CRectangle::GetPerimeter() const
{
	return 2 * (GetHeight() + GetWidth());
}

uint32_t CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
	return m_fillColor;
}

std::string CRectangle::ToString() const
{
	std::ostringstream oss;
	oss << "Rectangle: \n";
	oss << "Top Left: (" << m_topLeft.x << ", " << m_topLeft.y << ")\n";
	oss << "Bottom Right: (" << m_bottomRight.x << ", " << m_bottomRight.y << ")\n";
	oss << "Width: " << GetWidth() << "\n";
	oss << "Height: " << GetHeight() << "\n";
	oss << "Area: " << GetArea() << "\n";
	oss << "Perimeter: " << GetPerimeter() << "\n";
	oss << "Outline Color: " << std::hex << m_outlineColor << "\n";
	oss << "Fill Color: " << std::hex << m_fillColor << "\n";

	return oss.str();
}

double CRectangle::GetWidth() const
{
	return std::abs(m_bottomRight.x - m_topLeft.x);
}

double CRectangle::GetHeight() const
{
	return std::abs(m_topLeft.y - m_bottomRight.y);
}

void CRectangle::Draw(std::shared_ptr<ICanvas> canvas)
{
	if (!canvas )
	{
		throw std::invalid_argument("Canvas is null");
	}
	std::vector<CPoint> points = {
		m_topLeft,
		{ m_bottomRight.x, m_topLeft.y },
		m_bottomRight,
		{ m_topLeft.x, m_bottomRight.y }
	};
	canvas->FillPolygon(points, m_fillColor);
	canvas->DrawLine(m_topLeft, { m_bottomRight.x, m_topLeft.y }, m_outlineColor);
	canvas->DrawLine({ m_bottomRight.x, m_topLeft.y }, m_bottomRight, m_outlineColor);
	canvas->DrawLine(m_bottomRight, { m_topLeft.x, m_bottomRight.y }, m_outlineColor);
	canvas->DrawLine({ m_topLeft.x, m_bottomRight.y }, m_topLeft, m_outlineColor);
}

