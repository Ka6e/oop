#pragma once
#include <algorithm>
#include <stdexcept>

template<typename T>
class CMyArray
{
public:
	CMyArray()
		: m_data(nullptr),
		m_size(0),
		m_capacity(0) {
	};

	CMyArray(size_t capacity)
		: m_data(capacity > 0 ? new T[capacity]{} : nullptr),
		m_size(0),
		m_capacity(capacity)
	{
	}

	CMyArray(const CMyArray& other)
		: m_data(new T[other.m_capacity]),
		m_size(other.m_size),
		m_capacity(other.m_capacity)
	{
		std::copy(other.m_data, other.m_data + m_size, m_data);
	};

	CMyArray(CMyArray&& other) noexcept
		: m_data(other.m_data),
		m_size(other.m_size),
		m_capacity(other.m_capacity)
	{
		other.m_data = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;
	};
	~CMyArray()
	{
		delete[] m_data;
	}

	void Resize(unsigned int newCapacity)
	{
		if (m_capacity != newCapacity)
		{
			//тест для выделения capacity 0
			T* newArray = new T[newCapacity];
			unsigned int newSize = (newCapacity < m_size) ? newCapacity : m_size;
			for (size_t i = 0; i < newSize; i++)
			{
				newArray[i] = std::move(m_data[i]);
			}
			delete[] m_data;
			m_data = newArray;
			m_size = newSize;
			m_capacity = newCapacity;
		}

	}

	void PushBack(const T& value)
	{
		if (m_size == m_capacity)
		{
			Resize(m_capacity == 0 ? 1 : m_capacity * 2);
		}
		m_data[m_size++] = value;
	}

	void Clear()
	{
		for (size_t i = 0; i < m_size; i++)
		{
			m_data[i] = T();
		}
		m_size = 0;
	}

	size_t GetCapacity()
	{
		return m_capacity;
	}

	unsigned int Size()
	{
		return m_size;
	}

	const T& operator[](unsigned int index) const
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Index out of range");
		}
		return m_data[index];
	}
	T& operator[](unsigned int index)
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Index out of range");
		}
		return m_data[index];
	}

	CMyArray& operator=(const CMyArray& other)
	{
		if (this != &other)
		{
			CMyArray temp(other);
			std::swap(m_data, temp.m_data);
			std::swap(m_size, temp.m_size);
			std::swap(m_capacity, temp.m_capacity);
		}
		return *this;
	}

	CMyArray& operator=(CMyArray&& other) noexcept
	{
		if (this != &other)
		{
			delete[] m_data;
			m_size = 0;
			m_capacity = 0;

			std::swap(m_data, other.m_data);
			std::swap(m_size, other.m_size);
			std::swap(m_capacity, other.m_capacity);

			other.m_data = nullptr;
			other.m_size = 0;
			other.m_capacity = 0;
		}
		return *this;
	}
	//без классов
	template<typename T, bool IsConst>
	class Iterator
	{
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = std::conditional_t<IsConst, const T, T>;
		using pointer = std::conditional_t<IsConst, const T*, T*>;
		using reference = std::conditional_t<IsConst, const T&, T&>;
		using difference_type = std::ptrdiff_t;

		Iterator() : it_data(nullptr), it_begin(nullptr), it_end(nullptr) {}
		Iterator(pointer ptr, pointer begin, pointer end)
			: it_data(ptr),
			it_begin(begin),
			it_end(end)
		{
		}

		reference operator*() const
		{
			if (it_data < it_begin || it_data >= it_end)
			{
				throw std::out_of_range("Iterator dereference out of bounds");
			}
			return *it_data;
		}
		pointer operator->() const
		{
			if (it_data < it_begin || it_data >= it_end)
			{
				throw std::out_of_range("Iterator dereference out of bounds");
			}
			return it_data;
		}

		Iterator& operator++()
		{
			++it_data;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator temp(this);
			++(*this);
			return temp;
		}
		Iterator operator--()
		{
			--it_data;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator temp(this);
			--(*this);
			return temp;
		}
		Iterator& operator+=(difference_type offset)
		{
			it_data += offset;
			return *this;
		}
		Iterator& operator-=(difference_type offset)
		{
			it_data -= offset;
			return *this;
		}

		reference operator[](difference_type offset)
		{
			pointer target = it_data + offset;
			if (target < it_begin || target >= it_end)
			{
				throw std::out_of_range("Iterator index out of bounds");
			}
			return *(target);
		}
		//<=>
		bool operator==(const Iterator& other) const { return it_data == other.it_data; }
		bool operator!=(const Iterator& other) const { return !(*this == other); }
		bool operator<(const Iterator& other) const { return it_data < other.it_data; }
		bool operator>(const Iterator& other) const { return it_data > other.it_data; }
		bool operator<=(const Iterator& other) const { return it_data <= other.it_data; }
		bool operator>=(const Iterator& other) const { return it_data >= other.it_data; }

	private:
		pointer it_data, it_begin, it_end;
	};
	using DefaultIterator = Iterator<T, false>;
	using ConstIterator = Iterator<T, true>;
	using ReverseIterator = std::reverse_iterator<Iterator<T, false>>;
	using ConstReverseIterator = std::reverse_iterator<Iterator<T, true>>;

	//T* begin()
	//{
	//	return m_data;
	//}
	DefaultIterator begin()
	{
		return DefaultIterator(m_data, m_data, m_data + m_size);
	}
	DefaultIterator end()
	{
		return DefaultIterator(m_data + m_size, m_data, m_data + m_size);
	}
	ReverseIterator rbegin()
	{
		return ReverseIterator(end());
	}
	ReverseIterator rend()
	{
		return ReverseIterator(begin());
	}
	ConstIterator cbegin()
	{
		return ConstIterator(m_data, m_data, m_data + m_size);
	}
	ConstIterator cend()
	{
		return ConstIterator(m_data + m_size, m_data, m_data + m_size);
	}
	ConstReverseIterator crbegin()
	{
		return ConstReverseIterator(cend());
	}
	ConstReverseIterator crend()
	{
		return ConstReverseIterator(cbegin());
	}

private:
	T* m_data;
	size_t m_size;
	size_t m_capacity;
};
