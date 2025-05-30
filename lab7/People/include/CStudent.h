#pragma once
#include "headers.h"

class CStudent : public CStudentImpl<IStudent>
{
public:
	CStudent(const std::string& firstName,
		const std::string& lastName,
		const std::string& patronymic,
		const std::string& adress,
		const std::string& university,
		const std::string& studentId);
};
