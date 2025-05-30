#include "../include/CDate.h"
#include <stdexcept>
#include <string>

const char SEPARATOR = '.';
const int MONTH_DAYS[2][12] = {
		{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334},
		{0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 }
};

CDate::CDate(unsigned day, Month month, unsigned year)
{
	if (year < START_YEAR)
	{
		throw std::invalid_argument("Invalid year");
	}
	if (day > GetDaysInMonth(month, year))
	{
		throw std::invalid_argument("Invalid day");
	}
	auto timestamp = FromDateToTimestamp(day, month, year);
	if (timestamp > MAX_TIMESTAMP)
	{
		throw std::out_of_range("Out of range");
	}
	m_timestamp = timestamp;
}

CDate::CDate(unsigned timestamp)
{
	if (timestamp > MAX_TIMESTAMP)
	{
		throw std::invalid_argument("Invalid timestamp");
	}
	m_timestamp = timestamp;
}

CDate::CDate() :m_timestamp(0)
{
}

unsigned CDate::GetDay() const
{
	return FromTimestampToDate().day;
}

Month CDate::GetMonth() const
{
	return FromTimestampToDate().month;
}

unsigned CDate::GetYear() const
{
	return FromTimestampToDate().year;
}

WeekDay CDate::GetWeekDay() const
{
	return static_cast<WeekDay>((m_timestamp + static_cast<unsigned>(START_WEEKDAY)) % DAYS_IN_WEEK);
}

CDate& CDate::operator++()
{
	if ((m_timestamp + 1) > MAX_TIMESTAMP)
	{
		throw std::out_of_range("Out of range");
	}
	++m_timestamp;
	return *this;
}

CDate CDate::operator++(int)
{
	CDate temp(*this);
	++(*this);
	return temp;
}

CDate& CDate::operator--()
{
	if ((static_cast<int>(m_timestamp) - 1) < 0)
	{
		throw std::out_of_range("Out of range");
	}
	--m_timestamp;
	return *this;
}

CDate CDate::operator--(int)
{
	CDate temp(*this);
	--(*this);
	return temp;
}

CDate& CDate::operator+=(unsigned days)
{
	if ((m_timestamp + days) > MAX_TIMESTAMP)
	{
		throw std::out_of_range("Out of range");
	}
	m_timestamp += days;
	return *this;
}

CDate& CDate::operator-=(unsigned days)
{
	if ((m_timestamp - days) < MIN_TIMESTAMP)
	{
		throw std::out_of_range("Out of range");
	}
	m_timestamp -= days;
	return *this;
}

CDate operator+(const CDate& date, int days)
{
	return CDate(date.m_timestamp + days);
}

CDate operator+(int days, const CDate& date)
{
	return CDate(date.m_timestamp + days);
}

CDate operator-(const CDate& date, int days)
{
	return CDate(date.m_timestamp - days);
}

int operator-(const CDate& date1, const CDate& date2)
{
	return date1.m_timestamp - date2.m_timestamp;
}

bool CDate::operator==(const CDate& other) const
{
	return m_timestamp == other.m_timestamp;
}

bool CDate::operator!=(const CDate& other) const
{
	return m_timestamp != other.m_timestamp;
}

bool CDate::operator>(const CDate& other) const
{
	return m_timestamp > other.m_timestamp;
}

bool CDate::operator<(const CDate& other)const
{
	return m_timestamp < other.m_timestamp;
}

bool CDate::operator>=(const CDate& other) const
{
	return m_timestamp >= other.m_timestamp;
}

bool CDate::operator<=(const CDate& other) const
{
	return m_timestamp <= other.m_timestamp;
}

std::ostream& operator<<(std::ostream& os, const CDate& date)
{
	os << date.GetDay() << SEPARATOR
		<< static_cast<int>(date.GetMonth()) << SEPARATOR
		<< date.GetYear();
	return os;
}

std::istream& operator>>(std::istream& is, CDate& date)
{
	std::string input;
	is >> input;
	size_t pos1 = input.find(SEPARATOR);
	size_t pos2 = input.find(SEPARATOR, pos1 + 1);
	if (pos1 == std::string::npos || pos2 == std::string::npos)
	{
		throw std::invalid_argument("Invalid date format");
	}
	unsigned day = std::stoi(input.substr(0, pos1));
	unsigned month = std::stoi(input.substr(pos1 + 1, pos2 - pos1 - 1));
	unsigned year = std::stoi(input.substr(pos2 + 1));
	date = CDate(day, static_cast<Month>(month), year);
	return is;
}

bool CDate::IsLeapYear(unsigned year)
{
	return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

unsigned CDate::GetDaysInMonth(Month month, unsigned year)
{
	switch (month)
	{
	case Month::JANUARY:
	case Month::MARCH:
	case Month::MAY:
	case Month::JULY:
	case Month::AUGUST:
	case Month::OCTOBER:
	case Month::DECEMBER:
		return 31;
	case Month::APRIL:
	case Month::JUNE:
	case Month::SEPTEMBER:
	case Month::NOVEMBER:
		return 30;
	case Month::FEBRUARY:
		return IsLeapYear(year) ? 29 : 28;
	default:
		return 0;
	}
}

unsigned CDate::FromDateToTimestamp(unsigned day, Month month, unsigned year)
{
	unsigned years = year - START_YEAR;
	unsigned days = years * DAYS_IN_YEAR + years / 4 - years / 100 + years / 400;
	if (IsLeapYear(year - 1))
	{
		days++;
	}
	return days + MONTH_DAYS[IsLeapYear(year)][static_cast<int>(month) - 1] + (day - 1);
}

DateStruct CDate::FromTimestampToDate() const
{
	unsigned year = (START_YEAR + 4 * m_timestamp / (DAYS_IN_YEAR * 4 + 1)) + 1;

	int days = static_cast<int>(m_timestamp - FromDateToTimestamp(1, Month::JANUARY, year) + 1);
	if (days < 0)
	{
		year--;
		days += static_cast<int>(DAYS_IN_YEAR + IsLeapYear(year));
	}
	int month;
	unsigned d = 0;

	for (month = 0; month < 12 && days > MONTH_DAYS[IsLeapYear(year)][month]; month++)
	{
		d = days - MONTH_DAYS[IsLeapYear(year)][month];
	}
	return { d, static_cast<Month>(month), year };
}

