#pragma once
#include "../include/ISolidShape.h"
#include "../include/CPoint.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(const CPoint& point1, const CPoint& point2, const CPoint& point3,uint32_t outlineColor, uint32_t fillColor);
	double GetArea() const override;	
	double GetPerimeter() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;
	std::string ToString() const override;
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;
	void Draw(std::shared_ptr<ICanvas> canvas) override;
private:
	void CalculateLineLength(double& a, double& b, double& c) const;
	CPoint m_point1, m_point2, m_point3;
	uint32_t m_outlineColor, m_fillColor;
};
