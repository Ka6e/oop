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
	CarMovementState direction = CarMovementState::STAY;
	bool IsValidSpeed(int speed);
	bool IsValidGear(int gear);
	bool isTurnedOn = false;
	int speed = 0;
	int gear = 0;
};
