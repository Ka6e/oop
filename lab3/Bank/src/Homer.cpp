#include "../include/Homer.h"
#include <iostream>
#include <format>

Homer::Homer(std::string name, Money cash, Bank& bank, BankActor* marge, 
	BankActor* burns, Actor* bart, Actor* lisa)
	: BankActor(name, cash, bank),
	m_marge(marge),
	m_burns(burns),
	m_bart(bart),
	m_lisa(lisa)
{
}
//класс рпкраций
void Homer::Act()
{
	Money toMarge = 200;
	Money toElecity = 200;
	Money toBart = 75;
	Money toLisa = 75;

	if (m_marge && SendMoney(m_marge->GetAccountId(), toMarge))
	{
		std::cout << std::format("{} paid {} to {}", GetName(), toMarge, m_marge->GetName()) << std::endl;
	}
	else
	{
		std::cout << std::format("{} couldn't pay to {}", GetName(), m_marge->GetName()) << std::endl;
	}

	if (m_burns && SendMoney(m_burns->GetAccountId(), toElecity)) {
		std::cout << GetName() << " paid 200 for electricity\n";
	}
	else {
		std::cout << GetName() << " could not pay electricity\n";
	}

	if (Withdraw(150))
	{
		if (m_bart->ReceiveMoney(toBart) && m_lisa->ReceiveMoney(toLisa)) 
		{
			SpendMoney(150);
			std::cout << std::format("{} gave {} to {} and {} to {}", GetName(),
				toBart, m_bart->GetName(), toLisa, m_lisa->GetName()) << std::endl;
		}
		else {
			std::cout << GetName() << " could not give money to kids" << std::endl;
		}
	}
	else {
		std::cout << GetName() << " could not withdraw money for kids" << std::endl;
	}
}

void Homer::SetActor(Actor* firstActor, Actor* secondActor, Actor* thirdActor, Actor* fourthActor)
{
	m_marge = dynamic_cast<BankActor*>(firstActor);
	m_burns = dynamic_cast<BankActor*>(secondActor);
	m_bart = dynamic_cast<Actor*>(thirdActor);
	m_lisa = dynamic_cast<Actor*>(fourthActor);
}

void Homer::SetActor(Actor* actor)
{
}
