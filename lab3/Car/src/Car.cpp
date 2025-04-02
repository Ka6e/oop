#include "../include/Car.h"
#include <iostream>

const int MIN_SPEED = 0;
const int MAX_BACKWARD_SPEED = 20;
const int MAX_FIRST_GEAR_SPEED = 30;
const int MIN_SECOND_GEAR_SPEED = 20;
const int MAX_SECOND_GEAR_SPEED = 50;
const int MIN_THIRD_GEAR_SPEED = 30;
const int MAX_THIRD_GEAR_SPEED = 60;
const int MIN_FOURTH_GEAR_SPEED = 40;
const int MAX_FOURTH_GEAR_SPEED = 90;
const int MIN_FIFTH_GEAR_SPEED = 50;
const int MAX_FIFTH_GEAR_SPEED = 150;

bool Car::TurnOnEngine()
{
	this->isTurnedOn = true;
	std::cout << "Engine is on" << std::endl;
	return true;
}

bool Car::TurnOffEngine()
{
	if (m_speed != 0 || m_gear != 0)
	{
		return false;
	}
	this->isTurnedOn = false;
	std::cout << "Engine is off" << std::endl;
	return true;
}

void Car::SetDirection()
{
	if (m_speed == 0)
	{
		this->direction = CarMovementState::STAY;
		return;
	}
	if (m_gear == -1)
	{
		this->direction = CarMovementState::BACKWARD;
		return;
	}
	if (m_gear > 0)
	{
		this->direction = CarMovementState::FORWARD;
	}
}



bool Car::SetGear(int gear)
{
	//не здесь проверяется
	bool checkGear = IsValidGear(gear);

	if (!checkGear)
	{
		return false;
	}
	m_gear = gear;
	std::cout << "The gear is set to " << gear << std::endl;
	return true;

}

bool Car::SetSpeed(int speed)
{
	bool checkSpeed = IsValidSpeed(speed);
	if (!checkSpeed)
	{
		return false;
	}
	m_speed = speed;
	std::cout << "The speed is set to " << speed << std::endl;
	SetDirection();
	return true;
}

bool Car::IsTurnedOn()
{
	return this->isTurnedOn;
}

CarMovementState Car::GetDirection()
{
	return this->direction;
}

int Car::GetSpeed()  
{  
return m_speed;  
}

int Car::GetGear()
{
	return m_gear;
}
//структура или map для проверки
bool Car::IsValidSpeed(int speed)
{
	if (!this->isTurnedOn)
	{
		std::cout << "Cannot set speed while engine is off" << std::endl;
		return false;
	}
	if (speed < MIN_SPEED)
	{
		std::cout << "Speed cannot be negative" << std::endl;
		return false;
	}
	if (m_gear == 0 && speed > m_speed)
	{
		std::cout << "Cannot accelerate on neutral" << std::endl;
		return false;
	}
	if (m_gear == -1 && (speed < MIN_SPEED || speed > MAX_BACKWARD_SPEED) ||
		m_gear == 1 && (speed < MIN_SPEED || speed > MAX_FIRST_GEAR_SPEED) ||
		m_gear == 2 && (speed < MIN_SECOND_GEAR_SPEED || speed > MAX_SECOND_GEAR_SPEED) ||
		m_gear == 3 && (speed < MIN_THIRD_GEAR_SPEED || speed > MAX_THIRD_GEAR_SPEED) ||
		m_gear == 4 && (speed < MIN_FOURTH_GEAR_SPEED || speed > MAX_FOURTH_GEAR_SPEED) ||
		m_gear == 5 && (speed < MIN_FIFTH_GEAR_SPEED || speed > MAX_FIFTH_GEAR_SPEED))
	{
		std::cout << "Speed is out of gear range" << std::endl;
		return false;
	}
	return true;
}

bool Car::IsValidGear(int gear)
{
	if (!this->isTurnedOn)
	{
		std::cout << "Cannot set gear while engine is off" << std::endl;
		return false;
	}
	if (gear < 0 && this->direction == CarMovementState::FORWARD ||
		gear > 0 && this->direction == CarMovementState::BACKWARD)
	{
		return false;
	}
	if (gear < -1 || gear > 5)
	{
		std::cout << "Invalid gear" << std::endl;
		return false;
	}
	if (m_speed > 0 && (m_gear > 0 && gear < 0
		|| m_gear < 0 && gear > 0))
	{
		std::cout << "Cannot reverse while moving" << std::endl;
		return false;
	}

	if (gear == -1 && (m_speed < MIN_SPEED || m_speed > MAX_BACKWARD_SPEED) || 
		gear == 1 && (m_speed < MIN_SPEED || m_speed > MAX_FIRST_GEAR_SPEED) ||
		gear == 2 && (m_speed < MIN_SECOND_GEAR_SPEED || m_speed > MAX_SECOND_GEAR_SPEED) ||
		gear == 3 && (m_speed < MIN_THIRD_GEAR_SPEED || m_speed > MAX_THIRD_GEAR_SPEED) ||
		gear == 4 && (m_speed < MIN_FOURTH_GEAR_SPEED || m_speed > MAX_FOURTH_GEAR_SPEED) ||
		gear == 5 && (m_speed < MIN_FIFTH_GEAR_SPEED || m_speed > MAX_FIFTH_GEAR_SPEED)
		)
	{
		std::cout << "Unsuitable current speed" << std::endl;
		return false;
	}
	return true;
}