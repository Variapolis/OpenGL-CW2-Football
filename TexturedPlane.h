#pragma once
#include "GameObject.h"
class TexturedPlane :
    public GameObject
{
	GLuint m_texture;
public:
	TexturedPlane(GLuint tex);
	TexturedPlane(GLuint tex, float x, float y, float z);
	void draw();
};

