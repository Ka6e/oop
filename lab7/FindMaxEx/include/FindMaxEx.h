#pragma once
#include <string>
#include <vector>
#include <format>
#include <iostream>

struct Person
{
	std::string m_name;
	double m_weight = 0;
	double m_height = 0;
	Person() = default;
	Person(const std::string& name, double weight, double height)
		: m_name(name), m_weight(weight), m_height(height){}

	bool operator==(Person const& other) const noexcept
	{
		return m_name == other.m_name 
			&& m_weight == other.m_weight
			&& m_height == other.m_height;
	}
};


bool CompareWeight(const Person& first, const Person& second)
{
	return first.m_weight < second.m_weight;
}
bool CompareHeight(const Person& firts, const Person& second)
{
	return firts.m_height < second.m_height;
}

template <typename T, typename Less>
bool FindMaxEx(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}
	//проверка на exception
	T tempMaxVal = arr[0];
	for (const auto& elem : arr)
	{
		if (less(tempMaxVal, elem))
		{
			tempMaxVal = elem;
		}
	}
	maxValue = tempMaxVal;
	return true;
}

void PrintMaxWeight(const std::vector<Person>& vec)
{
	Person fat;
	if (FindMaxEx(vec, fat, CompareWeight))
	{
		std::cout << std::format("The most fat is {} and his weight: {}",
			fat.m_name, fat.m_weight) << std::endl;
	}
	else
	{
		std::cout << "No one found" << std::endl;
	}
}

void PrintMaxHeight(const std::vector<Person>& vec)
{
	Person tallset;
	if (FindMaxEx(vec, tallset, CompareHeight))
	{
		std::cout <<
			std::format("The most tallest person is {} and his height: {}",
				tallset.m_name, tallset.m_height)
			<< std::endl;
	}
	else
	{
		std::cout << "No one found";
	}
}