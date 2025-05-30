#include "../include/CStringList.h"
#include <string>
#include <cassert>
#include <stdexcept>

CStringList::Node::Node(std::string value)
	: m_data(std::move(value)),
	nextptr(nullptr),
	prevptr()
{
}


CStringList::CStringList()
	: m_head(nullptr),
	m_tail(nullptr),
	m_sentinel(std::make_shared<Node>("")),
	m_size(0)
{
	m_sentinel->prevptr.reset();
	m_sentinel->nextptr.reset();
}

CStringList::CStringList(const std::string& value)
	: m_head(std::make_shared<Node>(value)),
	m_tail(m_head),
	m_sentinel(std::make_shared<Node>("")),
	m_size(1)
{
	m_tail->nextptr = m_sentinel;
	m_sentinel->prevptr = m_tail;
}


CStringList::CStringList(const CStringList& other)
	: CStringList()
{
	m_sentinel->prevptr.reset();
	m_sentinel->nextptr.reset();
	std::shared_ptr<Node> current = other.m_head;
	while (current && current != other.m_sentinel)
	{
		PushBack(current->m_data);
		current = current->nextptr;
	}
}

CStringList::CStringList(CStringList&& other) noexcept
	: m_head(std::move(other.m_head)),
	m_tail(std::move(other.m_tail)),
	m_sentinel(std::move(other.m_sentinel)),
	m_size(other.m_size)
{
	other.m_head.reset();
	other.m_tail.reset();
	other.m_sentinel = std::make_shared<Node>("");
	other.m_sentinel->prevptr.reset();
	other.m_sentinel->nextptr.reset();
	other.m_size = 0;
}

CStringList& CStringList::operator=(const CStringList& other)
{
	if (this != &other)
	{
		CStringList temp(other);
		std::swap(*this, temp);
	}
	return *this;
}

CStringList& CStringList::operator=(CStringList&& other) noexcept
{  
    if (this != &other) 
	{
		Clear();
		m_head = std::move(other.m_head);
		m_tail = std::move(other.m_tail);
		m_sentinel = std::move(other.m_sentinel);
		m_size = other.m_size;

		other.m_head.reset();
		other.m_tail.reset();
		other.m_sentinel = std::make_shared<Node>("");
		other.m_sentinel->prevptr.reset();
		other.m_sentinel->nextptr.reset();
		other.m_size = 0;
    }  
    return *this;  
}

void CStringList::PushBack(const std::string& str)
{
	auto newNode = std::make_shared<Node>(str);
	if (m_tail)
	{
		newNode->prevptr = m_tail;
		m_tail->nextptr = newNode;
		m_tail = newNode;
		m_tail->nextptr = m_sentinel;
		m_sentinel->prevptr = m_tail;
	}
	else
	{
		m_head = m_tail = newNode;
		m_tail->nextptr = m_sentinel;
		m_sentinel->prevptr = m_tail;
	}
	m_size++;
}

void CStringList::PushFront(const std::string& str)
{
	auto newNode = std::make_shared<Node>(str);
	if (m_head)
	{
		newNode->nextptr = m_head;
		m_head->prevptr = newNode;
		m_head = newNode;
	}
	else
	{
		m_head = m_tail = newNode;
		m_tail->nextptr = m_sentinel;
		m_sentinel->prevptr = m_tail;
	}
	++m_size;
}

void CStringList::PopBack()
{
	if (m_size <= 0)
	{
		throw std::runtime_error("Size is zero");
	}
	if (m_tail == m_head)
	{
		m_head.reset();
		m_tail.reset();
		m_sentinel->prevptr.reset();
	}
	else
	{
		auto oldTail = m_tail;
		m_tail = m_tail->prevptr.lock();
		if (m_tail)
		{
			m_tail->nextptr = m_sentinel;
			m_sentinel->prevptr = m_tail;
		}
		oldTail->prevptr.reset();
	}
	--m_size;
}

void CStringList::PopFront()
{
	if (m_size <= 0)
	{
		throw std::runtime_error("Size is zero");
	}
	if (m_head == m_tail)
	{
		m_head.reset();
		m_tail.reset();
		m_sentinel->prevptr.reset();
	}
	else
	{
		m_head = m_head->nextptr;
		m_head->prevptr.reset();
	}
	--m_size;
}


size_t CStringList::Size() const
{
	return m_size;
}

bool CStringList::IsEmpty() const
{
	return m_size == 0;
}

void CStringList::Clear()
{
	m_head.reset();
	m_tail.reset();
	m_sentinel->prevptr.reset();
	m_sentinel->nextptr.reset();
	m_size = 0;
}

CStringList::~CStringList()
{
	Clear();
}

void CStringList::Insert(Iterator<false> pos, const std::string& str)
{
	auto newNode = std::make_shared<Node>(str);

	if (IsEmpty())
	{
		m_head = m_tail = newNode;
		m_tail->nextptr = m_sentinel;
		m_sentinel->prevptr = m_tail;
		m_size++;
		return;
	}

	if (pos == begin())
	{
		PushFront(str);
		return;
	}

	auto curr = pos.GetNode();
	if (curr == m_sentinel)
	{
		PushBack(str);
		return;
	}

	newNode->nextptr = curr;
	newNode->prevptr = curr->prevptr;
	if (curr->prevptr.lock())
	{
		curr->prevptr.lock()->nextptr = newNode;
	}
	curr->prevptr = newNode;
	if (curr == m_tail)
	{
		m_tail = newNode;
		m_tail->nextptr = m_sentinel;
		m_sentinel->prevptr = m_tail;
	}
	m_size++;
}

void CStringList::Erase(Iterator<false> pos)
{
	assert(!IsEmpty());
	auto curr = pos.GetNode();
	assert(curr != m_sentinel);
	if (m_size == 1)
	{
		m_head.reset();
		m_tail.reset();
		m_sentinel->prevptr.reset();
		m_size = 0;
		return;
	}
	if (curr == m_head)
	{
		PopFront();
		return;
	}
	if (curr == m_tail)
	{
		PopBack();
		return;
	}

	auto prev = curr->prevptr.lock();
	auto next = curr->nextptr;
	if (prev)
	{
		prev->nextptr = next;
	}
	if (next)
	{
		next->prevptr = prev;
	}
	m_size--;
}

CStringList::Iterator<false> CStringList::begin()
{
	return Iterator<false>(m_head);
}

CStringList::Iterator<false> CStringList::end()
{
	return Iterator<false>(m_sentinel);
}

CStringList::ReverseIterator CStringList::rbegin()
{
	return ReverseIterator(end());
}

CStringList::ReverseIterator CStringList::rend()
{
	return ReverseIterator(begin());
}

CStringList::ConstIterator CStringList::cbegin() const
{
	return ConstIterator(m_head);
}

CStringList::ConstIterator CStringList::cend() const
{
	return ConstIterator(m_sentinel);
}

CStringList::ConstReverseIterator CStringList::crbegin() const
{
	return ConstReverseIterator(cend());
}

CStringList::ConstReverseIterator CStringList::crend() const
{
	return ConstReverseIterator(cbegin());
}



