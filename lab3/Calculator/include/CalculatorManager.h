#pragma once
#include "include/Calculator.h"

class CalculatorManager
{
public:

	enum class Actions
	{
		VAR,
		LET,
		FN,
		PRINT,
		PRINTVARS,
		PRINTFNS
	};

	CalculatorManager() = default;
	void RunCalculator();
private:
	Actions DefiningAction(const std::string& str);
	void PrintVariable(const std::string variable);
	void Var(const std::string& str);
	void InitVariable(const std::string& str);
	void DeclareFuncion(const std::string& str);
	void PrintFns() const;
	void PrintVars() const;
	Calculator m_calculator;
};
