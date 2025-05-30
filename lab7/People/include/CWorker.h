#pragma once
#include "headers.h"

class CWorker : public CPersonImpl<IWorker>
{
public:
	CWorker(const std::string& firstName,
		const std::string& lastName,
		const std::string& patronymic,
		const std::string& adress,
		const std::string& specialization);
	std::string GetSpecialization() const override;

private:
	std::string m_specialization;
	void Validate() const override;
};