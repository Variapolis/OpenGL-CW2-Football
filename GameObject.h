#pragma once
#include <gl/freeglut.h>
#include "ConsoleDebug.h"
#include "Transform.h"
#include "Vector3.h"




class GameObject //Base class for every object, used to store position and size information.
{
	struct Transform
	{
		Vector3 position;
		Vector3 rotation;
		Vector3 scale;
		Transform();
		Transform(float x, float y, float z);
	};
public:
	Transform transform;
	GameObject();
	GameObject(float x, float y, float z);
	void draw();
	void scale(float);
	void remove() const;
};

