#pragma once
#include "../include/BankActor.h"

class Lisa : public Actor
{
public:
	Lisa(std::string name, Money cash, BankActor* apu);
	void Act() override;
	void SetActor(Actor* actor) override;
private: 
	void SetActor(Actor* firstActor, Actor* secondActor,
		Actor* thirdActor, Actor* fourthActor) override;
	BankActor* m_apu;
};
