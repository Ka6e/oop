#pragma once
#include "../include/Bank.h"
#include "../include/Actor.h"
#include <memory>

class Simulation
{
public:
	Simulation(Money cash);
	void Run(int steps);
private:
	Bank bank;
	Money initCash;
	std::vector<std::shared_ptr<Actor>> m_actors;
};
