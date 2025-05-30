#include "../include/CPupil.h"


CPupil::CPupil(const std::string& firstName,
	const std::string& lastName,
	const std::string& patronymic,
	const std::string& adress,
	const std::string& schoool,
	const std::string& grade)
	: CPersonImpl<IPupil>(firstName, lastName, patronymic, adress),
	m_school(schoool),
	m_grade(grade)
{
	Validate();
}

void CPupil::Validate() const
{

	CPersonImpl<IPupil>::Validate();

	if (m_school.empty())
	{
		throw std::invalid_argument("School cannot be empty");
	}
	if (m_school.find_first_not_of(" \t\n") == std::string::npos)
	{
		throw std::invalid_argument("School cannot be only whitespace");
	}
	if (m_school.length() > 100)
	{
		throw std::invalid_argument("School cannot exceed 100 characters");
	}

	if (m_grade.empty())
	{
		throw std::invalid_argument("Class cannot be empty");
	}
	if (m_grade.length() < 2 || m_grade.length() > 3)
	{
		throw std::invalid_argument("Class must be 2 or 3 characters (e.g., '7á')");
	}
	if (!std::isdigit(m_grade[0]) || !std::isalpha(m_grade[m_grade.length() - 1]))
	{
		throw std::invalid_argument("Class must be in format 'number + letter' (e.g., '7á')");
	}
}

std::string CPupil::GetSchool() const
{
	return m_school;
}
std::string CPupil::GetGrade() const
{
	return m_grade;
}