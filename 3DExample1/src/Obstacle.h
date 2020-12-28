#pragma once
#include "Rect.h"
class Obstacle :  public Rect //Essentially a copy of Rect, open ended class to allow for more functionality to be given to obstacles at a later date.
{
public:
	Obstacle(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
	Obstacle(GLfloat x, GLfloat y);
	Obstacle();
	
};

