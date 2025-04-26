#define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "../Calculator/include/Calculator.h"

TEST_CASE("Declaring a variable")
{
	Calculator calculator;
	calculator.DeclareVariable("x");
	auto var = calculator.GetVars();
	CHECK(var.find("x") != var.end());
	CHECK(std::isnan(calculator.CalculateValue("x")));
}

TEST_CASE("Initialization of variable by value")
{
	Calculator calculator;
	calculator.InitVariable("y", 12.0);
	auto value = calculator.CalculateValue("y");
	CHECK(value == 12.0);
}
//сделать перегрузку
TEST_CASE("Initilization of variable by variable")
{
	Calculator calculator;
	calculator.InitVariable("x", 15.0);
	calculator.InitVariableWithIdentifier("y", "x");
	CHECK(calculator.CalculateValue("x") == 15.0);
	CHECK(calculator.CalculateValue("y") == 15.0);
}

TEST_CASE("Declaring function with nan variables")
{
	Calculator calculator;
	calculator.DeclareVariable("x");
	calculator.DeclareVariable("y");
	calculator.CreateFunction("XPlusY", "x", Function::Operations::ADD, "y");
	auto value = calculator.CalculateValue("XPlusY");
	CHECK(std::isnan(value));
}

TEST_CASE("Declaring function")
{
	Calculator calculator;
	calculator.InitVariable("x", 12.0);
	calculator.InitVariable("y", 5.0);
	calculator.CreateFunction("foo", "x", Function::Operations::ADD, "y");
	auto value = calculator.CalculateValue("foo");
	CHECK(value == 17.0);
}

TEST_CASE("Addiction function")
{
	Calculator calculator;
	calculator.InitVariable("x", 3.0);
	calculator.InitVariable("y", 4.0);
	calculator.CreateFunction("foo", "x", Function::Operations::ADD, "y");
	CHECK(calculator.CalculateValue("foo") == 7);
}

TEST_CASE("Assigning functions to a variable")
{
	Calculator calculator;
	calculator.InitVariable("v", 42.0);
	calculator.InitVariableWithIdentifier("var", "v");
	calculator.CreateFunctionithVariable("foo", "v");
	calculator.InitVariable("v", 56.0);
	CHECK(calculator.CalculateValue("var") == 42.0);
	CHECK(calculator.CalculateValue("foo") == 56.0);
}

TEST_CASE("Substruction function")
{
	Calculator calculator;
	calculator.InitVariable("x", 15.0);
	calculator.InitVariable("y", 20.0);
	calculator.CreateFunction("foo", "y", Function::Operations::SUBSTRACT, "x");
	CHECK(calculator.CalculateValue("foo") == 5.0);
}

TEST_CASE("Division function")
{
	Calculator calculator;
	calculator.InitVariable("x", 10.0);
	calculator.InitVariableWithIdentifier("y", "x");
	calculator.CreateFunction("foo", "y", Function::Operations::DIVIDE, "x");
	CHECK(calculator.CalculateValue("foo") == 1.0);
}

TEST_CASE("Multiplication funcion")
{
	Calculator calculator;
	calculator.InitVariable("x", 24.9);
	calculator.InitVariable("y", 3.5);
	calculator.CreateFunction("foo", "x", Function::Operations::MULTIPLY, "y");
	CHECK_THAT(calculator.CalculateValue("foo"), Catch::Matchers::WithinRel(87.15, 1e-9));
}

TEST_CASE("Division by zero")
{
	Calculator calculator;
	calculator.InitVariable("x", 24.9);
	calculator.InitVariable("y", 0);
	calculator.CreateFunction("foo", "x", Function::Operations::DIVIDE, "y");
	CHECK_THROWS(calculator.CalculateValue("foo"));
}

TEST_CASE("Get variables")
{
	Calculator calculator;
	calculator.DeclareVariable("x");
	calculator.DeclareVariable("y");
	calculator.InitVariable("z", 6.0);
	auto variable = calculator.GetVars();
	CHECK(variable.size() == 3);
	CHECK(variable["z"] ==  6.0);
}

TEST_CASE("Get functions")
{
	Calculator calculator;
	calculator.InitVariable("x", 5.0);
	calculator.InitVariable("y", 10.0);
	calculator.CreateFunction("add", "y", Function::Operations::ADD, "x");
	calculator.CreateFunction("sub", "y", Function::Operations::SUBSTRACT, "x");
	calculator.CreateFunction("mul", "x", Function::Operations::MULTIPLY, "y");
	calculator.CreateFunction("div", "y", Function::Operations::DIVIDE, "x");
	calculator.CreateFunctionithVariable("foo", "add");
	auto functions = calculator.GetFuncs();
	CHECK(functions.size() == 5);
	CHECK(functions["add"] == 15.0);
	CHECK(functions["sub"] == 5.0);
	CHECK(functions["mul"] == 50.0);
	CHECK(functions["div"] == 2.0);
	CHECK(functions["foo"] == 15.0);
}

TEST_CASE("")
{

}
//нужны ломающие тесты