#include "PrimeNumbersOperations.h"
#include <stdexcept>

const int MAX_NUMBER = 100000000;
const int MIN_NUMBER = 2;

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound < MIN_NUMBER || upperBound > MAX_NUMBER)
	{
		throw std::invalid_argument("Number out of range. Number must be 2 <= number <= 100000000\n");
	}

	std::vector<bool> isPrime(upperBound + 1, true);
	isPrime[0] = isPrime[1] = false;
	std::set<int> result;
	
	//–ешето Ёратосфена
	for (size_t i = MIN_NUMBER; i * i <= upperBound ; i++)
	{
		if (isPrime[i])
		{
			for (size_t j = i*i; j <= upperBound; j+= i)
			{
				isPrime[j] = false;
			}
		}
	}

	//в дргую функцию
	for (size_t i = MIN_NUMBER; i <= upperBound; i++)
	{
		if (isPrime[i])
		{
			result.insert(i);
		}
	}

	return result;
}