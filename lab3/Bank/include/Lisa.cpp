#include "Lisa.h"
#include <iostream>
#include <format>

Lisa::Lisa(std::string name, Money cash, BankActor* apu)
	: Actor(name, cash),
	m_apu(apu)
{
}

void Lisa::Act()
{
	Money drink = 30;
	if (GetMoney() >= drink)
	{
		if (m_apu && SpendMoney(drink))
		{
			m_apu->ReceiveMoney(drink);
			std::cout << std::format("{} spent {} cash at Apu's store", GetName(), drink) << std::endl;
		}
		else
		{
			ReceiveMoney(drink);
			std::cout <<  std::format("{} couldn't spent {} cash at Apu's store", GetName(), drink);
		}
	}
	else
	{
		std::cout << GetName() << " doesn't have enough cash to spent" << std::endl;
	}
}

void Lisa::SetActor(Actor* actor)
{
	m_apu = dynamic_cast<BankActor*>(actor);
}

void Lisa::SetActor(Actor* firstActor, Actor* secondActor, Actor* thirdActor, Actor* fourthActor)
{
}



