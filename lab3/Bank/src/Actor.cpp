#include "../include/Actor.h"
#include <stdexcept>

Actor::Actor(std::string name, Money cash = 0):  m_name(name), m_money(cash)
{
}

const std::string Actor::GetName() const
{
	return m_name;
}

Money Actor::GetMoney() const
{
	return m_money;
}

Money Actor::SpendMoney(const Money& money)
{
	IsValidMoney(money);
	return m_money -= money;
}

Money Actor::ReceiveMoney(const Money& money)
{
	IsValidMoney(money);
	return m_money += money;
}

bool Actor::IsValidMoney(const Money money)
{
	if (money < 0)
	{
		throw std::invalid_argument("Money cannot be negatibe");
	}
	return true;
}

