#pragma once
#include "../include/CBody.h"

class CCone :public CBody
{
public:
	CCone(double destinity, double radius, double height);
	double GetHeight() const;
	double GetBaseRadius() const;
	double GetVolume() const override;

private:
	void AppendProperties(std::ostream& strm) const override;
	double m_height;
	double m_radius;
};
