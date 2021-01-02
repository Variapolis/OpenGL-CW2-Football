#include "GameObject.h"

GameObject::GameObject(): transform()
{
	scale(10);
}

GameObject::GameObject(float x, float y, float z) : transform(x,y,z)
{
	scale(10);
}

void GameObject::draw()
{
}

void GameObject::scale(float scale)
{
	transform.scale.x *= scale;
	transform.scale.y *= scale;
}

void GameObject::remove() const
{
	delete this;
}
