#pragma once
#include "../include/ISolidShape.h"
#include "../include/CPoint.h"

class CRectangle : public ISolidShape
{
public:
	CRectangle(const CPoint& topLeft, const CPoint& bottomRight, uint32_t outlineColor, uint32_t fillColor);
	CPoint GetTopLeft() const;
	CPoint GetBottomRight() const;
	double GetArea() const override;
	double GetPerimeter() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;
	std::string ToString() const override;
	double GetWidth() const;
	double GetHeight() const;
	void Draw(std::shared_ptr<ICanvas> canvas) override;
private:
	CPoint m_topLeft, m_bottomRight;
	uint32_t m_outlineColor, m_fillColor;
};
