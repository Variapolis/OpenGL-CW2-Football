#include "GameObject.h"

GameObject::GameObject(): transform()
{
}

GameObject::GameObject(float x, float y, float z) : transform(x,y,z)
{
}

void GameObject::draw()
{
}

void GameObject::remove() const
{
	delete this;
}
