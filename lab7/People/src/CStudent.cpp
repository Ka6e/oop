#include "../include/CStudent.h"

CStudent::CStudent(const std::string& firstName, 
	const std::string& lastName, 
	const std::string& patronymic, 
	const std::string& adress, 
	const std::string& university, 
	const std::string& studentId) 
	: CStudentImpl(firstName,
		lastName,
		patronymic,
		adress,
		university,
		studentId)
{
}
