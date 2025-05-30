#include "../include/CWorker.h"
#include <algorithm>

CWorker::CWorker(const std::string& firstName,
	const std::string& lastName,
	const std::string& patronymic,
	const std::string& adress,
	const std::string& specialization)
	: CPersonImpl<IWorker>(firstName,
		lastName,
		patronymic,
		adress),
	m_specialization(specialization)
{
	Validate();
}

void CWorker::Validate() const
{
    CPersonImpl<IWorker>::Validate();
    if (m_specialization.empty()) 
    {
        throw std::invalid_argument("Specialty cannot be empty");
    }
    if (m_specialization.find_first_not_of(" \t\n") == std::string::npos) 
    {
        throw std::invalid_argument("Specialty cannot be only whitespace");
    }
    if (m_specialization.length() > 50) 
    {
        throw std::invalid_argument("Specialty cannot exceed 50 characters");
    }
    if (!std::all_of(m_specialization.begin(), m_specialization.end(), [](char c) 
        {
        return std::isalpha(c) || std::isspace(c);
        })) 
    {
        throw std::invalid_argument("Specialty must contain only letters and spaces");
    }
}

std::string CWorker::GetSpecialization() const 
{
	return m_specialization;
}
