#pragma once
#include "../include/BankActor.h"

class Bart : public Actor
{
public:
	Bart(std::string name, Money cash, BankActor* m_apu);
	void Act() override;
	void SetActor(Actor* actor) override;
private:
	void SetActor(Actor* firstActor, Actor* secondActor,
		Actor* thirdActor, Actor* fourthActor) override;
	BankActor* m_apu;
};
