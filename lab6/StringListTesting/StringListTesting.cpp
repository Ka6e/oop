#define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "../StringList//include//CStringList.h"

TEST_CASE("Default constructor testing")
{
	CStringList list;
	CHECK(list.Size() == 0);
	CHECK(list.IsEmpty());
}

TEST_CASE("Copy constructor testing")
{
	CStringList firstList("Herbert");
	CStringList secondList(firstList);

	SECTION("Checking list size")
	{
		CHECK(firstList.Size() == 1);
		CHECK(secondList.Size() == 1);
	}
	SECTION("Checking begin and end iterator")
	{
		CHECK(firstList.begin() != firstList.end());
		CHECK(secondList.begin() != secondList.end());
	}
	SECTION("Checkong the value of lists")
	{
		CHECK(*firstList.begin() == "Herbert");
		CHECK(*secondList.begin() == "Herbert");
	}
}

TEST_CASE("Move constructor testing")
{
	CStringList firstList("Hello");
	CStringList secondList(std::move(firstList));

	SECTION("Cheching size")
	{
		CHECK(firstList.Size() == 0);
		CHECK(secondList.Size() == 1);
	}
	SECTION("Checking the value")
	{
		CHECK(firstList.IsEmpty());
		CHECK_FALSE(secondList.IsEmpty());
		CHECK(*secondList.begin() == "Hello");
	}
}

TEST_CASE("Value constructor testing")
{
	CStringList list("May");

	CHECK(list.Size() == 1);
	CHECK_FALSE(list.IsEmpty());
	CHECK(*list.begin() == "May");
}

TEST_CASE("Copy operator testing")
{
	CStringList first("May");
	CStringList second;
	second = first;
	CHECK_FALSE(second.IsEmpty());
	CHECK(second.Size() == 1);
	CHECK(*second.begin() == "May");
	CHECK(first.begin() != second.begin());
}

TEST_CASE("Move operator testing")
{
	CStringList first("Summer");
	CStringList second;
	second = std::move(first);
	CHECK(first.Size() == 0);
	CHECK(second.Size() == 1);
	CHECK(*second.begin() == "Summer");
}

TEST_CASE("Testing methods")
{
	GIVEN("List with value")
	{
		CStringList list("Hello");

		WHEN("Push back")
		{
			list.PushBack("Value");
			THEN("Size must be 2 & first value[Hello] second value[Value]")
			{
				CHECK(list.Size() == 2);
				auto it = list.begin();
				CHECK(*it == "Hello");
				++it;
				CHECK(*it == "Value");
			}
		}

		WHEN("Push front")
		{
			list.PushFront("FirstVal");
			THEN("Size must be 2 & first value[FirstVal] second value [Hello]")
			{
				CHECK(list.Size() == 2);
				auto it = list.begin();
				CHECK(*it == "FirstVal");
				++it;
				CHECK(*it == "Hello");
			}
		}
		WHEN("Pop front & Pop back")
		{
			list.PushBack("One");
			list.PushBack("Two");
			list.PushFront("Three");
			list.PopBack();
			THEN("Last iterator must return [One]")
			{
				CHECK(list.Size() == 3);
				auto it = list.end();
				CHECK(*(--it) == "One");
			}
			list.PopFront();
			THEN("First iterator must return [Hello]")
			{
				CHECK(*list.begin() == "Hello");
			}
		}
		WHEN("Size")
		{
			THEN("Must return [1]")
			{
				CHECK(list.Size() == 1);
			}
		}
		WHEN("IsEmpty")
		{
			THEN("Must return false")
			{
				CHECK_FALSE(list.IsEmpty());
			}
		}
	}
}

TEST_CASE("Iterator testing")
{
	GIVEN("List with values")
	{
		CStringList list;
		list.PushBack("One");
		list.PushBack("Two");
		list.PushBack("Three");

		GIVEN("Default Iterator")
		{
			SECTION("Begin and end")
			{
				auto it = list.begin();
				CHECK(*it == "One");
				CHECK(*(--list.end()) == "Three");
				CHECK(list.begin() != list.end());
			}

			SECTION("Increment and decrement")
			{
				auto it = list.begin();
				CHECK(*it == "One");
				++it;
				CHECK(*it == "Two");
				it++;
				CHECK(*it == "Three");
				--it;
				CHECK(*it == "Two");
				it--;
				CHECK(*it == "One");
			}

			SECTION("Comparison operations")
			{
				auto it = list.begin();
				++it;
				CHECK(it != list.begin());
				--it;
				CHECK(it == list.begin());
			}

			SECTION("Write access")
			{
				auto it = list.begin();
				*it = "Hello";
				CHECK(*(list.begin()) == "Hello");
			}
		}
		GIVEN("Const iterator")
		{
			SECTION("Begin and end")
			{
				auto it = list.cbegin();
				CHECK(*it == "One");
				CHECK(*(--list.end()) == "Three");
				CHECK(list.cbegin() != list.cend());
			}

			SECTION("Increment and decrement")
			{
				auto it = list.cbegin();
				CHECK(*it == "One");
				++it;
				CHECK(*it == "Two");
				it++;
				CHECK(*it == "Three");
				--it;
				CHECK(*it == "Two");
				it--;
				CHECK(*it == "One");
			}

			SECTION("Comparison operations")
			{
				auto it = list.begin();
				++it;
				CHECK(it != list.begin());
				--it;
				CHECK(it == list.begin());
			}

			SECTION("Read-only access")
			{
				auto it = list .cbegin();
				CHECK(*it == "One");
			}
		}
		GIVEN("Reverse iterator")
		{
			SECTION("Begin and end")
			{
				auto it = list.rbegin();
				CHECK(*it == "Three");
				CHECK(*(--list.rend()) == "One");
				CHECK(list.rbegin() != list.rend());
			}

			SECTION("Increment and decrement")
			{
				auto it = list.rbegin();
				CHECK(*it == "Three");
				++it;
				CHECK(*it == "Two");
				it++;
				CHECK(*it == "One");
				--it;
				CHECK(*it == "Two");
				it--;
				CHECK(*it == "Three");
			}

			SECTION("Write access")
			{
				auto it = list.rbegin();
				*it = "HELLO";
				CHECK(*(list.rbegin()) == "HELLO");
			}
		}
		GIVEN("Const Reverse iterator")
		{
			SECTION("Begin and end")
			{
				auto it = list.crbegin();
				CHECK(*it == "Three");
				CHECK(*(--list.crend()) == "One");
				CHECK(list.crbegin() != list.crend());
			}

			SECTION("Increment and decrement")
			{
				auto it = list.crbegin();
				CHECK(*it == "Three");
				++it;
				CHECK(*it == "Two");
				it++;
				CHECK(*it == "One");
				--it;
				CHECK(*it == "Two");
				it--;
				CHECK(*it == "Three");
			}

			SECTION("Write access")
			{
				auto it = list.crbegin();
				CHECK(*(list.crbegin()) == "Three");
			}
		}
	}
}

TEST_CASE("PopBack & PopFront empty list")
{
	CStringList list;
	CHECK_THROWS_AS(list.PopBack(), std::runtime_error);
	CHECK_THROWS_AS(list.PopFront(), std::runtime_error);
}