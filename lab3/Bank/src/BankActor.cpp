#include "../include/BankActor.h"
#include "../include//BankOperationError.h"


BankActor::BankActor(std::string name, Money cash, Bank& bank) 
	: Actor(name, cash),
	m_bank(bank),
	m_id(bank.OpenAccount())
{
}

AccountId BankActor::GetAccountId() const
{
	return m_id;
}

bool BankActor::RequestTransfer(AccountId dst, Money money)
{
	return SendMoney(dst, money);
}

BankActor::~BankActor()
{
	if (m_id != 0)
	{
		m_bank.CloseAccount(m_id);
	}
}

bool BankActor::Deposit(Money amount)
{
	if (amount <= 0 || amount > GetMoney())
	{
		return false;
	}
	try
	{
		m_bank.DepositMoney(m_id, amount);
		SpendMoney(amount);
	}
	catch (const BankOperationError&)
	{
		ReceiveMoney(amount);
		return false;
	}
}

bool BankActor::Withdraw(Money amount)
{
	if (amount <= 0 || !m_bank.TryWithdrawMoney(m_id, amount))
	{
		return false;
	}
	ReceiveMoney(amount);
	return true;
}

bool BankActor::SendMoney(AccountId dst, Money amount)
{
	if (amount <= 0)
	{
		return false;
	}
	return m_bank.TrySendMoney(m_id, dst, amount);
}

Money BankActor::GetBalance() const
{
	try
	{
		return m_bank.GetAccountBalance(m_id);
	}
	catch (const BankOperationError&)
	{
		return 0;
	}
}
