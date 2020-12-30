#include "Vec3.h"

#include <cmath>

vec3_f::vec3_f():x(0),y(0),z(0)
{
}

vec3_f::vec3_f(const float x, const float y) : x(x), y(y),z(0)
{
}

vec3_f::vec3_f(const float x, const float y, const float z) : x(x), y(y), z(z)
{
}

vec3_f& vec3_f::operator+(const vec3_f& other) const
{
	return vec3_f(x + other.x, y + other.y, z + other.z);
}

vec3_f& vec3_f::operator-(const vec3_f& other) const
{
	return vec3_f(x - other.x, y - other.y, z - other.z);
}

vec3_f& vec3_f::operator*(const vec3_f& other) const
{
	return vec3_f(x * other.x, y * other.y, z * other.z);
}

vec3_f& vec3_f::operator+=(const vec3_f& other)
{
	x = x + other.x;
	y = y + other.y;
	z = z + other.z;
	return *this;
}

vec3_f& vec3_f::operator-=(const vec3_f& other)
{
	x = x - other.x;
	y = y - other.y;
	z = z - other.z;
	return *this;
}

vec3_f& vec3_f::operator*=(const vec3_f& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

vec3_f& vec3_f::operator*=(const float num)
{
	x *= num;
	y *= num;
	z *= num;
	return *this;
}

bool vec3_f::operator==(const vec3_f& other) const
{
	return (x == other.x && y == other.y && z == other.z);
}

bool vec3_f::operator!=(const vec3_f& other) const
{
	return !(x == other.x && y == other.y && z == other.z);
}

vec3_f& vec3_f::operator*(float num) const
{
	return vec3_f(x*num,y*num,z*num);
}

vec3_f& vec3_f::operator/(float num) const
{
	return vec3_f(x / num, y / num, z / num);
}

vec3_f& vec3_f::cross(vec3_f& other) const
{
	return operator*(other);
}

float vec3_f::magnitude() const
{
	return sqrt(pow(x,2)+ pow(y, 2)+ pow(z, 2));
}

float vec3_f::dot(vec3_f& other) const
{
	return (x * other.x) + (y* other.y) + (z* other.z);
}

vec3_f& vec3_f::normalized() const
{
	const float mag = magnitude();
	return vec3_f(x / mag, y / mag, z / mag);
}


