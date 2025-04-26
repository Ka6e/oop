#include "../include/CParallelepiped.h"
#include <sstream>

CParallelepiped::CParallelepiped(double density, double length, double width, double height)
	: CBody("Parallelepiped", density),
	m_length(length),
	m_width(width),
	m_height(height)
{
}
double CParallelepiped::GetVolume() const
{
	return m_length * m_width * m_height;
}
double CParallelepiped::GetLength() const
{
	return m_length;
}
double CParallelepiped::GetWidth() const
{
	return m_width;
}
double CParallelepiped::GetHeight() const
{
	return m_height;
}
void CParallelepiped::AppendProperties(std::ostream& strm) const
{
	strm << "Length: " << m_length << "\n"
		<< "Width: " << m_width << "\n"
		<< "Height: " << m_height << "\n";
}