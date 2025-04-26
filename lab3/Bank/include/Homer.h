#pragma once
#include "../include/BankActor.h"

class Homer : public BankActor
{
public:
	Homer(std::string name, Money cash, Bank& bank, BankActor* marge,
		BankActor* burns, Actor* art, Actor* lisa);
	void Act() override;
	void SetActor(Actor* firstActor, Actor* secondActor,
		Actor* thirdActor, Actor* fourthActor) override;
private:
	void SetActor(Actor* actor) override;
	BankActor* m_marge;
	BankActor* m_burns;
	Actor* m_bart;
	Actor* m_lisa;
};

