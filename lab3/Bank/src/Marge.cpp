#include "../include/Marge.h"
#include <iostream>


Marge::Marge(std::string name, Money cash, Bank& bank, BankActor* apu):
	BankActor(name, cash, bank),
	m_apu(apu)
{
}

void Marge::Act()
{
	Money cash = 150;
	if (m_apu && SendMoney(m_apu->GetAccountId(), cash))
	{
		std::cout << GetName() << " bought apple for 150 from Apu" << std::endl;
	}
	else
	{
		std::cout << GetName() << "could buy apple" << std::endl;
	}
}

void Marge::SetActor(Actor* actor)
{
	m_apu = dynamic_cast<BankActor*>(actor);
}

void Marge::SetActor(Actor* firstActor, Actor* secondActor, Actor* thirdActor, Actor* fourthActor)
{
}


