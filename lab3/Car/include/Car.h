#pragma once

enum class CarMovementState
{
	FORWARD,
	BACKWARD,
	STAY,
};

class Car
{
public:
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
	bool IsTurnedOn();
	CarMovementState GetDirection();
	int GetSpeed();
	int GetGear();
		
private:
	void SetDirection();
	CarMovementState m_direction = CarMovementState::STAY;
	bool IsValidSpeed(int speed);
	bool IsValidGear(int gear);
	bool m_isTurnedOn = false;
	int m_speed = 0;
	int m_gear = 0;
};
