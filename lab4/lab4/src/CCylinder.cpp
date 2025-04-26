#include "../include/CCylinder.h"
#include <sstream>
#include <numbers>

CCylinder::CCylinder(double density, double radius, double height)
	: CBody("Cylinder", density),
	m_radius(radius),
	m_height(height)
{ 
}

double CCylinder::GetHeight() const
{
	return m_height;
}

double CCylinder::GetVolume() const
{
	return (std::numbers::pi * pow(m_radius, 2) * m_height);
}

double CCylinder::GetBaseRadius() const
{
	return m_radius;
}

void CCylinder::AppendProperties(std::ostream& strm) const
{
	strm << "\tradius = " << GetBaseRadius() << std::endl;
	strm << "\theight = " << GetHeight() << std::endl;
}
