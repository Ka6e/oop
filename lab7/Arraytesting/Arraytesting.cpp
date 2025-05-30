#define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "../CMyArray/include/CMyArray.h"
#include <string>

TEST_CASE("Empty array testing")
{
	CMyArray<int> arr;
	CHECK(arr.Size() == 0);
	CHECK(arr.GetCapacity() == 0);
}

TEST_CASE("Capacity constructor testing")
{
	CMyArray<int> arr(16);
	CHECK(arr.Size() == 0);
	CHECK(arr.GetCapacity() == 16);
}

TEST_CASE("Copy constructor")
{
	CMyArray<int> first(5);
	first.PushBack(1);
	first.PushBack(2);
	first.PushBack(3);
	first.PushBack(4);

	CMyArray<int> second(first);

	CHECK(second.Size() == 4);
	CHECK(second.GetCapacity() == 5);
	for (size_t i = 0; i < second.Size(); i++)
	{
		CHECK(second[i] == i + 1);
	}
}

TEST_CASE("Move constructor")
{
	CMyArray<int> first(4);
	first.PushBack(10);
	first.PushBack(4);
	CMyArray<int> second(std::move(first));
	CHECK(first.Size() == 0);
	CHECK(first.GetCapacity() == 0);
	CHECK(second.Size() == 2);
	CHECK(second.GetCapacity() == 4);
	CHECK(second[0] == 10);
	CHECK(second[1] == 4);
}

TEST_CASE("Int array testing")
{
	CMyArray<int> arr(5);
	CHECK(arr.Size() == 0);
	CHECK(arr.GetCapacity() == 5);
	arr.PushBack(4);
	CHECK(arr.Size() == 1);
	CHECK(arr[0] == 4);
}

TEST_CASE("Double array testing")
{
	CMyArray<double> arr;
	arr.PushBack(3.14);
	arr.PushBack(2.7);
	CHECK(arr.Size() == 2);
	CHECK(arr.GetCapacity() == 2);
	arr.PushBack(5);
	CHECK(arr.GetCapacity() == 4);
}

TEST_CASE("Float array testing")
{
	CMyArray<float> arr;
	arr.PushBack(3.14);
	arr.PushBack(2.7);
	CHECK(arr.Size() == 2);
	CHECK(arr.GetCapacity() == 2);
	arr.PushBack(5);
	CHECK(arr.GetCapacity() == 4);
}

TEST_CASE("String array testing")
{
	CMyArray<std::string> arr;
	arr.PushBack("Hello");
	arr.PushBack("World");
	CHECK(arr.GetCapacity() == 2);
	CHECK(arr.Size() == 2);
	CHECK(arr[0] == "Hello");
	CHECK(arr[1] == "World");
}

TEST_CASE("Array methods")
{
	GIVEN("Empty array")
	{
		CMyArray<int> arr;

		WHEN("Push back")
		{
			arr.PushBack(1);
			arr.PushBack(2);
			arr.PushBack(3);
			arr.PushBack(4);
			arr.PushBack(5);
			THEN("Capacity must be [8] & size [4]")
			{
				CHECK(arr.Size() == 5);
				CHECK(arr.GetCapacity() == 8);
			}
		}
		WHEN("Resize")
		{
			CMyArray<int> arr;
			arr.Resize(20);
			THEN("Capacity must be [20]")
			{
				CHECK(arr.GetCapacity() == 20);
				CHECK(arr.Size() == 0);
			}
		}
		WHEN("Clear")
		{
			CMyArray<int> arr;
			arr.PushBack(1);
			arr.PushBack(2);
			arr.Clear();
			THEN("Size must be [0]")
			{
				CHECK(arr.Size() == 0);
				CHECK(arr.GetCapacity() == 2);
			}
		}

		WHEN("Capasity")
		{
			CMyArray<int> arr(5);
			THEN("Capacity must be [5]")
			{
				CHECK(arr.GetCapacity() == 5);
			}
		}
		WHEN("Size")
		{
			CMyArray<int> arr(2);
			arr.PushBack(1);
			arr.PushBack(2);
			THEN("Size must be [2]")
			{
				CHECK(arr.Size() == 2);
			}
		}
	}
}

TEST_CASE("Copy operator")
{
	CMyArray<int> first(3);
	first.PushBack(4);
	first.PushBack(6);
	CMyArray<int> second;
	second = first;
	CHECK(second.Size() == 2);
	CHECK(second.GetCapacity() == 3);
	CHECK(std::addressof(first) != std::addressof(second));
}

TEST_CASE("Selfassignment")
{
	CMyArray<int> arr;
	arr.PushBack(45);
	arr.PushBack(100);
	arr = arr;
	CHECK(arr.Size() == 2);
	CHECK(arr.GetCapacity() == 2);
	CHECK(arr[0] == 45);
	CHECK(arr[1] == 100);
}

TEST_CASE("Move operator")
{
	CMyArray<int> arr;
	arr.PushBack(1);
	arr.PushBack(2);
	CMyArray<int> second;
	second = std::move(arr);
	CHECK(arr.Size() == 0);
	CHECK(arr.GetCapacity() == 0);
	CHECK(second.Size() == 2);
	CHECK(second.GetCapacity() == 2);
}

TEST_CASE("Iterator testing")
{
	GIVEN("Array with values")
	{
		CMyArray<int> arr(3);
		arr.PushBack(1);
		arr.PushBack(2);
		arr.PushBack(3);

		GIVEN("Default iterator")
		{

			SECTION("begin & end iterator")
			{
				auto it = arr.begin();
				CHECK(*it == 1);
				it += 3;
				CHECK(it == arr.end());
			}
			SECTION("Increment and decrement")
			{
				auto it = arr.begin();
				CHECK(*it == 1);
				++it;
				CHECK(*it == 2);
				++it;
				CHECK(*it == 3);
				--it;
				CHECK(*it == 2);
				--it;
				CHECK(*it == 1);
			}
			SECTION("Arithmetic operations")
			{
				auto it = arr.begin();
				it += 2;
				CHECK(*it == 3);
				it -= 2;
				CHECK(*it == 1);
			}
			SECTION("Write test")
			{
				auto it = arr.begin();
				*it = 10;
				CHECK(*arr.begin() == 10);
			}
		}
		GIVEN("Const Iterator")
		{ 
			SECTION("cbegin & cend iterator")
			{
				auto it = arr.cbegin();
				CHECK(*it == 1);
				it += 3;
				CHECK(it == arr.cend());
			}
			SECTION("Increment and decrement")
			{
				auto it = arr.cbegin();
				CHECK(*it == 1);
				++it;
				CHECK(*it == 2);
				++it;
				CHECK(*it == 3);
				--it;
				CHECK(*it == 2);
				--it;
				CHECK(*it == 1);
			}
			SECTION("Arithmetic operations")
			{
				auto it = arr.cbegin();
				it += 2;
				CHECK(*it == 3);
				it -= 2;
				CHECK(*it == 1);
			}
			SECTION("Read only acsess")
			{
				auto it = arr.cbegin();
				CHECK(*it == 1);
			}
		}
		GIVEN("Reverse Iterator")
		{
			SECTION("rbegin & rend iterator")
			{
				auto it = arr.rbegin();
				CHECK(*it == 3);
				it += 3;
				CHECK(it == arr.rend());
			}
			SECTION("Increment and decrement")
			{
				auto it = arr.rbegin();
				CHECK(*it == 3);
				++it;
				CHECK(*it == 2);
				it++;
				CHECK(*it == 1);
				--it;
				CHECK(*it == 2);
				it--;
				CHECK(*it == 3);
			}
			SECTION("Arithmetic operations")
			{
				auto it = arr.rbegin();
				it += 2;
				CHECK(*it == 1);
				it -= 2;
				CHECK(*it == 3);
			}
			SECTION("Write test")
			{
				auto it = arr.rbegin();
				*it = 4;
				CHECK(*arr.rbegin() == 4);
			}
		}
		GIVEN("ConstReverse Iterator")
		{ 
			SECTION("crbegin & crend iterator")
			{
				auto it = arr.crbegin();
				CHECK(*it == 3);
				it += 3;
				CHECK(it == arr.crend());
			}
			SECTION("Increment and decrement")
			{
				auto it = arr.crbegin();
				CHECK(*it == 3);
				++it;
				CHECK(*it == 2);
				it++;
				CHECK(*it == 1);
				--it;
				CHECK(*it == 2);
				it--;
				CHECK(*it == 3);
			}
			SECTION("Arithmetic operations")
			{
				auto it = arr.crbegin();
				it += 2;
				CHECK(*it == 1);
				it -= 2;
				CHECK(*it == 3);
			}
			SECTION("Read only acsess")
			{
				auto it = arr.crbegin();
				CHECK(*it== 3);
			}
		}
	}
}

TEST_CASE("Crash test")
{
	SECTION("Get value out of range")
	{
		CMyArray<int> arr;
		arr.PushBack(1);
		arr.PushBack(2);
		CHECK_THROWS_AS(arr[2], std::out_of_range);
	}
	SECTION("Get iterator out of range")
	{
		CMyArray<int> arr;
		arr.PushBack(1);
		arr.PushBack(2);
		auto it = arr.end();
		++it;
		CHECK_THROWS_AS(*it, std::out_of_range);
	}
	SECTION("Resize from a larger to a smaller size")
	{
		CMyArray<int> arr;
		arr.Resize(2);
		arr.PushBack(1);
		arr.PushBack(2);
		arr.Resize(1);
		CHECK(arr.GetCapacity() == 1);
		CHECK_THROWS_AS(arr[1], std::out_of_range);
	}
	SECTION("Resize from a larger to 0")
	{
		CMyArray<int> arr;
		arr.Resize(2);
		arr.PushBack(1);
		arr.PushBack(2);
		arr.Resize(0);
		CHECK(arr.GetCapacity() == 0);
		CHECK_THROWS_AS(arr[0], std::out_of_range);
	}
}