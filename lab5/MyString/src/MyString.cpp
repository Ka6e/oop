#include "../include/MyString.h"
#include <stdexcept>
#include <iostream>

char CMyString::emptyString[1] = { '\0' };

CMyString::CMyString() : CMyString(emptyString, 0)
{}

CMyString::CMyString(const char* pString) : CMyString(pString, strlen(pString))
{}

CMyString::CMyString(const char* pString, size_t length) 
	: m_length(length),
	m_capacity(length + 1)
{
	m_pString = new char[m_capacity];
	strncpy_s(m_pString, m_capacity, pString, length);
	m_pString[m_length] = endString;
}

CMyString::CMyString(CMyString const& other) 
	: CMyString(other.GetStringData(), other.GetLength())
{
}

CMyString::CMyString(CMyString&& other) noexcept
	: m_pString(other.m_pString),
	m_length(other.m_length),
	m_capacity(other.m_capacity)
{
	other.m_pString = emptyString;
	other.m_length = 0;
	other.m_capacity = 1;
}

CMyString::CMyString(std::string const& stlString)
	: CMyString(stlString.c_str(), stlString.length())
{
}

CMyString::~CMyString()
{
	if (m_pString != emptyString)
	{
		delete[] m_pString;
	}
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	return m_pString;
}
//assert в ифке
CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_length)
	{
		throw std::out_of_range("Start index is greater than length");
	}
	if (length > m_length)
	{
		throw std::out_of_range("End index is greater than length");
	}
	if ((start + length) > m_length)
	{
		length = m_length - start;
	}
	return { &m_pString[start], length };
}

size_t CMyString::GetCapacity()
{
	return m_capacity;
}

CMyString& CMyString::operator=(const CMyString& other)
{
	if (this != &other)
	{
		CMyString temp(other);
		std::swap(m_pString, temp.m_pString);
		std::swap(m_length, temp.m_length);
		std::swap(m_capacity, temp.m_capacity);
	}
	return *this;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (this != &other)
	{
		delete[] m_pString;
		m_pString = other.m_pString;
		m_length = other.m_length;
		m_capacity = other.m_capacity;
		other.m_pString = emptyString;
		other.m_length = 0;
		other.m_capacity = 1;
	}
	return *this;
}

CMyString& CMyString::operator+=(const CMyString& other)
{
	size_t newLength = m_length + other.m_length;
	if (newLength >= m_capacity)
	{
		m_capacity = newLength + 1;
		char* newString = new char[m_capacity];
		strncpy_s(newString, m_capacity, m_pString, m_length);
		strncpy_s(newString + m_length, m_capacity - m_length, other.m_pString, other.m_length);
		delete[] m_pString;
		m_pString = newString;
	}
	else
	{
		strncpy_s(m_pString + m_length, m_capacity - m_length, other.m_pString, other.m_length);
	}
	m_length = newLength;
	m_pString[m_length] = endString;
	return *this;

}

const char& CMyString::operator[](size_t index) const
{
	if (index >= m_length)
	{
		throw std::out_of_range("Index is out of range");
	}
	return m_pString[index];
}

char& CMyString::operator[](size_t index)
{
	if (index >= m_length)
	{
		throw std::out_of_range("Index is out of range");
	}
	return m_pString[index];
}

CMyString::MyIterator CMyString::begin()
{
	return MyIterator(m_pString);
}

CMyString::MyIterator CMyString::end()
{
	return MyIterator(m_pString + m_length);
}

CMyString::ReverseIterator CMyString::rbegin()
{
	return ReverseIterator(end());
}

CMyString::ReverseIterator CMyString::rend()
{
	return ReverseIterator(begin());
}

CMyString::MyConstIterator CMyString::cbegin() const
{
	return MyConstIterator(m_pString);
}

CMyString::MyConstIterator CMyString::cend() const
{
	return MyConstIterator(m_pString + m_length);
}

CMyString::ConstReverseIterator CMyString::crbegin() const
{
	return ConstReverseIterator(cend());
}

CMyString::ConstReverseIterator CMyString::crend() const
{
	return ConstReverseIterator(cbegin());
}

void CMyString::Clear()
{
	delete[] m_pString;
	m_pString = new char[1];
	m_pString[0] = endString;
	m_length = 0;
	m_capacity = 1;
}

CMyString operator+(CMyString const& myString1, CMyString const& myString2)
{
	CMyString result;
	result.m_length = myString1.m_length + myString2.m_length;
	result.m_capacity = result.m_length + 1;
	result.m_pString = new char[result.m_capacity];
	strncpy_s(result.m_pString, result.m_capacity, myString1.m_pString, myString1.m_length);
	strncpy_s(result.m_pString + myString1.m_length, result.m_capacity - myString1.m_length, myString2.m_pString, myString2.m_length);
	result.m_pString[result.m_length] = CMyString::endString;
	return result;
}

CMyString operator+(std::string const& string1, CMyString const& myString2)
{
	CMyString result;
	result.m_length = string1.length() + myString2.m_length;
	result.m_capacity = result.m_length + 1;
	result.m_pString = new char[result.m_capacity];
	strncpy_s(result.m_pString, result.m_capacity, string1.c_str(), string1.length());
	strncpy_s(result.m_pString + string1.length(), result.m_capacity - string1.length(), myString2.m_pString, myString2.m_length);
	result.m_pString[result.m_length] = CMyString::endString;
	return result;
}

CMyString operator+(char const* string1, CMyString const& myString2)
{
	CMyString result;
	result.m_length = strlen(string1) + myString2.m_length;
	result.m_capacity = result.m_length + 1;
	result.m_pString = new char[result.m_capacity];
	strncpy_s(result.m_pString, result.m_capacity, string1, strlen(string1));
	strncpy_s(result.m_pString + strlen(string1), result.m_capacity - strlen(string1), myString2.m_pString, myString2.m_length);
	result.m_pString[result.m_length] = CMyString::endString;
	return result;
}

CMyString operator+(CMyString const& myString1, std::string const& string2)
{
	CMyString result;
	result.m_length = myString1.m_length + string2.length();
	result.m_capacity = result.m_length + 1;
	result.m_pString = new char[result.m_capacity];
	strncpy_s(result.m_pString, result.m_capacity, myString1.m_pString, myString1.m_length);
	strncpy_s(result.m_pString + myString1.m_length, result.m_capacity - myString1.m_length, string2.c_str(), string2.length());
	result.m_pString[result.m_length] = CMyString::endString;
	return result;
}

CMyString operator+(CMyString const& myString1, char const* string2)
{
	CMyString result;
	result.m_length = myString1.m_length + strlen(string2);
	result.m_capacity = result.m_length + 1;
	result.m_pString = new char[result.m_capacity];
	strncpy_s(result.m_pString, result.m_capacity, myString1.m_pString, myString1.m_length);
	strncpy_s(result.m_pString + myString1.m_length, result.m_capacity - myString1.m_length, string2, strlen(string2));
	result.m_pString[result.m_length] = CMyString::endString;
	return result;
}

bool operator==(CMyString const& myString1, CMyString const& myString2)
{
	if (myString1.GetLength() != myString2.GetLength())
	{
		return false;
	}
	return strncmp(myString1.GetStringData(), myString2.GetStringData(), myString1.GetLength()) == 0;
}

bool operator!=(CMyString const& myString1, CMyString const& myString2)
{
	return !(myString1 == myString2);
}

bool operator>(CMyString const& myString1, CMyString const& myString2)
{
	size_t minLength = std::min(myString1.GetLength(), myString2.GetLength());
	int result = strncmp(myString1.GetStringData(), myString2.GetStringData(), minLength);
	return result > 0 || (result == 0 && myString1.GetLength() > myString2.GetLength());
}

bool operator>=(CMyString const& myString1, CMyString const& myString2)
{
	return myString1 > myString2 || myString1 == myString2;
}

bool operator<(CMyString const& myString1, CMyString const& myString2)
{
	size_t minLength = std::min(myString1.GetLength(), myString2.GetLength());
	int result = strncmp(myString1.GetStringData(), myString2.GetStringData(), minLength);
	return result < 0 || (result == 0 && myString1.GetLength() < myString2.GetLength());
}

bool operator<=(CMyString const& myString1, CMyString const& myString2)
{
	return myString1 < myString2 || myString1 == myString2;
}

std::ostream& operator<<(std::ostream& stream, CMyString const& myString)
{
	stream << myString.GetStringData();
	return stream;
}

std::istream& operator>>(std::istream& stream, CMyString& myString)
{
	size_t newSrtingCapacity = 1;
	size_t length = 0;
	char* newString = new char[newSrtingCapacity];
	char ch;
	while (stream.get(ch) && ch != '\n')
	{
		if (length + 1 >= newSrtingCapacity)
		{
			newSrtingCapacity *= 2;
			char* temp = new char[newSrtingCapacity];
			strncpy_s(temp, newSrtingCapacity, newString, length);
			delete[] newString;
			newString = temp;
		}
		newString[length++] = ch;
	}
	newString[length] = CMyString::endString;
	myString = CMyString(newString, length);
	delete[] newString;
	return stream;
}

bool operator==(const CMyString::MyIterator& it1, const CMyString::MyIterator& it2)
{
	return it1.m_ptr == it2.m_ptr;
}

bool operator!=(const CMyString::MyIterator& it1,const CMyString::MyIterator& it2)
{
	return !(it1 == it2);
}

bool operator>(const CMyString::MyIterator& it1, const CMyString::MyIterator& it2)
{
	return it1.m_ptr > it2.m_ptr;
}

bool operator<(const CMyString::MyIterator& it1, const CMyString::MyIterator& it2)
{
	return it1.m_ptr < it2.m_ptr;
}

bool operator<=(const CMyString::MyIterator& it1, const CMyString::MyIterator& it2)
{
	return it1.m_ptr <= it2.m_ptr;
}

bool operator>=(const  CMyString::MyIterator& it1, const  CMyString::MyIterator& it2)
{
	return it1.m_ptr >= it2.m_ptr;
}

bool operator==(const CMyString::MyConstIterator&  it1, const CMyString::MyConstIterator& it2)
{
	return it1.m_ptr == it2.m_ptr;
}

bool operator!=(const CMyString::MyConstIterator& it1, const CMyString::MyConstIterator& it2)
{
	return !(it1 == it2);
}

bool operator>(const CMyString::MyConstIterator& it1, const CMyString::MyConstIterator& it2)
{
	return it1.m_ptr > it2.m_ptr;
}

bool operator<(const CMyString::MyConstIterator& it1, const CMyString::MyConstIterator& it2)
{
	return it1.m_ptr < it2.m_ptr;
}

bool operator<=(const CMyString::MyConstIterator& it1, const CMyString::MyConstIterator& it2)
{
	return it1.m_ptr <= it2.m_ptr;
}

bool operator>=(const CMyString::MyConstIterator& it1, const CMyString::MyConstIterator& it2)
{
	return it1.m_ptr >= it2.m_ptr;
}

CMyString::MyIterator& CMyString::MyIterator::operator++()
{
	++m_ptr;
	return *this;
}

CMyString::MyIterator CMyString::MyIterator::operator++(int)
{
	MyIterator temp(m_ptr);
	++m_ptr;
	return temp;
}

CMyString::MyIterator& CMyString::MyIterator::operator--()
{
	--m_ptr;
	return *this;
}

CMyString::MyIterator CMyString::MyIterator::operator--(int)
{
	MyIterator temp(m_ptr);
	--m_ptr;
	return temp;
}

CMyString::MyIterator CMyString::MyIterator::operator+(difference_type n) const 
{
	return MyIterator(m_ptr + n);
}

CMyString::MyIterator CMyString::MyIterator::operator-(difference_type n) const
{
	return MyIterator(m_ptr - n);
}

CMyString::MyIterator& CMyString::MyIterator::operator+=(difference_type n)
{
	m_ptr += n;
	return *this;
}

CMyString::MyIterator& CMyString::MyIterator::operator-=(difference_type n)
{
	m_ptr -= n;
	return *this;
}

CMyString::MyIterator::difference_type CMyString::MyIterator::operator-(const MyIterator& other)
{
	return m_ptr - other.m_ptr;
}

CMyString::MyConstIterator& CMyString::MyConstIterator::operator++()
{
	++m_ptr;
	return *this;
}

CMyString::MyConstIterator CMyString::MyConstIterator::operator++(int)
{
	MyConstIterator temp(m_ptr);
	++m_ptr;
	return *this;
}

CMyString::MyConstIterator& CMyString::MyConstIterator::operator--()
{
	--m_ptr;
	return *this;
}

CMyString::MyConstIterator CMyString::MyConstIterator::operator--(int)
{
	MyConstIterator temp(m_ptr);
	--m_ptr;
	return *this;
}

CMyString::MyConstIterator CMyString::MyConstIterator::operator+(difference_type n) const
{
	return MyConstIterator(m_ptr + n);
}

CMyString::MyConstIterator CMyString::MyConstIterator::operator-(difference_type n) const
{
	return MyConstIterator(m_ptr - n);
}

CMyString::MyConstIterator& CMyString::MyConstIterator::operator+=(difference_type n)
{
	m_ptr += n;
	return *this;
}

CMyString::MyConstIterator& CMyString::MyConstIterator::operator-=(difference_type n)
{
	m_ptr -= n;
	return *this;
}

CMyString::MyConstIterator::difference_type CMyString::MyConstIterator::operator-(const MyConstIterator& other) const
{
	return m_ptr - other.m_ptr;
}
