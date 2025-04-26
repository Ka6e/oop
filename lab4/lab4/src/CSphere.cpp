#include "../include/CSphere.h"
#include <ostream>
#include <numbers>

CSphere::CSphere(double density, double radius)
	: CBody("Sphere", density)
	, m_radius(radius)
{
}

double CSphere::GetRadius()const
{
	return m_radius;
}

double CSphere::GetVolume()const
{
	return (pow(m_radius, 3) * std::numbers::pi) * 4 / 3;
}

void CSphere::AppendProperties(std::ostream& strm) const
{
	strm << "\tradius = " << GetRadius() << std::endl;
}