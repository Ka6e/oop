#include "../../vector/include/VectorOperations.h"

DoubleVector ReadNumbers()
{
	std::vector<double> vector;
	std::string str;
	std::istringstream iss;
	double value;

	std::getline(std::cin, str);
	iss.str(str);
	while (iss >> value)
	{
		vector.push_back(value);
	}
	if (!iss.eof() || iss.bad())
	{
		throw std::runtime_error("ERROR\n");
	}
	if (vector.empty())
	{
		throw std::runtime_error("ERROR\n");
	}
	return vector;
}

DoubleVector ProcessNumbers(std::vector<double>& vec)
{
	double avg = std::accumulate(
		vec.begin(),
		vec.end(), 0.0, 
		[](double a, double b) { 
			return b > 0 ? a + b : a; 
		}
	);

	int count = std::count_if(vec.begin(), 
		vec.end(), 
		[](double x) {
			return x > 0; 
		}
	);

	if (count == 0)
	{
		return vec;
	}
	avg /= count;

	for (size_t i = 0; i < vec.size(); i++)
	{
		vec[i] += avg;
	}

	return vec;
}

void PrintSortedNumbers(std::vector<double>& vec)
{
	for (auto& el : vec)
	{
		std::cout << std::fixed << std::setprecision(3) << el << ' ';
	}
	std::cout << std::endl;
}

DoubleVector Sort(std::vector<double>& vec)
{
	std::sort(vec.begin(), vec.end());
	return vec;
}