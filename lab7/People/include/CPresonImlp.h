#pragma once
#include <string>
#include <stdexcept>

template <typename Base>
class CPersonImpl : public Base
{
public:
	CPersonImpl(
		const std::string& firstName,
		const std::string& lastName,
		const std::string& patronymic,
		const std::string& adress)
		: m_firstName(firstName),
		m_lastName(lastName),
		m_patronymic(patronymic),
		m_adress(adress)
	{
		Validate();
	} 

	std::string GetFirstName() const override { return m_firstName; }
	std::string GetSecondName() const override { return m_lastName; }
	std::string GetPatronymic()  const override { return m_patronymic; }
	std::string GetAdress() const override { return m_adress; }

protected:

	void ValidateFields(const std::string& field, const std::string& fieldName) const
	{
		if (field.empty()) 
		{
			throw std::invalid_argument(fieldName + " cannot be empty");
		}
		if (field.find_first_not_of(" \t\n") == std::string::npos) 
		{
			throw std::invalid_argument(fieldName + " cannot be only whitespace");
		}
		if (field.length() > 50) 
		{
			throw std::invalid_argument(fieldName + " cannot exceed 50 characters");
		}
	}

	virtual void Validate() const
	{
		ValidateFields(m_firstName, "First name");
		ValidateFields(m_lastName, "Last name");
		ValidateFields(m_patronymic, "Patronymic");
		ValidateFields(m_adress, "Address");

	}
	std::string m_firstName;
	std::string m_lastName;
	std::string m_patronymic;
	std::string m_adress;
};
