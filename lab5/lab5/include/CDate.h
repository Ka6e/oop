#pragma once
#include <map>
#include <iostream>

enum class Month
{
    JANUARY = 1, 
    FEBRUARY, 
    MARCH, 
    APRIL,
    MAY, 
    JUNE, 
    JULY, 
    AUGUST, 
    SEPTEMBER,
    OCTOBER, 
    NOVEMBER, 
    DECEMBER
};

enum class WeekDay
{
    SUNDAY = 0, 
    MONDAY, 
    TUESDAY, 
    WEDNESDAY,
    THURSDAY, 
    FRIDAY, 
    SATURDAY
};

struct DateStruct
{
    unsigned day;
    Month month;
    unsigned year;
};

class CDate
{
public:
    CDate(unsigned day, Month month, unsigned year);
    explicit CDate(unsigned timestamp);
    CDate();
    
    unsigned GetDay()const;

    Month GetMonth()const;

    unsigned GetYear()const;

    WeekDay GetWeekDay()const;

    CDate& operator++();
    CDate operator++(int);
    CDate& operator--();
    CDate operator--(int);

    friend CDate operator+(const CDate& date ,int days);
	friend CDate operator+(int days, const CDate& date);
    friend CDate operator-(const CDate& date,int days);
    friend int operator-(const CDate& date1, const CDate& date2);
    CDate& operator+=(unsigned days);
    CDate& operator-=(unsigned days);

    friend std::ostream& operator<<(std::ostream& os, const CDate& date);
    friend std::istream& operator>>(std::istream& is, CDate& date);

    bool operator==(const CDate& other) const ;
    bool operator!=(const CDate& other) const ;
    bool operator>(const CDate& other) const ;
    bool operator<(const CDate& other) const ;
    bool operator>=(const CDate& other) const ;
    bool operator<=(const CDate& other) const ;

private:
	DateStruct m_dateStruct;
    unsigned m_timestamp;
    static const unsigned DAYS_IN_YEAR = 365;
	static const unsigned START_YEAR = 1970;
	static const WeekDay START_WEEKDAY = WeekDay::THURSDAY;
    static const unsigned MAX_TIMESTAMP = 2932896;
    static const unsigned MIN_TIMESTAMP = 0;
    static const unsigned DAYS_IN_WEEK = 7;
    static bool IsLeapYear(unsigned year);
    static unsigned GetDaysInMonth(Month month, unsigned year);
    static unsigned FromDateToTimestamp(unsigned day, Month month, unsigned year);
	DateStruct FromTimestampToDate() const;
};