#pragma once
#include "../include/BankActor.h"

class Apu : public BankActor
{
public:
	Apu(std::string name, Money cash, Bank& bank, BankActor* burns);
	void Act() override;
	void SetActor(Actor* actor) override;
private:
	void SetActor(Actor* firstActor, Actor* secondActor,
		Actor* thirdActor, Actor* fourthActor) override;
	BankActor* m_burns;
};
