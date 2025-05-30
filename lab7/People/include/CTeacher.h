#pragma once
#include "headers.h"

class CTeacher : public CPersonImpl<ITeacher>
{
public:
	CTeacher(const std::string& firstName,
		const std::string& lastName,
		const std::string& patronymic,
		const std::string& adress,
		const std::string& subject);

	void Validate() const override;
	std::string GetSubject() const override;
private:
	std::string m_subject;
};