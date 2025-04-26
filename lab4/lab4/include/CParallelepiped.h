#pragma once
#include "../include/CBody.h"

class CParallelepiped : public CBody
{
public:
	CParallelepiped(double density, double length, double width, double height);
	double GetLength() const;
	double GetWidth() const;
	double GetHeight() const;
	double GetVolume() const override;

private:
	void AppendProperties(std::ostream& strm) const override;
	double m_length;
	double m_width;
	double m_height;
};
