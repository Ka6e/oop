#pragma once
#include "./Function.h"
#include "./Variable.h"
#include <map>
#include <memory>

using VariableMap = std::map<std::string, std::unique_ptr<Variable>>;
using FunctionMap = std::map<std::string, std::unique_ptr<Function>>;


class Calculator
{
public:
	Calculator() = default;
	void DeclareVariable(const std::string& identifier);
	void InitVariable(const std::string& identifier, double value);
	void InitVariableWithIdentifier(const std::string& identifierFirts, const std::string& identifierSecond);
	void CreateFunction(const std::string& funcName, const std::string& firtVariable,
		Function::Operations operation, const std::string& secondVariable);
	void CreateFunctionithVariable(const std::string& funcName, const std::string& variable);
	double CalculateFunction(const std::string& identifier) const;
	std::map<std::string, double> GetVars() const;
	std::map<std::string, double> GetFuncs() const;
	double CalculateValue(const std::string& identifier) const;
private:
	Variable m_variable;
	Function m_function;
	VariableMap m_varMap;
	FunctionMap m_funcMap;
};
