#pragma once
#include "../include/Bank.h"
#include <string>

class Actor
{
public:
	Actor(std::string name, Money cash);
	virtual void Act() = 0;
	virtual void SetActor(Actor* actor) = 0;
	virtual void SetActor(Actor* firstActor, Actor* secondActor,
		Actor* thirdActor, Actor* fourthActor) = 0;
	const std::string GetName() const;
	Money GetMoney() const;
	Money SpendMoney(const Money& money);
	Money ReceiveMoney(const Money& money);
private:
	bool IsValidMoney(const Money money);
	std::string m_name;
	Money m_money;
};
