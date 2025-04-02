#include "../../PrimeNumbers/include/PrimeNumbersOperations.h"
#include <stdexcept>

const int MAX_NUMBER = 100000000;
const int MIN_NUMBER = 2;


std::set<int> FillSet(std::vector<bool>& vec, int upperBound)
{
	std::set<int> primes;
	for (size_t i = 0; i <= upperBound ; i++)
	{
		if (vec[i])
		{
			primes.insert(i);
		}
	}

	return primes;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound < MIN_NUMBER || upperBound > MAX_NUMBER)
	{
		throw std::invalid_argument("Number out of range. Number must be 2 <= number <= 100000000\n");
	}

	std::vector<bool> isPrime(upperBound + 1, true);
	isPrime[0] = isPrime[1] = false;
	std::set<int> result;
	
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

	return FillSet(isPrime, upperBound);
}