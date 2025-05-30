#pragma once
#include "headers.h"

class CPupil : public CPersonImpl<IPupil>
{
public:
	CPupil(const std::string& firstName,
		const std::string& lastName,
		const std::string& patronymic,
		const std::string& adress,
		const std::string& schoool,
		const std::string& grade);

	std::string GetSchool() const override;
	std::string GetGrade() const override;
private:
	std::string m_school;
	std::string m_grade;
	void Validate() const override;
};