#include "include/CalculatorManager.h"
#include <iostream>
#include <map>
#include <optional>
#include <sstream>
#include <iomanip>
#include <algorithm>

const std::string VAR = "var";
const std::string LET = "let";
const std::string FN = "fn";
const std::string PRINT = "print";
const std::string PRINT_VARS = "printvars";
const std::string PRINT_FNS = "printfns";

const std::string ADDITION = "+";
const std::string SUBTRACTION = "-";
const std::string DIVISION = "/";
const std::string MULTIPLICATION = "*";
const char EUALATION = '=';


std::string Trim(std::string& str)
{
	std::string result;
	std::remove_copy_if(str.begin(), str.end(), std::back_inserter(result), ::isspace);
	return result;
}

void ParseString(const std::string& source, std::string& name,
	std::string* firstVariable, std::string* operation, std::string* secondVariabe)
{
	size_t pos = source.find('=');
	if (pos == std::string::npos)
	{
		name = source;
		return;
	}
	name = source.substr(0, pos);
	size_t oper = source.find_first_of("+-/*");
	if (oper == std::string::npos || !firstVariable || !operation || !secondVariabe)
	{
		*firstVariable = source.substr(pos + 1);
		return;
	}
	*firstVariable = source.substr(pos + 1, oper - (pos + 1));
	*operation = source.substr(oper, 1);
	*secondVariabe = source.substr(oper + 1);
}

std::map<std::string, CalculatorManager::Actions> actionMap =
{
	{VAR, CalculatorManager::Actions::VAR},
	{LET, CalculatorManager::Actions::LET},
	{FN, CalculatorManager::Actions::FN},
	{PRINT, CalculatorManager::Actions::PRINT},
	{PRINT_VARS, CalculatorManager::Actions::PRINTVARS},
	{PRINT_FNS, CalculatorManager::Actions::PRINTFNS}
};

void CalculatorManager::PrintVariable(const std::string variable)
{

	auto var = m_calculator.GetVars();
	auto func = m_calculator.GetFuncs();
	if (var.find(variable) != var.end())
	{
		std::cout << std::fixed << std::setprecision(2) << var.at(variable) << std::endl;
		return;
	}
	if (func.find(variable) != func.end())
	{
		std::cout << std::fixed << std::setprecision(2) << func.at(variable) << std::endl;
		return;
	}
	else
	{
		std::cout << "Variable not found: " << variable << '\n';
	}
}

void CalculatorManager::Var(const std::string& str)
{
	std::string name;
	ParseString(str, name, nullptr, nullptr, nullptr);
	if (::isdigit(name[0]))
	{

	}
	if (!name.empty())
	{
		m_calculator.DeclareVariable(name);
	}
	else
	{
		std::cout << "Error: No variable name provided.\n";
	}
}

void CalculatorManager::InitVariable(const std::string& str)
{
	std::string name, variable;
	ParseString(str, name, &variable, nullptr, nullptr);

	try
	{
		double value = std::stod(variable);
		m_calculator.InitVariable(name, value);
		return;
	}
	catch (const std::exception&)
	{
		m_calculator.InitVariableWithIdentifier(name, variable);
	}
}

void CalculatorManager::DeclareFuncion(const std::string& str)
{
	std::string name, firstVariable, operation, secondVariable;
	ParseString(str, name, &firstVariable, &operation, &secondVariable);
	if (firstVariable.empty())
	{
		std::cerr << "Invalid usege" << std::endl;
		return;
	}
	if (operation.empty() || secondVariable.empty())
	{
		m_calculator.CreateFunctionithVariable(name, firstVariable);
		return;
	}
	Function::Operations op = Function::Operations::NONE;
	if (operation == ADDITION)
	{
		op = Function::Operations::ADD;
	}
	else if (operation == SUBTRACTION)
	{
		op = Function::Operations::SUBSTRACT;
	}
	else if (operation == DIVISION)
	{
		op = Function::Operations::DIVIDE;
	}
	else if (operation == MULTIPLICATION)
	{
		op = Function::Operations::MULTIPLY;
	}
	else
	{
		std::cout << "Unknown operation" << std::endl;
		return;
	}
	m_calculator.CreateFunction(name, firstVariable, op, secondVariable);
}

void CalculatorManager::PrintFns() const
{
	auto arrayFunc = m_calculator.GetFuncs();
	for (const auto& [name, value] : arrayFunc)
	{
		std::cout << name << ':' << std::fixed << std::setprecision(2) << value << std::endl;
	}
}

void CalculatorManager::PrintVars() const
{
	auto arrayVars = m_calculator.GetVars();
	for (const auto& [name, value] : arrayVars)
	{
		std::cout << name << ':' << std::fixed << std::setprecision(2) << value << std::endl;
	}
}

CalculatorManager::Actions CalculatorManager::DefiningAction(const std::string& str)
{
	auto action = actionMap.find(str);
	if (action != actionMap.end())
	{
		return action->second;
	}
	throw std::invalid_argument("Unknown command");
}

void CalculatorManager::RunCalculator()
{
	std::string str;
	while (std::getline(std::cin, str))
	{
		size_t pos = str.find(' ');
		std::string command, line;
		command = str.substr(0, pos);
		line = str.substr(pos + 1);
		line = Trim(line);
		switch (DefiningAction(command))
		{
		case Actions::VAR:
			Var(line);
			break;
		case Actions::LET:
			InitVariable(line);
			break;
		case Actions::FN:
			DeclareFuncion(line);
			break;
		case Actions::PRINT:
			PrintVariable(line);
			break;
		case Actions::PRINTVARS:
			PrintVars();
			break;
		case Actions::PRINTFNS:
			PrintFns();
			break;
		}
	}
}
