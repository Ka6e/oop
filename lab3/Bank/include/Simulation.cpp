#include "../include/Simulation.h"
#include "../include/Actors.h"
#include <memory>
#include <iostream>

struct Actors {
	std::shared_ptr<Bart> bart;
	std::shared_ptr<Lisa> lisa;
	std::shared_ptr<Homer> homer;
	std::shared_ptr<Marge> marge;
	std::shared_ptr<Apu> apu;
	std::shared_ptr<Burns> burns;
};
//массивчик сделать
Actors CreateActors(Bank& bank) {
	Actors a;
	a.bart = std::make_shared<Bart>("Bart", 20, nullptr);
	a.lisa = std::make_shared<Lisa>("Lisa", 10, nullptr);
	a.homer = std::make_shared<Homer>("Homer", 3000, bank, nullptr, nullptr, nullptr, nullptr);
	a.marge = std::make_shared<Marge>("Marge", 1970, bank, nullptr);
	a.apu = std::make_shared<Apu>("Apu", 1000, bank, nullptr);
	a.burns = std::make_shared<Burns>("Burns", 5000, bank, nullptr);
	return a;
}

void FillVector(
	std::vector<std::shared_ptr<Actor>>& vec,
	std::shared_ptr<Homer> homer,
	std::shared_ptr<Marge> marge,
	std::shared_ptr<Bart> bart,
	std::shared_ptr<Lisa> lisa,
	std::shared_ptr<Apu> apu,
	std::shared_ptr<Burns> burns
)
{
	vec.push_back(homer);
	vec.push_back(marge);
	vec.push_back(bart);
	vec.push_back(lisa);
	vec.push_back(apu);
	vec.push_back(burns);
}

void SetActors(const std::shared_ptr<Homer>& homer,
	const std::shared_ptr<Marge>& marge,
	const std::shared_ptr<Bart>& bart,
	const std::shared_ptr<Lisa>& lisa,
	const std::shared_ptr<Apu>& apu,
	const std::shared_ptr<Burns>& burns)
{
	bart->SetActor(apu.get());
	lisa->SetActor(apu.get());
	homer->SetActor(marge.get(), burns.get(), bart.get(), lisa.get());
	marge->SetActor(apu.get());
	apu->SetActor(burns.get());
	burns->SetActor(homer.get());
}

void InitialDeposits(const Actors& a) {
	a.homer->Deposit(1000);
	a.marge->Deposit(500);
	a.apu->Deposit(400);
	a.burns->Deposit(3000);
}

void CalculateMoney(const std::vector<std::shared_ptr<Actor>>& actors, Bank& bank, Money initCash)
{
	Money totalCashHold = 0;
	Money totalAccountMoney = 0;

	for (const auto& actor : actors)
	{
		std::cout << actor->GetName() << " cash: " << actor->GetMoney();
		if (auto* bankActor = dynamic_cast<BankActor*>(actor.get()))
		{
			Money balance = bankActor->GetBalance();
			std::cout << ", account: " << balance;
			totalAccountMoney += balance;
		}
		std::cout << std::endl;
		totalCashHold += actor->GetMoney();
	}

	std::cout << "Bank Cash: " << bank.GetCash() << std::endl;
	std::cout << "Total cash money: " << totalCashHold << std::endl;
	std::cout << "Total account money: " << totalAccountMoney << std::endl;

	Money totalMoney = totalCashHold + totalAccountMoney;
	std::cout << "Total physical cash: " << (totalCashHold) << std::endl;

	if (totalMoney == initCash)
	{
		std::cout << "Total money consistency OK\n";
	}
	else
	{
		std::cout << "Total money inconsistency! Total: " << totalMoney << ", Initial: " << initCash << std::endl;
	}
}

Simulation::Simulation(Money cash) : bank(cash), initCash(cash)
{
	Actors actors = CreateActors(bank);
	SetActors(actors.homer, actors.marge, actors.bart, actors.lisa, actors.apu, actors.burns);
	InitialDeposits(actors);
	FillVector(m_actors, actors.homer, actors.marge, actors.bart, actors.lisa, actors.apu, actors.burns);
	std::cout << "Initial state:" << std::endl;
	CalculateMoney(m_actors, bank, initCash);
}

void Simulation::Run(int steps)
{
	for (int i = 0; i < steps; ++i) 
	{
		std::cout << "\nStep " << i + 1 << std::endl;;
		for (auto& actor : m_actors) 
		{
			actor->Act();
		}
	}
	std::cout << std::endl;

	CalculateMoney(m_actors, bank, initCash);
}

