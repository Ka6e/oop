#pragma once
#include <stack>
#include <stdexcept>
#include <iostream>
#include <unordered_map>
#include <sstream>


struct  Expression
{
	char operation;
	std::vector<int> args;
};

int Calculate(char ch, std::vector<int>& vec);
int Evaluate();