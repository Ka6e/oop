#define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "../MyString/include/MyString.h"
#include <iostream>
#include <typeinfo>

TEST_CASE("Testing defalt constructor")
{
	CMyString string;
	CHECK(string.GetLength() == 0);
	CHECK(std::strcmp(string.GetStringData(), "") == 0);
	CHECK(string.GetCapacity() == 1);
}

TEST_CASE("Testing constructor with a string as a parameter")
{
	CMyString string("MyString");
	CHECK(string.GetLength() == 8);
	CHECK(string.GetCapacity() == 9);
	CHECK(std::strcmp(string.GetStringData(), "MyString") == 0);
}

TEST_CASE("Testing constructor with a char pointer as a parameter")
{
	const char* data = "MyString";
	CMyString string(data);
	CHECK(string.GetLength() == 8);
	CHECK(std::strcmp(string.GetStringData(), "MyString") == 0);
	CHECK(string.GetCapacity() == 9);
}

TEST_CASE("Testing constructor with length")
{
	const char* data = "My string";
	CMyString string(data, 2);
	CHECK(string.GetCapacity() == 3);
	CHECK(string.GetLength() == 2);
	CHECK(std::strcmp(string.GetStringData(), "My") == 0);
}

TEST_CASE("Testing copy constructor")
{
	CMyString str1("copy");
	CMyString str2(str1);
	CHECK(str1.GetStringData() != str2.GetStringData());
	CHECK(str1.GetLength() == str2.GetLength());
	CHECK(str1.GetCapacity() == str2.GetCapacity());
	CHECK(std::strcmp(str1.GetStringData(), str2.GetStringData()) == 0);
}

TEST_CASE("Testing move constructor")
{
	CMyString str1("Move Constructor");
	CMyString move(std::move(str1));
	CHECK(str1.GetCapacity() == 1);
	CHECK(str1.GetLength() == 0);
	CHECK(std::strcmp(str1.GetStringData(), "") == 0);
	CHECK(move.GetCapacity() == 17);
	CHECK(move.GetLength() == 16);
	CHECK(std::strcmp(move.GetStringData(), "Move Constructor") == 0);
}

TEST_CASE("Testing string methods")
{
	GIVEN("String with value")
	{
		CMyString str("Testing");

		WHEN("testing string length")
		{
			THEN("must return 7")
			{
				CHECK(str.GetLength() == 7);
			}
		}
		WHEN("testing string capacity")
		{
			THEN("must return 8")
			{
				CHECK(str.GetCapacity() == 8);
			}
		}
		WHEN("testing string data")
		{
			THEN("must return [Testing]")
			{
				CHECK(std::strcmp(str.GetStringData(), "Testing") == 0);
			}
		}
		WHEN("testing string substring")
		{
			CMyString sub(str.SubString(0, 3));
			THEN("must return [Tes]")
			{
				CHECK(std::strcmp(sub.GetStringData(), "Tes") == 0);
			}
			CMyString str("hello");
			THEN("must throw exception")
			{
				CHECK_THROWS(str.SubString(5, 50));
			}
		}
		WHEN("testing string clear")
		{
			CMyString clear(str);
			clear.Clear();
			THEN("must return empty string")
			{
				CHECK(clear.GetCapacity() == 1);
				CHECK(clear.GetLength() == 0);
				CHECK(std::strcmp(clear.GetStringData(), "") == 0);
			}
		}
	}
}

TEST_CASE("Testing string operators")
{
	GIVEN("String with value")
	{
		CMyString str("My string");

		WHEN("testing the addition of class")
		{
			CMyString hello("Hello world");
			THEN("must return [My stringHello world]")
			{
				CHECK(std::strcmp((str + hello).GetStringData(), "My stringHello world") == 0);
				CHECK(std::strcmp((hello + str).GetStringData(), "Hello worldMy string") == 0);
			}
		}
		WHEN("testing the addition of string")
		{
			std::string hello = "Hello world";
			THEN("must return [My stringHello world]")
			{
				CHECK(std::strcmp((str + hello).GetStringData(), "My stringHello world") == 0);
				CHECK(std::strcmp((hello + str).GetStringData(), "Hello worldMy string") == 0);
			}
		}
		WHEN("testing the addition of char*")
		{
			const char* hello = "Hello World!";
			THEN("must return [My stringHello World!]")
			{
				CHECK(std::strcmp((str + hello).GetStringData(), "My stringHello World!") == 0);
				CHECK(std::strcmp((hello + str).GetStringData(), "Hello World!My string") == 0);
			}
		}
		WHEN("testing the concationation")
		{
			CMyString data("Travel");
			CMyString result(str);
			result += data;
			THEN("must return [My stringTravel]")
			{
				CHECK(std::strcmp(result.GetStringData(), "My stringTravel") == 0);
			}
		}
		WHEN("testing the equality")
		{
			CMyString data("My string");
			THEN("must return true")
			{
				CHECK(str == data);
			}
		}
		WHEN("testing the inequality")
		{
			CMyString data("Test");
			THEN("must return true")
			{
				CHECK(str != data);
			}
		}
		WHEN("testing the <")
		{
			CMyString data("Test");
			THEN("must return return false")
			{
				CHECK(str < data);
			}
		}
		WHEN("testing the >")
		{
			CMyString data("Test");
			THEN("must return false")
			{
				CHECK_FALSE(str > data);
			}
		}
		WHEN("testing the <=")
		{
			CMyString data1("Tractor");
			CMyString data2("My string");
			THEN("must return true")
			{
				CHECK(str <= data1);
				CHECK(str <= data2);
			}
		}
		WHEN("testing the >=")
		{
			CMyString data1("Appel");
			CMyString data2("My string");
			THEN("must return false and true")
			{
				CHECK(str >= data1);
				CHECK(str >= data2);
			}
		}
		WHEN("testing the []")
		{
			CMyString data("hello");
			THEN("Reading characters by index")
			{
				CHECK(data[0] == 'h');
				CHECK(data[1] == 'e');
				CHECK(data[2] == 'l');
				CHECK(data[3] == 'l');
				CHECK(data[4] == 'o');
			}
			THEN("Modifying characters by index")
			{
				data[0] = 'H';
				data[1] = 'O';
				data[2] = 'L';
				CHECK(data[0] == 'H');
				CHECK(data[1] == 'O');
				CHECK(data[2] == 'L');
			}
		}
		WHEN("testing output operator")
		{
			std::ostringstream oss;
			oss << str;
			THEN("must return [My string]")
			{
				CHECK(oss.str() == "My string");
			}
		}
		WHEN("testing input operator")
		{
			CMyString data;
			std::istringstream iss("Hello world");
			iss >> data;
			THEN("must be [Hello world]")
			{
				CHECK(std::strcmp(data.GetStringData(), "Hello world") == 0);
			}
		}
	}
}

TEST_CASE("Testing empty string with equality operator")
{
	CMyString data1;
	CMyString data2;
	CHECK(data1 == data2);
	CHECK_FALSE(data1 != data2);
}

TEST_CASE("Testing out of range index")
{
	CMyString data("Hello");
	CHECK(data[0] == 'H');
	CHECK_THROWS(data[20]);
}

TEST_CASE("Testing concatenation with self")
{
	CMyString a("Test");
	a += a;
	CHECK(std::strcmp(a.GetStringData(), "TestTest") == 0);
}

TEST_CASE("Testing self-assignment")
{
	CMyString str("Hello");
	str = str;
	CHECK(str.GetLength() == 5);
	CHECK(std::strcmp(str.GetStringData(), "Hello") == 0);
}

TEST_CASE("Testing operator with empty stream")
{
	CMyString str;
	std::istringstream iss("");
	iss >> str;
	CHECK(str.GetLength() == 0);
	CHECK(std::strcmp(str.GetStringData(), "") == 0);
}

TEST_CASE("Testing substring with out of range")
{
	CMyString a("Hello");
	CHECK_THROWS(a.SubString(10, 20));
	CHECK_THROWS(a.SubString(0, 100));
}

TEST_CASE("Testing ensure deep copy")
{
	CMyString a("hello");
	CMyString b(a);
	a[0] = 'H';
	CHECK(b[0] == 'h');
}

TEST_CASE("Testing compare empry string")
{
	CMyString a;
	CMyString b;
	CHECK_FALSE(a > b);
	CHECK_FALSE(a < b);
	CHECK(a <= b);
	CHECK(a >= b);
}

TEST_CASE("Iterator testing")
{
	GIVEN("MyIterator operations")
	{
		CMyString str("hello");

		SECTION("Begin and end")
		{
			auto it = str.begin();
			CHECK(*it == 'h');
			CHECK(*(str.end() - 1) == 'o');
			CHECK(str.begin() != str.end());
		}

		SECTION("Increment and decrement")
		{
			auto it = str.begin();
			CHECK(*it == 'h');
			++it;
			CHECK(*it == 'e');
			it++;
			CHECK(*it == 'l');
			--it;
			CHECK(*it == 'e');
			it--;
			CHECK(*it == 'h');
		}

		SECTION("Arithmetic operations")
		{
			auto it = str.begin();
			it = it + 2;
			CHECK(*it == 'l');
			it = it - 1;
			CHECK(*it == 'e');
			it += 3;
			CHECK(*it == 'o');
			it -= 2;
			CHECK(*it == 'l');
		}

		SECTION("Comparison operations")
		{
			auto it1 = str.begin();
			auto it2 = str.begin() + 2;
			CHECK(it1 != it2);
			CHECK(it1 < it2);
			CHECK(it2 > it1);
			CHECK(it1 <= it2);
			CHECK(it2 >= it1);
			it2 -= 2;
			CHECK(it1 == it2);
			CHECK(it1 <= it2);
			CHECK(it1 >= it2);
		}

		SECTION("Difference operation")
		{
			auto it1 = str.begin();
			auto it2 = str.end();
			CHECK((it2 - it1) == 5);
			CHECK((it1 - it2) == -5);
		}

		SECTION("Write access")
		{
			auto it = str.begin();
			*it = 'H';
			CHECK(str.GetStringData() == std::string("Hello"));
		}
	}
	GIVEN("MyConstIterator operations")
	{
		const CMyString str("hello");

		SECTION("Begin and end")
		{
			auto it = str.cbegin();
			CHECK(*it == 'h');
			CHECK(*(str.cend() - 1) == 'o');
			CHECK(str.cbegin() != str.cend());
		}

		SECTION("Increment and decrement")
		{
			auto it = str.cbegin();
			CHECK(*it == 'h');
			++it;
			CHECK(*it == 'e');
			it++;
			CHECK(*it == 'l');
			--it;
			CHECK(*it == 'e');
			it--;
			CHECK(*it == 'h');
		}

		SECTION("Arithmetic operations")
		{
			auto it = str.cbegin();
			it = it + 2;
			CHECK(*it == 'l');
			it = it - 1;
			CHECK(*it == 'e');
			it += 3;
			CHECK(*it == 'o');
			it -= 2;
			CHECK(*it == 'l');
		}

		SECTION("Comparison operations")
		{
			auto it1 = str.cbegin();
			auto it2 = str.cbegin() + 2;
			CHECK(it1 != it2);
			CHECK(it1 < it2);
			CHECK(it2 > it1);
			CHECK(it1 <= it2);
			CHECK(it2 >= it1);
			it2 -= 2;
			CHECK(it1 == it2);
			CHECK(it1 <= it2);
			CHECK(it1 >= it2);
		}

		SECTION("Difference operation")
		{
			auto it1 = str.cbegin();
			auto it2 = str.cend();
			CHECK((it2 - it1) == 5);
			CHECK((it1 - it2) == -5);
		}

		SECTION("Read-only access")
		{
			auto it = str.cbegin();
			CHECK(*it == 'h');
		}
	}
	GIVEN("ReverseIterator operations")
	{ 
		CMyString str("hello");

		SECTION("Begin and end")
		{
			auto it = str.rbegin();
			CHECK(*it == 'o');
			CHECK(*(--str.rend()) == 'h');
			CHECK(str.rbegin() != str.rend());
		}

		SECTION("Increment and decrement")
		{
			auto it = str.rbegin();
			CHECK(*it == 'o');
			++it;
			CHECK(*it == 'l');
			it++;
			CHECK(*it == 'l');
			--it;
			CHECK(*it == 'l');
			it--;
			CHECK(*it == 'o');
		}

		SECTION("Arithmetic operations")
		{
			auto it = str.rbegin();
			it = it + 2;
			CHECK(*it == 'l');
			it = it - 1;
			CHECK(*it == 'l');
			it += 3;
			CHECK(*it == 'h');
			it -= 2;
			CHECK(*it == 'l');
		}

		SECTION("Write access")
		{
			auto it = str.rbegin();
			*it = 'O';
			CHECK(str.GetStringData() == std::string("hellO"));
		}
	}
	GIVEN("ConstReverseIterator operations")
	{
		const CMyString str("hello");

		SECTION("Begin and end")
		{
			auto it = str.crbegin();
			REQUIRE(*it == 'o');
			REQUIRE(*(str.crend() - 1) == 'h');
			REQUIRE(str.crbegin() != str.crend());
		}

		SECTION("Increment and decrement")
		{
			auto it = str.crbegin();
			REQUIRE(*it == 'o');
			++it;
			REQUIRE(*it == 'l');
			it++;
			REQUIRE(*it == 'l');
			--it;
			REQUIRE(*it == 'l');
			it--;
			REQUIRE(*it == 'o');
		}

		SECTION("Arithmetic operations")
		{
			auto it = str.crbegin();
			it = it + 2;
			REQUIRE(*it == 'l');
			it = it - 1;
			REQUIRE(*it == 'l');
			it += 3;
			REQUIRE(*it == 'h');
			it -= 2;
			REQUIRE(*it == 'l');
		}
		SECTION("Read-only access")
		{
			auto it = str.crbegin();
			REQUIRE(*it == 'o');
		}
	}
	SECTION("Iterator compatibility with range-based for")
	{
		CMyString str("Hello");
		std::string result;

		for (auto it = str.begin(); it != str.end(); it++)
		{
			result += *it;
		}
		CHECK(str.GetStringData() == result);
	}
}
