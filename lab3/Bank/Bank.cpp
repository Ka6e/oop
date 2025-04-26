#include "include/Bank.h"
#include "include/BankOperationError.h"

Bank::Bank(Money cash) :
	m_nextAccountId(0),
	m_cash(cash)
{
	if (cash < 0)
	{
		throw BankOperationError("Cash is negative");
	}
}

void Bank::SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount)
{
	if (!TrySendMoney(srcAccountId, dstAccountId, amount))
	{
		throw BankOperationError("Not enough money");
	}
}

bool Bank::TrySendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount)
{
	if (amount < 0)
	{
		throw std::out_of_range("Cannot send negative amoount");
	}
	auto srcAccount = m_accounts.find(srcAccountId);
	if (srcAccount == m_accounts.end())
	{
		throw BankOperationError("Source account not found");
	}
	auto dstAccount = m_accounts.find(dstAccountId);
	if (dstAccount == m_accounts.end())
	{
		throw BankOperationError("Destination account not found");
	}
	if (srcAccount->second < amount)
	{
		return false;
	}
	srcAccount->second -= amount;
	dstAccount->second += amount;
	return true;
}

Money Bank::GetCash() const
{
	return m_cash;
}

Money Bank::GetAccountBalance(AccountId accountId) const
{
	auto account = m_accounts.find(accountId);
	if (account == m_accounts.end())
	{
		throw BankOperationError("Account doesn't exist");
	}
	return account->second;
}

void Bank::WithdrawMoney(AccountId account, Money amount)
{
	if (!TryWithdrawMoney(account, amount))
	{
		throw BankOperationError("Not enough money");
	}
}

bool Bank::TryWithdrawMoney(AccountId account, Money amount)
{
	if (amount < 0)
	{
		throw std::out_of_range("Cannot withdraw negative amount");
	}
	auto acc = m_accounts.find(account);
	if (acc == m_accounts.end())
	{
		throw BankOperationError("Account doesn't exist");
	}
	if (acc->second < amount)
	{
		return false;
	}
	m_cash += amount;
	acc->second -= amount;
	return true;
}

void Bank::DepositMoney(AccountId account, Money amount)
{
	auto acc = m_accounts.find(account);
	if (acc == m_accounts.end())
	{
		throw BankOperationError("Account doesn't exist");
	}
	if (amount < 0)
	{
		throw std::out_of_range("Cannot deposit negative amount");
	}
	if (m_cash < amount)
	{
		throw BankOperationError("Not enough cash");
	}
	m_cash -= amount;
	acc->second += amount;
}

AccountId Bank::OpenAccount()
{
	AccountId account = m_nextAccountId++;
	m_accounts[account] = 0;
	return account;
}

Money Bank::CloseAccount(AccountId accountId)
{
	auto account = m_accounts.find(accountId);
	if (account == m_accounts.end())
	{
		throw BankOperationError("Account doesn't exist");
	}
	Money balance = account->second;
	m_cash += balance;
	m_accounts.erase(account);
	return balance;
}

