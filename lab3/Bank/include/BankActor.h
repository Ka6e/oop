#pragma once
#include "../include/Actor.h"
#include "../include/Bank.h"

class BankActor : public Actor
{
public:
	BankActor(std::string name, Money cash, Bank& bank);
	~BankActor();	
	AccountId GetAccountId() const;
	bool RequestTransfer(AccountId dst, Money money);
	bool Deposit(Money amount);
	bool Withdraw(Money amount);
	bool SendMoney(AccountId dst, Money amount);
	Money GetBalance() const;
private:
	AccountId m_id;
	Bank& m_bank;
};
