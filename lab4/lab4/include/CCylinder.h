#pragma once
#include "../include/CBody.h"

class CCylinder : public CBody
{
public:
	CCylinder(double density,double radius, double height);

	double GetHeight() const;
	double GetBaseRadius() const;
	double GetVolume() const override;

private:
	void AppendProperties(std::ostream& strm) const override;
	double m_radius;
	double m_height;
};
