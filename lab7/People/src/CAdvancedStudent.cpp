#include "../include/CAdvancedStudent.h"

CAdvancedStudent::CAdvancedStudent(const std::string& firstName,
	const std::string& lastName,
	const std::string& patronymic,
	const std::string& adress,
	const std::string& university,
	const std::string& studentId,
	const std::string& dissertationTopic)
	: CStudentImpl<IAdvancedStudent>(firstName,
		lastName,
		patronymic,
		adress,
		university,
		studentId),
	m_dissertationTopic(dissertationTopic)
{
	Validate();
}

void CAdvancedStudent::Validate() const
{
	CStudentImpl<IAdvancedStudent>::Validate();
	if (m_dissertationTopic.empty()) 
	{
		throw std::invalid_argument("Dissertation topic cannot be empty");
	}
	if (m_dissertationTopic.find_first_not_of(" \t\n") == std::string::npos) 
	{
		throw std::invalid_argument("Dissertation topic cannot be only whitespace");
	}
	if (m_dissertationTopic.length() > 200) 
	{
		throw std::invalid_argument("Dissertation topic cannot exceed 200 characters");
	}
}
std::string CAdvancedStudent::GetDissertationTopic() const
{
	return m_dissertationTopic;
}