#pragma once
#include <unordered_map>

using AccountId = unsigned long long;
using Money = long long;

// ������������ ��� ������ � ������� (��� ��������, ��� � �����������)
class Bank
{
public:
	// �������������� ���������� �������. cash � ���������� ����� � �������� �������
	// ��� ������������� ���������� �����, ������������� BankOperationError
	explicit Bank(Money cash);

	Bank(const Bank&) = delete;
	Bank& operator=(const Bank&) = delete;


	// ��������� ������ � ��������� ����� (srcAccountId) �� ������� (dstAccountId)
	// ������ ��������� ������, ��� ���� �� �������� �����
	// ������ ��������� ������������� ���������� �����
	// ���������� BankOperationError �������������, ��� ���������� ������ ���
	// ���������� ����� �� �������� �����
	// ��� ������������� ���������� ����������� ����� ������������� std::out_of_range
	void SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount);

	// ��������� ������ � ��������� ����� (srcAccountId) �� ������� (dstAccountId)
	// ������ ��������� ������, ��� ���� �� �������� �����
	// ������ ��������� ������������� ���������� �����
	// ��� �������� ����� �� �������� ����� ������������ false
	// ���� ������ ������ ���������, ������������� BankOperationError
	// ��� ������������� ���������� ����� ������������� std::out_of_range
	[[nodiscard]] bool TrySendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount);

	// ���������� ���������� �������� ����� � �������
	[[nodiscard]] Money GetCash() const;

	// �������� � ���������� ����� �� ��������� �����
	// ���� ��������� ���� �����������, ������������� ���������� BankOperationError
	Money GetAccountBalance(AccountId accountId) const;

	// ������� ������ �� �����. ������ ����� ������, ��� ���� �� �����
	// ������ ����� ������������� ���������� �����
	// ������ ������ ��������� ����������� � ����� �������� �����
	// ��� ���������� ������ ����� ��� ���������� �����, ������������� ���������� BankOperationError
	// ��� ������������� ���������� ����� ������������� std::out_of_range
	void WithdrawMoney(AccountId account, Money amount);

	// ���������� ����� ������ � ������� amount �� ����� account.
	// ����� ����� � �������� ������� ������������� �� �������� amount
	// ��� �������� ����� �� ����� ������������ false, � ���������� �������� ����� ������� ����������
	// ��� ���������� ������ �������� ������������� BankOperationError.
	// ��� ������������� ���������� ����� ������������� std::out_of_range
	[[nodiscard]] bool TryWithdrawMoney(AccountId account, Money amount);

	// ��������� �������� ������ �� ����. ���������� ����� � �������� �������
	// ����������� �� �������� amount.
	// ������ ��������� ������, ��� ������� ����� � �������� �������
	// ������ ��������� �� ���� ������������� ���������� �����
	// ������ ��������� ������ �� ������������� ����
	// ��� ���������� ������ �������� ��� �������� �������� ����� � ������� ������������� BankOperationError.
	// ��� ������������� ���������� ����� ������������� std::out_of_range
	void DepositMoney(AccountId account, Money amount);

	// ��������� ���� � �����. ����� �������� ����� �� �� ������� ������.
	// ������ �������� ���� ����� ���������� �����.
	// ���������� ����� �����
	[[nodiscard]] AccountId OpenAccount();

	// ��������� ��������� ����.
	// ���������� ���������� �����, ������� ���� �� ����� � ������ ��������
	// ��� ������ ��������� � �������� ������
	[[nodiscard]] Money CloseAccount(AccountId accountId);


private:
	Money m_cash; 
	AccountId m_nextAccountId;
	std::unordered_map<AccountId, Money> m_accounts;
	//bool IsAccountValid(AccountId accountId) const;
};