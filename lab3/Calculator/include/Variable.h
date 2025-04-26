#pragma once
#include <string>
//�������� ����� �� ������ � ������ �� ���� ��� ���������
class Variable
{
public:
	Variable() = default;
	Variable(std::string identifier, double value = NAN);
	std::string GetIdentifier() const;
	void SetValue(double value);
	double GetValue() const;

private:
	std::string m_identifier;
	double m_value = NAN;
};
