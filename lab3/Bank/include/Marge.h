#pragma once
#include "../include/BankActor.h"

class Marge : public BankActor
{
public:
	Marge(std::string name, Money cash, Bank& bank, BankActor* apu);
	void Act() override;
	void SetActor(Actor* actor) override;
private:
	void SetActor(Actor* firstActor, Actor* secondActor,
		Actor* thirdActor, Actor* fourthActor) override;
	BankActor* m_apu;
};
