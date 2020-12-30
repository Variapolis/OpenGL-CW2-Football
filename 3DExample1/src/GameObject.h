#pragma once
#include "freeglut.h"
#include "ConsoleDebug.h"
#include "Transform.h"
class GameObject //Base class for every object, used to store position and size information.
{
public:
	Transform transform;
	GameObject();
	GameObject(float x, float y, float z);
	void draw();
};

