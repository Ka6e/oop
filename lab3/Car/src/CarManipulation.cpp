#include "../include/CarManipulation.h"
#include "../Car/include/Car.h"

void PrintInfo(Car& car)
{
	std::string direction;

	switch (car.GetDirection())
	{
	case CarMovementState::FORWARD:
		direction = "forward";
		break;
	case CarMovementState::BACKWARD:
		direction = "backward";
		break;
	case CarMovementState::STAY:
		direction = "standing still";
		break;
	default:
		std::cout << "Unkown direction" << std::endl;
		break;
	}

	std::cout << "Engine: " << (car.IsTurnedOn() ? "On" : "Off") << std::endl
		<< "Direction: " << direction << std::endl
		<< "Speed: " << (car.GetSpeed()) << std::endl
		<< "Gear: " << (car.GetGear()) << std::endl;
}

void TurnOffEngine(Car& car)
{
	if (!car.TurnOffEngine())
	{
		std::cout << "Car must be stopped and in neutral gear" << std::endl;
	}
}

void TurnOnEngine(Car& car)
{
	car.TurnOnEngine();
}

void ConvertStringToInt(const std::string& str, int& value)
{
	try
	{
		size_t pos;
		value = std::stoi(str,&pos);

		if (pos != str.length())
		{
			throw std::invalid_argument("Invalid command argument");
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void SetSpeed(Car& car, std::string& str)
{
	int speed;
	ConvertStringToInt(str, speed);
	if (!car.SetSpeed(speed))
	{
		std::cout << "Unable to set speed to " << speed << std::endl;
	}
}

void SetGear(Car& car, std::string& str)
{
	int gear;
	ConvertStringToInt(str, gear);
	if (!car.SetGear(gear))
	{
		std::cout << "Unable to set gear to " << gear << std::endl;
	}
}

void WorkingWithCar()
{
	Car car;
	std::string line;
	do
	{
		std::getline(std::cin, line);
		ToLower(line);
		std::string value;
		Trim(line, value);
		switch (CompareStrings(line))
		{
		case State::ENGINE_ON:
			TurnOnEngine(car);
			break;
		case State::ENGINE_OFF:
			TurnOffEngine(car);
			break;
		case State::SET_SPEED:
			SetSpeed(car, value);
			break;
		case State::SET_GEAR:
			SetGear(car, value);
			break;
		case State::INFO:
			PrintInfo(car);
			break;
		case State::UNKNOWN:
			std::cout << "Unknown command" << std::endl;
			break;
		}
		std::cout << std::endl;
	} while (line != QUIT);
}