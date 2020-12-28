#include "Obstacle.h"

Obstacle::Obstacle(GLfloat x, GLfloat y, GLfloat width, GLfloat height):Rect(x,y,width,height)
{
}

Obstacle::Obstacle(GLfloat x, GLfloat y) : Rect(x, y)
{
}

Obstacle::Obstacle():Rect()
{
}
