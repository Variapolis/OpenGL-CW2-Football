#include "ConsoleDebug.h"

#include "Vector3.h"

// File used  to contain Debug functions neatly.

void Log(std::string message){
std::cout<< "Debug Log: " << message << std::endl;
}

void LogIntValue(std::string message, int value, std::string message2)
{
	std::cout << "DebugValue Log: "<< message << value << message2 << std::endl;
}

void LogIntValue(std::string message, int value) // Log overload
{
	std::cout << "DebugValue Log: " << message << value << std::endl;
}

void LogIntValue(std::string message, Vector3 value) // Log overload
{
	std::cout << "DebugValue Log: " << message << "X: " << value.x << "Y: " << value.y << "Z: " << value.z << std::endl;
}

void LogIntro() // TODO Change intro
{
	std::cout << "Welcome to my Car Game! By Tautvydas Marcinkevicius"<< std::endl;
	std::cout << "W - Move Up" << std::endl;
	std::cout << "S - Move Down" << std::endl;
	std::cout << "A - Move Left" << std::endl;
	std::cout << "D - Move Right" << std::endl;
	std::cout << "R - Rotate 90" << std::endl;
	std::cout << "Reach the red gate and avoid the obstacles!" << std::endl;
}
