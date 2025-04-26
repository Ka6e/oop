#include "../include/Burns.h"
#include <format>
#include <iostream>

Burns::Burns(std::string name, Money cash, Bank& bank, BankActor* homer)
	: BankActor(name, cash, bank),
	m_homer(homer)
{
}

void Burns::Act()
{
	Money salary = 700;
	if (m_homer && SendMoney(m_homer->GetAccountId(), salary))
	{
		std::cout << std::format("{} send {}'s salary in the amount of {} ",
			GetName(), m_homer->GetName(), salary) << std::endl;
	}
	else
	{
		std::cout << "Couldn't sent salary" << std::endl;
	}
}

void Burns::SetActor(Actor* actor)
{
	m_homer = dynamic_cast<BankActor*>(actor);
}

void Burns::SetActor(Actor* firstActor, Actor* secondActor, Actor* thirdActor, Actor* fourthActor)
{
}
