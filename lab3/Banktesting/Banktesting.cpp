#define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "../Bank/include/Bank.h"
#include "../Bank/include/BankOperationError.h"

TEST_CASE("Bank initialization")
{
	GIVEN("Positive cash")
	{
		auto money = 1000;
		WHEN("Initializing the bank")
		{
			Bank bank(money);
			THEN("Bank with 1000 cash")
			{
				CHECK(bank.GetCash() == money);
			}
		}

	}
	GIVEN("Zero cash")
	{
		auto money = 0;
		WHEN("Initialization with zero cash")
		{
			Bank bank(money);
			THEN("Bank with zero cash")
			{
				CHECK(bank.GetCash() == money);
			}
		}
	}
	GIVEN("Negative cash")
	{
		auto money = -1000;
		WHEN("Initialization the bank")
		{
			THEN("It should trhwo BankOperationError")
			{
				CHECK_THROWS_AS(Bank(money), BankOperationError);
			}
		}
	}
}

TEST_CASE("Account operations")
{
	GIVEN("A bank with 1000 cash")
	{
		Bank bank(1000);
		WHEN("Opening account")
		{
			auto account = bank.OpenAccount();
			THEN("Account with zero balance and bank's cahs is 1000")
			{
				CHECK(bank.GetAccountBalance(account) == 0);
				CHECK(bank.GetCash() == 1000);
			}
		}
		WHEN("Oppening multiple accounts")
		{
			auto firstAccount = bank.OpenAccount();
			auto secondaccount = bank.OpenAccount();
			THEN("The are unique and zero balance")
			{
				CHECK(firstAccount != secondaccount);
				CHECK(bank.GetAccountBalance(firstAccount) == 0);
				CHECK(bank.GetAccountBalance(secondaccount) == 0);
				CHECK(bank.GetCash() == 1000);
			}
		}
		WHEN("Closing account with balance")
		{
			auto account = bank.OpenAccount();
			bank.DepositMoney(account, 500);
			THEN("Account's balance should be 500 and bank's cash also 500")
			{
				CHECK(bank.GetAccountBalance(account) == 500);
				CHECK(bank.GetCash() == 500);
				AND_THEN("Closing account and bank's cash is 1500")
				{
					CHECK(bank.CloseAccount(account));
					CHECK(bank.GetCash() == 1000);
				}
			}
		}
		WHEN("Closing non-existing account")
		{
			auto account = 500;
			THEN("should be BankErrorException")
			{
				CHECK_THROWS_AS(bank.CloseAccount(account), BankOperationError);
			}
		}
	}
}

TEST_CASE("Deposit operations")
{
	GIVEN("Bank with 10000 cash")
	{
		Bank bank(10000);
		auto account = bank.OpenAccount();
		WHEN("Deposit valid money")
		{
			auto money = 500;
			bank.DepositMoney(account, money);
			THEN("Account with 500 cash")
			{
				CHECK(bank.GetAccountBalance(account) == money);
				CHECK(bank.GetCash() == 9500);
			}
		}
		WHEN("Deposit all cash")
		{
			auto money = 10000;
			bank.DepositMoney(account, money);
			THEN("Account with all cash")
			{
				CHECK(bank.GetAccountBalance(account) == money);
				CHECK(bank.GetCash() == 0);
			}
		}
		WHEN("Deposit is more than possible")
		{
			auto money = 40000;
			THEN("It should be BankOperationError")
			{
				CHECK_THROWS_AS(bank.DepositMoney(account, money), BankOperationError);
			}
		}
		WHEN("Deposit negative cash")
		{
			auto money = -500;
			THEN("It should be BankOperationError")
			{
				CHECK_THROWS_AS(bank.DepositMoney(account, money), std::out_of_range);
			}
		}
		WHEN("Deposit to non-existing account")
		{
			auto money = 500;
			THEN("It should be BankOperationError")
			{
				CHECK_THROWS_AS(bank.DepositMoney(20, money), BankOperationError);
			}
		}
	}
}

TEST_CASE("Withdraw operations")
{
	GIVEN("Bank with 1000 cash")
	{
		Bank bank(1000);
		auto account = bank.OpenAccount();
		bank.DepositMoney(account, 500);
		WHEN("Withdrawing a valid amount using WithdrawMoney")
		{
			bank.WithdrawMoney(account, 300);
			THEN("It should decrease balance and increase cash")
			{
				CHECK(bank.GetAccountBalance(account) == 200);
				CHECK(bank.GetCash() == 800);
			}
		}
		WHEN("Withdrawing a valid amount using TryWithdrawMoney") 
		{
			bool success = bank.TryWithdrawMoney(account, 300);
			THEN("It should decrease balance and increase cash") 
			{
				CHECK(success == true);
				CHECK(bank.GetAccountBalance(account) == 200);
				CHECK(bank.GetCash() == 800);
			}
		}
	}

	GIVEN("A bank with an account having insufficient balance") 
	{
		Bank bank(1000);
		auto account = bank.OpenAccount();
		bank.DepositMoney(account, 500);
		WHEN("Withdrawing more than balance using WithdrawMoney") 
		{
			THEN("It should throw BankOperationError") {
				CHECK_THROWS_AS(bank.WithdrawMoney(account, 501), BankOperationError);
				AND_THEN("Balance and cash should remain unchanged") 
				{
					CHECK(bank.GetAccountBalance(account) == 500);
					CHECK(bank.GetCash() == 500);
				}
			}
		}

		WHEN("Withdrawing more than balance using TryWithdrawMoney") 
		{
			bool success = bank.TryWithdrawMoney(account, 501);
			THEN("It should return false") {
				CHECK(success == false);
				AND_THEN("Balance and cash should remain unchanged") 
				{
					CHECK(bank.GetAccountBalance(account) == 500);
					CHECK(bank.GetCash() == 500);
				}
			}
		}
	}

	GIVEN("A bank with an account") 
	{
		Bank bank(1000);
		auto account = bank.OpenAccount();
		WHEN("Withdrawing a negative amount") 
		{
			THEN("It should throw out_of_range for both WithdrawMoney and TryWithdrawMoney") 
			{
				CHECK_THROWS_AS(bank.WithdrawMoney(account, -100), std::out_of_range);
				CHECK_THROWS_AS(bank.TryWithdrawMoney(account, -100), std::out_of_range);
				AND_THEN("Balance and cash should remain unchanged") 
				{
					CHECK(bank.GetAccountBalance(account) == 0);
					CHECK(bank.GetCash() == 1000);
				}
			}
		}

		WHEN("Withdrawing from a non-existent account") {
			auto invalidId = 999;
			THEN("It should throw BankOperationError") {
				CHECK_THROWS_AS(bank.WithdrawMoney(invalidId, 100), BankOperationError);
				CHECK_THROWS_AS(bank.TryWithdrawMoney(invalidId, 100), BankOperationError);
			}
		}
	}
}

