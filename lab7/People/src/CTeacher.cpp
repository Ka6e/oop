#include "../include/CTeacher.h"
#include <algorithm>


CTeacher::CTeacher (const std::string& firstName,
	const std::string& lastName,
	const std::string& patronymic,
	const std::string& adress,
	const std::string& subject)
	: CPersonImpl<ITeacher>(firstName, lastName, patronymic, adress),
	m_subject(subject)
{
	Validate();
}

void CTeacher::Validate() const 
{
    CPersonImpl<ITeacher>::Validate();
    if (m_subject.empty()) 
    {
        throw std::invalid_argument("Subject cannot be empty");
    }
    if (m_subject.find_first_not_of(" \t\n") == std::string::npos) 
    {
        throw std::invalid_argument("Subject cannot be only whitespace");
    }
    if (m_subject.length() > 50) 
    {
        throw std::invalid_argument("Subject cannot exceed 50 characters");
    }
    if (!std::all_of(m_subject.begin(), m_subject.end(), 
        [](char c) 
        {
        return std::isalpha(c) || std::isspace(c);
        })) 
    {
        throw std::invalid_argument("Subject must contain only letters and spaces");
    }
}

std::string CTeacher::GetSubject() const 
{
	return m_subject;
}