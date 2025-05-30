#define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "../lab5/include/CDate.h"

TEST_CASE("Default date constructor")
{
	CDate date1;	
	CHECK(date1.GetDay() == 1);
	CHECK(date1.GetMonth() == Month::JANUARY);
	CHECK(date1.GetYear() == 1970);
	CHECK(date1.GetWeekDay() == WeekDay::THURSDAY);
}

TEST_CASE("Date timestamp constructor")
{
	CDate date(0);
	CHECK(date.GetDay() == 1);
	CHECK(date.GetMonth() == Month::JANUARY);
	CHECK(date.GetYear() == 1970);
	CHECK(date.GetWeekDay() == WeekDay::THURSDAY);
}

TEST_CASE("Date constructor with day, month, year")
{
	CDate date(1, Month::JANUARY, 1970);
	CHECK(date.GetDay() == 1);
	CHECK(date.GetMonth() == Month::JANUARY);
	CHECK(date.GetYear() == 1970);
	CHECK(date.GetWeekDay() == WeekDay::THURSDAY);
}

TEST_CASE("Date constructor with invalid date")
{
	CHECK_THROWS(CDate(32, Month::JANUARY, 1970));
	CHECK_THROWS(CDate(1, Month::JANUARY, 1969));
	CHECK_THROWS(CDate(1, Month::FEBRUARY, 10000));
}

TEST_CASE("NotZeroTimestampConstructor")
{
	auto date = CDate(19832);

	CHECK(date.GetDay() == 19);
	CHECK(date.GetMonth() == Month::APRIL);
	CHECK(date.GetWeekDay() == WeekDay::FRIDAY);
	CHECK(date.GetYear() == 2024);
}

TEST_CASE("Constructor throws on invalid timestamp") 
{
	CHECK_THROWS(CDate(3000000));
	CHECK_THROWS(CDate(-1)); 
}

TEST_CASE("Post/Pre increment/decrement operators") 
{
	CDate date(1, Month::JANUARY, 2024);

	SECTION("++date") 
	{
		++date;
		CHECK(date == CDate(2, Month::JANUARY, 2024));
	}
	SECTION("date++") 
	{
		date++;
		CHECK(date == CDate(2, Month::JANUARY, 2024));
	}
	SECTION("--date") 
	{
		--date;
		CHECK(date == CDate(31, Month::DECEMBER, 2023));
	}
	SECTION("date--") 
	{
		date--;
		CHECK(date == CDate(31, Month::DECEMBER, 2023));
	}
}

TEST_CASE("Date arithmetic: +, -, +=, -=") 
{
	CDate date(1, Month::JANUARY, 2024);

	date = date + 10;
	CHECK(date == CDate(11, Month::JANUARY, 2024));

	date += 21;
	CHECK(date == CDate(1, Month::FEBRUARY, 2024));

	date = date - 10;
	CHECK(date == CDate(22, Month::JANUARY, 2024));

	date -= 22;
	CHECK(date == CDate(31, Month::DECEMBER, 2023));
}

TEST_CASE("Addition and subtraction beyond bounds") 
{
	auto maxDate = CDate(31, Month::DECEMBER, 9999);
	CHECK_THROWS(maxDate + 1);
	CHECK_THROWS(++maxDate);

	auto minDate = CDate(); 
	CHECK_THROWS(minDate - 1);
	CHECK_THROWS(--minDate);
}

TEST_CASE("Subtraction between two dates") 
{
	CDate d1(1, Month::JANUARY, 2024);
	CDate d2(10, Month::JANUARY, 2024);

	CHECK(d2 - d1 == 9);
	CHECK(d1 - d2 == -9);
}

TEST_CASE("Comparison operators") 
{
	CDate d1(1, Month::JANUARY, 2024);
	CDate d2(10, Month::JANUARY, 2024);
	CDate d3(10, Month::JANUARY, 2024);

	CHECK(d1 < d2);
	CHECK(d2 > d1);
	CHECK(d2 == d3);
	CHECK(d1 != d2);
	CHECK(d1 <= d2);
	CHECK(d2 >= d1);
	CHECK(d2 <= d3);
	CHECK(d2 >= d3);
}

TEST_CASE("Stream output operator <<") 
{
	CDate date(15, Month::FEBRUARY, 2023);
	std::ostringstream oss;
	oss << date;
	CHECK(oss.str() == "15.2.2023");
}

TEST_CASE("Stream input operator >> with valid data") 
{
	std::istringstream iss("25.12.2022");
	CDate date;
	iss >> date;

	CHECK_FALSE(iss.fail());
	CHECK(date.GetDay() == 25);
	CHECK(date.GetMonth() == Month::DECEMBER);
	CHECK(date.GetYear() == 2022);
}

TEST_CASE("Stream input operator >> with invalid data") 
{
	std::istringstream iss("25.2022");
	CDate date;
	CHECK_THROWS_AS(iss >> date, std::invalid_argument);
}

TEST_CASE("Leap Year")
{
	CHECK_NOTHROW(CDate(29, Month::FEBRUARY, 2020));
	CHECK_NOTHROW(CDate(29, Month::FEBRUARY, 2000));
	CHECK_THROWS_AS(CDate(29, Month::FEBRUARY, 2019), std::invalid_argument);
	CHECK_THROWS_AS(CDate(29, Month::FEBRUARY, 2100), std::invalid_argument);
	CHECK_NOTHROW(CDate(18312));
	CHECK_NOTHROW(CDate(18313));
}