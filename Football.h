#pragma once
#include "GameObject.h"
class Football : public GameObject
{
	GLUquadricObj* quadricBall;
	GLuint texture;
	float radius;
public:
	Football::Football(GLuint tex);
	Football::Football(GLuint tex, float r);
	Football::Football(GLuint tex, float r, float x, float y, float z);
	void draw();
};

