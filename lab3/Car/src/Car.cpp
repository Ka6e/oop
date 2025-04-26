#include "../include/Car.h"
#include <iostream>
#include <map>

std::map<int, std::pair<int, int>> speedRange =
{
	{-1, {0, 20}},
	{0, {0, 150}},
	{1, {0, 30}},
	{2, {20, 50}},
	{3, {30, 60}},
	{4, {40, 90}},
	{5, {50, 150}},
};

bool Car::TurnOnEngine()
{
	m_isTurnedOn = true;
	std::cout << "Engine is on" << std::endl;
	return true;
}

bool Car::TurnOffEngine()
{
	if (m_speed != 0 || m_gear != 0)
	{
		return false;
	}
	m_isTurnedOn = false;
	std::cout << "Engine is off" << std::endl;
	return true;
}

void Car::SetDirection()
{
	if (m_speed == 0)
	{
		m_direction = CarMovementState::STAY;
		return;
	}
	if (m_gear == -1)
	{
		m_direction = CarMovementState::BACKWARD;
		return;
	}
	if (m_gear > 0)
	{
		m_direction = CarMovementState::FORWARD;
	}
}



bool Car::SetGear(int gear)
{

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
	return m_isTurnedOn;
}

CarMovementState Car::GetDirection()
{
	return m_direction;
}

int Car::GetSpeed()  
{  
	return m_speed;  
}

int Car::GetGear()
{
	return m_gear;
}

bool Car::IsValidSpeed(int speed)
{
	if (!m_isTurnedOn)
	{
		std::cout << "Cannot set speed while engine is off" << std::endl;
		return false;
	}
	if (speed < 0)
	{
		std::cout << "Speed cannot be negative" << std::endl;
		return false;
	}
	if (m_gear == 0 && speed > m_speed)
	{
		std::cout << "Cannot accelerate on neutral" << std::endl;
		return false;
	}
	if (speedRange.find(m_gear) != speedRange.end())
	{
		auto speedRangePair = speedRange.at(m_gear);
		int minSpeed = speedRangePair.first;
		int maxSpeed = speedRangePair.second;
		if (speed < minSpeed || speed > maxSpeed)
		{
			std::cout << "Speed is out of gear range" << std::endl;
			return false;
		}
	}
	return true;
}

bool Car::IsValidGear(int gear)
{
	if (!m_isTurnedOn)
	{
		std::cout << "Cannot set gear while engine is off" << std::endl;
		return false;
	}
	if (gear < 0 && m_direction == CarMovementState::FORWARD ||
		gear > 0 && m_direction == CarMovementState::BACKWARD)
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
	if (speedRange.find(m_gear) != speedRange.end())
	{
		auto speedRangePair = speedRange.at(gear);
		int minSpeed = speedRangePair.first;
		int maxSpeed = speedRangePair.second;
		if (m_speed < minSpeed || m_speed > maxSpeed)
		{
			std::cout << "Unsuitable current speed" << std::endl;
			return false;
		}
	}
	return true;
}