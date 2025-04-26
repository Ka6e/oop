#include "include/Function.h"



Function::Function(const std::string& identifier, const  std::string& firstVariable,
	Operations operation, const std::string& secondVariable) :
	m_identifier(identifier),
	m_firstVariable(firstVariable),
	m_operation(operation),
	m_secondVariable(secondVariable)
{
}

Function::Function(const std::string& identifier, const std::string& variable) :
	m_identifier(identifier),
	m_firstVariable(variable)
{
}

std::string Function::GetName() const
{
	return m_identifier;
}

Function::Operations Function::GetOperator() const
{
	return m_operation;
}

std::string Function::GetFirstIdentifier() const
{
	return m_firstVariable;
}

std::string Function::GetSecondIdentifier() const
{
	return m_secondVariable;
}