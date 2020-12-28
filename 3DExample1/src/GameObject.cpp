#include "GameObject.h"

GameObject::GameObject(GLfloat x, GLfloat y, GLfloat width, GLfloat height):_posX(x), _posY(y), _width(width), _height(height) // constructor for 
{
	
}

GameObject::GameObject(GLfloat x, GLfloat y): _posX(x), _posY(y), _width(1), _height(1) // constructor for only x and y
{
	
}

GameObject::GameObject(): _posX(0), _posY(0), _width(1),_height(1) // default constructor
{
}

GLfloat GameObject::getPosX()	{ return _posX; } // Getters for pos and size
GLfloat GameObject::getPosY()	{ return _posY; }
GLfloat GameObject::getWidth()	{ return _width; }
GLfloat GameObject::getHeight() { return _height; }


void GameObject::Move(GLfloat x, GLfloat y) { _posX += x; _posY += y; } // Moves the object by a certain amount

void GameObject::MoveTo(GLfloat x, GLfloat y){ _posX = x; _posY = y; } // Moves the object to a specified coordinate

void GameObject::Resize(GLfloat width, GLfloat height) { _width = width; _height = height; } // Resizes the object
void GameObject::ResizeWidth(GLfloat width) { _width = width; }
void GameObject::ResizeHeight(GLfloat height) {_height = height; }