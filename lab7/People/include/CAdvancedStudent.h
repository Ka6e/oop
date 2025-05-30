#pragma once
#include "headers.h"

class CAdvancedStudent : public CStudentImpl<IAdvancedStudent>
{
public:
	CAdvancedStudent(const std::string& firstName,
		const std::string& lastName,
		const std::string& patronymic,
		const std::string& adress,
		const std::string& university,
		const std::string& studentId,
		const std::string& dissertationTopic);
	std::string GetDissertationTopic() const override;
private:
	void Validate() const override;
	std::string m_dissertationTopic;
};