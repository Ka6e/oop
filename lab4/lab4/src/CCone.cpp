#include "../include/CCone.h"
#include <numbers>
#include <sstream>

CCone::CCone(double destinity, double radius, double height)
	: CBody("Cone", destinity)
	, m_height(height)
	, m_radius(radius)
{
}
double CCone::GetHeight() const
{
	return m_height;
}
double CCone::GetBaseRadius() const
{
	return m_radius;
}

double CCone::GetVolume() const
{
	return (std::numbers::pi * pow(m_radius, 2) * m_height) / 3;
}

void CCone::AppendProperties(std::ostream& strm) const
{
	strm << "\tradius = " << GetBaseRadius() << std::endl;
	strm << "\theight = " << GetHeight() << std::endl;
}