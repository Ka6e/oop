#pragma once
#include "CPresonImlp.h"

template <typename Base>
class CStudentImpl : public CPersonImpl<Base>
{
public:
    CStudentImpl(const std::string& firstName,
        const std::string& lastName,
        const std::string& patronymic,
        const std::string& adress,
        const std::string& university,
        const std::string& studentId)
        : CPersonImpl<Base>(firstName, lastName, patronymic, adress),
        m_university(university),
        m_studentId(studentId)
    {
        Validate();
	}

    std::string GetUniversity() const override
    {
        return m_university;
    }

    std::string GetStudentId() const override
    {
        return m_studentId;
    }

protected:
	std::string m_university;
	std::string m_studentId;

    void Validate() const override 
    {
        CPersonImpl<Base>::Validate();

        if (m_university.empty()) 
        {
            throw std::invalid_argument("University cannot be empty");
        }
        if (m_university.find_first_not_of(" \t\n") == std::string::npos) 
        {
            throw std::invalid_argument("University cannot be only whitespace");
        }
        if (m_university.length() > 100) 
        {
            throw std::invalid_argument("University cannot exceed 100 characters");
        }

        if (m_studentId.empty()) 
        {
            throw std::invalid_argument("Student ID cannot be empty");
        }
        if (m_studentId.length() < 5 || m_studentId.length() > 10) 
        {
            throw std::invalid_argument("Student ID must be between 5 and 10 characters");
        }
    }
};
