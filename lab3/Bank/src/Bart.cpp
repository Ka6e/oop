#include "../include/Bart.h"
#include <iostream>
#include "format"

Bart::Bart(std::string name, Money cash, BankActor* apu)
	: Actor(name, cash),
	m_apu(apu)
{
}

void Bart::Act()
{
	Money candies = 20;
	if (GetMoney() >= candies)
	{
		if (m_apu && SpendMoney(candies))
		{
			m_apu->ReceiveMoney(candies);
			std::cout << std::format("{} spent {} cash at Apu's store", GetName(), candies) << std::endl;
		}
		else
		{
			ReceiveMoney(candies);
			std::cout << std::format("{} couldn't spent {} cash at Apu's store", GetName(), candies);
		}
	}
	else
	{
		std::cout << GetName() << " doesn't have enough cash to spent" << std::endl;
	}
}

void Bart::SetActor(Actor* actor)
{
	m_apu = dynamic_cast<BankActor*>(actor);
}

void Bart::SetActor(Actor* firstActor, Actor* secondActor, Actor* thirdActor, Actor* fourthActor)
{
}
