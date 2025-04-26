#pragma once
#include "../include/BankActor.h"

class Burns : public BankActor
{
public:
	Burns(std::string name, Money cash, Bank& bank, BankActor* homer);
	void Act() override;
	void SetActor(Actor* actor) override;
private:
	void SetActor(Actor* firstActor, Actor* secondActor,
		Actor* thirdActor, Actor* fourthActor) override;
	BankActor* m_homer;
};
