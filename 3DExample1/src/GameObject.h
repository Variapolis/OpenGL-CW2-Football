#pragma once
#include "freeglut.h"
#include "ConsoleDebug.h"
class GameObject //Base class for every object, used to store position and size information.
{
protected:
	GLfloat _posX, _posY, _width, _height;
public:
	GameObject(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
	GameObject(GLfloat x, GLfloat y);
	GameObject();
	GLfloat getPosX(); 	GLfloat getPosY();	GLfloat getWidth();	GLfloat getHeight();
	void Move(GLfloat x, GLfloat y);
	void MoveTo(GLfloat x, GLfloat y);
	void Resize(GLfloat width, GLfloat height);
	void ResizeWidth(GLfloat width);
	void ResizeHeight(GLfloat height);
};

