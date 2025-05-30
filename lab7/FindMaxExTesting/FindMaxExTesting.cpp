#define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "../FindMaxEx/include/FindMaxEx.h"

TEST_CASE("FindMaxEx with empty vector")
{
	std::vector<int> vec{};
	int max;
	auto less = std::less<int>{};
	CHECK_FALSE(FindMaxEx(vec, max, less));
}

TEST_CASE("FindMaxEx with one value")
{
	std::vector<int> vec{ 5 };
	int max;
	auto less = std::less<int>{};
	CHECK(FindMaxEx(vec, max, less));
	CHECK(max == 5);
}

TEST_CASE("FindMaxEx with double")
{
	std::vector<double> vec{ 3.14, 2.7, 14.5354, 0.1651 };
	double max;
	auto less = std::less<double>{};
	CHECK(FindMaxEx(vec, max, less));
	CHECK(max == 14.5354);
}

TEST_CASE("FindMaxEx with float")
{
	std::vector<float> vec{ 3.14f, 2.7f, 14.5354f, 0.1651f };
	float max;
	auto less = std::less<float>{};
	CHECK(FindMaxEx(vec, max, less));
	CHECK(max == 14.5354f);
}

TEST_CASE("FindMaxEx with int")
{
	std::vector<int> vec = { 1, 5, 3, 8, 2 };
	int maxValue = 0;
	auto less = std::less<int>{};
	CHECK(FindMaxEx(vec, maxValue, less));
	CHECK(maxValue == 8);
}

TEST_CASE("FindMaxEx with char")
{
	std::vector<char> vec = { 'z', 'x', 'c', 'a' };
	char max;
	auto less = std::less<char>{};
	CHECK(FindMaxEx(vec, max, less));
	CHECK(max == 'z');
}

TEST_CASE("FindMaxEx with string")
{
	std::vector<std::string> vec{ "abc", "hello", "World", "Zurich" };
	std::string max;
	auto less = std::less<std::string>{};
	CHECK(FindMaxEx(vec, max, less));
	CHECK(max == "hello");
}

TEST_CASE("FindMaxEx max height")
{
	std::vector<Person> persons = {
		{"Mike Tyson", 100.0, 186.0},
		{"Keanu Reeves", 76.8, 171.0},
		{"Tyler Durden", 75.8, 168.0},
		{"Serena Williams", 70.0, 175.0},
		{"Usain Bolt", 94.0, 195.0},
		{"Lionel Messi", 72.0, 170.0},
		{"Simone Biles", 47.0, 142.0},
		{"LeBron James", 113.0, 206.0},
		{"Maria Sharapova", 68.0, 188.0},
		{"Conor McGregor", 77.0, 175.0},
		{"Shaquille O'Neal", 147.0, 216.0},
		{"Hiroshi Yama", 200.0, 190.0}
	};
	Person tallest;
	CHECK(FindMaxEx(persons, tallest,
		[](const Person& first, const Person& second)
		{
			return first.m_height < second.m_height;
		}));
	CHECK(tallest == Person("Shaquille O'Neal", 147.0, 216.0));
}

TEST_CASE("FindMaxEx max weight")
{
	std::vector<Person> persons = {
		{"Mike Tyson", 100.0, 186.0},
		{"Keanu Reeves", 76.8, 171.0},
		{"Tyler Durden", 75.8, 168.0},
		{"Serena Williams", 70.0, 175.0},
		{"Usain Bolt", 94.0, 195.0},
		{"Lionel Messi", 72.0, 170.0},
		{"Simone Biles", 47.0, 142.0},
		{"LeBron James", 113.0, 206.0},
		{"Maria Sharapova", 68.0, 188.0},
		{"Conor McGregor", 77.0, 175.0},
		{"Shaquille O'Neal", 147.0, 216.0},
		{"Hiroshi Yama", 200.0, 190.0}
	};
	Person fat;
	CHECK(FindMaxEx(persons, fat,
		[](const Person& first, const Person& second)
		{
			return first.m_weight < second.m_weight;
		}));
	CHECK(fat == Person("Hiroshi Yama", 200.0, 190.0));
}

TEST_CASE("FindMaxEx with equal heights")
{
	std::vector<Person> persons = {
		{"Mike Tyson", 100.0, 186.0},
		{"Shaquille O'Neal", 147.0, 216.0},
		{"Hiroshi Yama", 200.0, 216.0} 
	};
	Person tallest;
	CHECK(FindMaxEx(persons, tallest, 
		[](const Person& first, const Person& second)
		{
			return first.m_height < second.m_height;
		}));
	CHECK(tallest == Person("Shaquille O'Neal", 147.0, 216.0));
}

TEST_CASE("FindMaxEx with equal weight")
{
	std::vector<Person> persons = {
		{"Mike Tyson", 100.0, 186.0},
		{"Shaquille O'Neal", 200.0, 216.0},
		{"Hiroshi Yama", 200.0, 216.0}
	};
	Person fat;
	CHECK(FindMaxEx(persons, fat,
		[](const Person& first, const Person& second)
		{
			return first.m_weight < second.m_weight;
		}));
	CHECK(fat == Person("Shaquille O'Neal", 200.0, 216.0));
}

//exception 