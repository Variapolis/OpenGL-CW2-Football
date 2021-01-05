#pragma once
#include "GameObject.h"
class TexturedPlane :
    public GameObject
{
public:
	GLuint m_texture;
	TexturedPlane(GLuint tex);
	TexturedPlane(GLuint tex, float x, float y, float z);
	void draw();
};

