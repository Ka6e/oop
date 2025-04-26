#pragma once
#include <stdexcept>

class BankOperationError : std::runtime_error
{
public:
	explicit BankOperationError(const std::string& message) :
		std::runtime_error(message)
	{
	}
	using runtime_error::runtime_error;
};
