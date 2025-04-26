#pragma once
#include <string>


class Function
{
public:
	enum class Operations
	{
		ADD,
		SUBSTRACT,
		MULTIPLY,
		DIVIDE,
		NONE
	};
	Function() = default;
	Function(const std::string& identifier, const  std::string& firstVariable,
		Operations operation, const std::string& secondVariable);
	Function(const std::string& identifier, const std::string& variable);
	std::string GetName() const;
	Operations GetOperator() const;
	std::string GetFirstIdentifier() const;
	std::string GetSecondIdentifier() const;

private:
	std::string m_identifier;
	std::string m_firstVariable;
	Operations m_operation = Operations::NONE;
	std::string m_secondVariable;
};
