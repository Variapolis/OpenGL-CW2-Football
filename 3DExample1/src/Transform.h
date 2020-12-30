#pragma once
#include <Vector3.h>

class Transform {
public:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	Transform();
	Transform(float x, float y, float z);
	
};
