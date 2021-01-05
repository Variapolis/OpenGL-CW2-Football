#pragma once
#include "GameObject.h"
class Football : public GameObject
{
	GLUquadricObj* m_quadricBall;
	GLuint m_texture;
	float m_radius;
	Vector3 m_velocity, m_acceleration;
public:
	Football::Football(GLuint tex);
	Football::Football(GLuint tex, float r);
	Football::Football(GLuint tex, float r, float x, float y, float z);
	bool checkPlaneCollision(GameObject);
	void draw();
};

