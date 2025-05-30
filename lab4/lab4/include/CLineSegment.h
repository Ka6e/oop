#pragma once
#include "../include/IShape.h"
#include "../include/CPoint.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(const CPoint& startPoint, const CPoint& endPoint, uint32_t color);
	uint32_t GetOutlineColor() const override;
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
	void Draw(std::shared_ptr<ICanvas> canvas) override;
private:
	CPoint m_startPoint;
	CPoint m_endPoint;
	uint32_t m_color;
};
