#pragma once
#include <string>
#include <algorithm>

const std::string ENGINE_ON = "engineon";
const std::string ENGINE_OFF = "engineoff";
const std::string SET_GEAR = "setgear";
const std::string SET_SPEED = "setspeed";
const std::string INFO = "info";
const std::string QUIT = "quit";

enum class State
{
	ENGINE_ON,
	ENGINE_OFF,
	SET_GEAR,
	SET_SPEED,
	INFO,
	UNKNOWN
};


State CompareStrings(std::string& str1);
std::string ToLower(std::string& line);
void Trim(std::string& str1, std::string& str2);