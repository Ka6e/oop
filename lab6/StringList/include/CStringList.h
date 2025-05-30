#pragma once
#include <memory>
#include <string>
#include <utility>

//проверка на out of range
class CStringList
{
public:
	struct Node
	{
		std::string m_data;
		std::shared_ptr<Node> nextptr;
		std::weak_ptr<Node> prevptr;
		explicit Node(std::string value);
	};

	CStringList();
	CStringList(const std::string& value);
	CStringList(const CStringList& other);
	CStringList(CStringList&& other) noexcept;

	CStringList& operator=(const CStringList& other);
	CStringList& operator=(CStringList&& other) noexcept;

	void PushBack(const std::string& str);
	void PushFront(const std::string& str);
	void PopBack();
	void PopFront();
	size_t Size() const;
	bool IsEmpty() const;
	void Clear();

	~CStringList();
	template <bool IsConst>
	class Iterator
	{
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = std::conditional_t<IsConst, const std::string, std::string>;
		using reference = std::conditional_t<IsConst, const std::string&, std::string&>;
		using pointer = std::conditional_t<IsConst, const std::string*, std::string*>;
		using difference_type = std::ptrdiff_t;

		explicit Iterator(const std::shared_ptr<Node> node) : m_node(std::move(node)) {}

		std::shared_ptr<Node> GetNode() const
		{
			return m_node;
		}

		reference operator*() const 
		{
			return m_node->m_data;
		}
		pointer operator->() const 
		{
			return &m_node->m_data;
		}
		Iterator& operator++() noexcept
		{
			m_node = m_node->nextptr;
			return *this;
		}
		Iterator operator++(int) noexcept
		{
			Iterator temp(*this);
			++(*this);
			return temp;
		}
		Iterator& operator--() noexcept
		{
			if (m_node)
			{
				m_node = m_node->prevptr.lock();
			}
			return *this;
		}
		Iterator operator--(int) noexcept	
		{
			Iterator temp(*this);
			--(*this);
			return *this;
		}
		bool operator==(const Iterator& other) const
		{
			return m_node == other.m_node;
		}
		bool operator!=(const Iterator& other) const
		{
			return !(m_node == other.m_node);
		}

	private:
		std::shared_ptr<Node> m_node;
	};

	using DefaultIterator = Iterator<false>;
	using ReverseIterator = std::reverse_iterator<Iterator<false>>;
	using ConstIterator = Iterator<true>;
	using ConstReverseIterator = std::reverse_iterator <Iterator<true>>;


	void Insert(Iterator<false> pos, const std::string& str);
	void Erase(Iterator<false> pos);
	Iterator<false> begin();
	Iterator<false> end();
	ConstIterator cbegin() const;
	ConstIterator cend() const;
	ReverseIterator rbegin();
	ReverseIterator rend();
	ConstReverseIterator crbegin() const;
	ConstReverseIterator crend() const;

private:
	std::shared_ptr<Node> m_head, m_tail, m_sentinel;
	size_t m_size;
};

