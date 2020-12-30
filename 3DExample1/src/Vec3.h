#pragma once
struct vec3_f
{
	float x, y, z;

	vec3_f();
	vec3_f(float x, float y);
	vec3_f(float x, float y, float z);
	
	vec3_f& operator + (const vec3_f&) const;
	vec3_f& operator - (const vec3_f&) const;
	vec3_f& operator * (const vec3_f&) const;
	
	vec3_f& operator += (const vec3_f&);
	vec3_f& operator -= (const vec3_f&);
	vec3_f& operator *= (const vec3_f&);
	vec3_f& operator *= (float);
	
	bool operator == (const vec3_f&) const;
	bool operator != (const vec3_f&) const;
	
	vec3_f& operator * (float) const;
	
	vec3_f& operator / (float) const;

	vec3_f& cross(vec3_f&) const;
	float magnitude() const;
	float dot(vec3_f&) const;
	vec3_f& normalized() const;
	
};

