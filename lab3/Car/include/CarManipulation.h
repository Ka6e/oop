#pragma once
#include "Car.h"
#include "StringOperations.h"


//вынести инклюды
void PrintInfo(Car& car);
void TurnOffEngine(Car& car);
void TurnOnEngine(Car& car);
void SetCarSpeed(Car& car, std::string& str);
void SetGear(Car& car, std::string& str);
void WorkingWithCar();

