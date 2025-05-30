#pragma once
#include <string>

class CMyString
{
public:
	CMyString();
	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	CMyString(CMyString const& other);
	CMyString(CMyString&& other) noexcept;
	CMyString(std::string const& stlString);
	~CMyString();

	size_t GetLength()const;
	const char* GetStringData()const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();
	size_t GetCapacity();

	CMyString& operator=(const CMyString& other);
	CMyString& operator=(CMyString&& other) noexcept;
	CMyString& operator+=(const CMyString& other);
	const char& operator[](size_t index) const;
	char& operator[](size_t index);

	friend CMyString operator+(CMyString const& myString1, CMyString const& myString2);
	friend CMyString operator+(std::string const& string1, CMyString const& myString2);
	friend CMyString operator+(char const* string1, CMyString const& myString2);
	friend CMyString operator+(CMyString const& myString1, std::string const& string2);
	friend CMyString operator+(CMyString const& myString1, char const* string2);
	friend bool operator==(CMyString const& myString1, CMyString const& myString2);
	friend bool operator!=(CMyString const& myString1, CMyString const& myString2);
	friend bool operator>(CMyString const& myString1, CMyString const& myString2);
	friend bool operator>=(CMyString const& myString1, CMyString const& myString2);
	friend bool operator<(CMyString const& myString1, CMyString const& myString2);
	friend bool operator<=(CMyString const& myString1, CMyString const& myString2);
	friend std::ostream& operator<<(std::ostream& stream, CMyString const& myString);
	friend std::istream& operator>>(std::istream& stream, CMyString& myString);


	class MyIterator
	{
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = char;
		using difference_type = std::ptrdiff_t;
		using pointer = char*;
		using reference = char&;
		MyIterator(char* ptr) : m_ptr(ptr) {}

		reference operator*() const { return *m_ptr; }
		pointer operator->() const { return m_ptr; }

		MyIterator& operator++();
		MyIterator operator++(int);
		MyIterator& operator--();
		MyIterator operator--(int);
		MyIterator operator+(difference_type n) const;
		MyIterator operator-(difference_type n) const;
		MyIterator& operator+=(difference_type n);
		MyIterator& operator-=(difference_type n);

		friend bool operator==(const MyIterator& it1, const MyIterator& it2);
		friend bool operator!=(const MyIterator& it1, const MyIterator& it2);
		friend bool operator>(const MyIterator& it1, const MyIterator& it2);
		friend bool operator<(const MyIterator& it1, const MyIterator& it2);
		friend bool operator <=(const MyIterator& it1, const MyIterator& it2);
		friend bool operator >=(const MyIterator& it1, const MyIterator& it2);
		difference_type operator-(const MyIterator& other);
	private:
		char* m_ptr;
	};

	class MyConstIterator
	{
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = char;
		using difference_type = std::ptrdiff_t;
		using pointer = const char*;
		using reference = const char&;

		MyConstIterator(const char* ptr) : m_ptr(ptr) {}
		reference operator*() { return *m_ptr; }
		pointer operator->() { return m_ptr; }

		MyConstIterator& operator++();
		MyConstIterator operator++(int);
		MyConstIterator& operator--();
		MyConstIterator operator--(int);
		MyConstIterator operator+(difference_type n) const ;
		MyConstIterator operator-(difference_type n) const ;
		MyConstIterator& operator+=(difference_type n);
		MyConstIterator& operator-=(difference_type n);

		friend bool operator==(const MyConstIterator& it1, const MyConstIterator& it2);
		friend bool operator!=(const MyConstIterator& it1, const MyConstIterator& it2);
		friend bool operator>(const MyConstIterator& it1, const MyConstIterator& it2);
		friend bool operator<(const MyConstIterator& it1, const MyConstIterator& it2);
		friend bool operator <=(const MyConstIterator& it1, const MyConstIterator& it2);
		friend bool operator >=(const MyConstIterator& it1, const MyConstIterator& it2);
		difference_type operator-(const MyConstIterator& other) const;

	private:
		const char* m_ptr;
	};

	using ReverseIterator = std::reverse_iterator<MyIterator>;
	using ConstReverseIterator = std::reverse_iterator<MyConstIterator>;

	MyIterator begin();
	MyIterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();
	MyConstIterator cbegin() const;
	MyConstIterator cend() const ;
	ConstReverseIterator crbegin() const;
	ConstReverseIterator crend() const ;
private:
	char* m_pString; 
	size_t m_length; 
	size_t m_capacity; 
	static const char endString = '\0'; 
	static char emptyString[1];
};