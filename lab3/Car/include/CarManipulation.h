#pragma once
#include "Car.h"
#include "StringOperations.h"
#include <iostream>
#include <algorithm>

void PrintInfo(Car& car);
bool CheckInt(std::string& str);
void TurnOffEngine(Car& car);
void TurnOnEngine(Car& car);
void SetCarSpeed(Car& car, std::string& str);
void SetGear(Car& car, std::string& str);
void WorkingWithCar();

