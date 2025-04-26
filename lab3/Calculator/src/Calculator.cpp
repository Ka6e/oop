#include "include/Calculator.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>

//вынести дубликат
void Calculator::DeclareVariable(const std::string& identifier)
{
	if (m_varMap.find(identifier) != m_varMap.end())
	{
		std::cerr << "The identifier is already in use" << std::endl;
		return;
	}
	m_varMap[identifier] = std::make_unique<Variable>(identifier, NAN);
}
void Calculator::InitVariable(const std::string& identifier, double value)
{
	auto variable = m_varMap.find(identifier);
	if (variable == m_varMap.end())
	{
		m_varMap[identifier] = std::make_unique<Variable>(identifier, value);
		return;
	}
	variable->second->SetValue(value);
}

void Calculator::InitVariableWithIdentifier(const std::string& identifierFirts, const std::string& identifierSecond)
{
	if (identifierFirts == identifierSecond)
	{
		std::cerr << "This variable already exist" << std::endl;
		return;
	}
	auto func = m_funcMap.find(identifierFirts);
	if (func != m_funcMap.end())
	{
		std::cerr << "The variable cannot named like the function" << std::endl;
		return;
	}
	double value = CalculateValue(identifierSecond);
	m_varMap[identifierFirts] = std::make_unique<Variable>(identifierFirts, value);
}

void Calculator::CreateFunction(const std::string& funcName, const std::string& firtVariable, 
	Function::Operations operation, const std::string& secondVariable)
{
	auto function = m_funcMap.find(funcName);
	if (function != m_funcMap.end())
	{
		std::cerr << "This function already exist" << std::endl;
		return;
	}
	m_funcMap[funcName] = std::make_unique<Function>(funcName, firtVariable, operation, secondVariable);
}

void Calculator::CreateFunctionithVariable(const std::string& funcName, const std::string& variable)
{
	auto function = m_funcMap.find(funcName);
	if (function != m_funcMap.end())
	{
		std::cerr << "This function name is already exist" << std::endl;
		return;
	}
	m_funcMap[funcName] = std::make_unique<Function>(funcName, variable);
}

double Calculator::CalculateFunction(const std::string& identifier) const
{
	if (m_funcMap.find(identifier) == m_funcMap.end())
	{
		std::invalid_argument("This function doesn't exist");
	}

	auto function = m_funcMap.find(identifier);
	auto firtstVar = function->second->GetFirstIdentifier();
	auto secondVar = function->second->GetSecondIdentifier();
	auto operation = function->second->GetOperator();

	if (operation == Function::Operations::NONE)
	{
		return CalculateValue(firtstVar);
	}
	auto firstValue = CalculateValue(firtstVar);
	auto secondValue = CalculateValue(secondVar);
	if (std::isnan(firstValue) || std::isnan(secondValue))
	{
		return NAN;
	}
	switch (operation)
	{
	case Function::Operations::ADD:
		return firstValue + secondValue;
	case Function::Operations::SUBSTRACT:
		return firstValue - secondValue;
	case Function::Operations::MULTIPLY:
		return firstValue * secondValue;
	case Function::Operations::DIVIDE:
		if (secondValue == 0)
		{
			throw std::invalid_argument("Division by zero");
		}
		return firstValue / secondValue;
	default:
		break;
	}
	return NAN;
}

std::map<std::string, double> Calculator::GetVars() const
{
	std::map<std::string, double> varValues;
	for (auto& var : m_varMap)
	{
		varValues[var.first] = var.second->GetValue();
	}
	return varValues;
}

std::map<std::string, double> Calculator::GetFuncs() const
{
	std::map<std::string, double> funcsMap;

	for (const auto& [name, funcPtr] : m_funcMap)
	{
		funcsMap[name] = CalculateFunction(name);
	}
	return funcsMap;
}

double Calculator::CalculateValue(const std::string& identifier) const
{
	auto variable = m_varMap.find(identifier);
	if (variable != m_varMap.end() && variable->second)
	{
		return variable->second->GetValue();
	}
	auto function = m_funcMap.find(identifier);
	if (function != m_funcMap.end())
	{
		return CalculateFunction(identifier);
	}
	return NAN;
}