#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <string>

using DoubleVector = std::vector<double>;
DoubleVector ReadNumbers();
DoubleVector ProcessNumbers(std::vector<double>& vec);
void PrintSortedNumbers(std::vector<double>& vec);
DoubleVector Sort(std::vector<double>& vec);