#include "../include/Apu.h"
#include <iostream>
#include "format"

Apu::Apu(std::string name, Money cash, Bank& bank, BankActor* burns):
	BankActor(name, cash, bank),
	m_burns(burns)
{
}

void Apu::Act()
{
	Money payment = 100;
	if (m_burns)
	{
		SendMoney(m_burns->GetAccountId(), payment);
		std::cout << std::format("{} paid {} for electicity", GetName(), payment) << std::endl;
	}
	if (GetMoney() > 0)
	{
		Deposit(GetMoney());
	}
}

void Apu::SetActor(Actor* actor)
{
	m_burns = dynamic_cast<BankActor*>(actor);
}

void Apu::SetActor(Actor* firstActor, Actor* secondActor, Actor* thirdActor, Actor* fourthActor)
{
}
//класс операций где указатели и сколько денег