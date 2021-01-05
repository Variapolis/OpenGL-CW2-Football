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
	std::cout << "Welcome to my Football Game! "<< std::endl;
	std::cout << "Up Arrow - Aim Higher" << std::endl;
	std::cout << "Down Arrow - Aim Lower" << std::endl;
	std::cout << "Left Arrow - Aim Left" << std::endl;
	std::cout << "Right Arrow - Aim Right" << std::endl;
	std::cout << "Space or Z - Shoot" << std::endl;
	std::cout << "R - Restart" << std::endl;
	std::cout << "F - Follow ball" << std::endl;
	std::cout << "Hit the targets to win." << std::endl;
}
