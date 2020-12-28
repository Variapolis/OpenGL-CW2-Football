#pragma once
#include "GameObject.h"
class Rect :
    public GameObject //Rect class object used as a base and as an individual object for drawing rectangle polygons.
{
	GLfloat _red, _green, _blue;
public:
	Rect(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
	Rect(GLfloat x, GLfloat y);
	Rect();
	void Draw();
	void SetColor(GLfloat red, GLfloat green, GLfloat blue);
};

