#include "GameObject.h"

GameObject::Transform::Transform() : position(0,0,0), rotation(0, 0, 0), scale(1, 1, 1)
{
}

GameObject::Transform::Transform(float x, float y, float z): position(x, y, z), rotation(0, 0, 0), scale(1, 1, 1)
{
}
