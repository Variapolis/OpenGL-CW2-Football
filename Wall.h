#pragma once
#include "GameObject.h"

class Wall :
    public GameObject
{
		GLuint m_texture;
	public:
		Wall(GLuint tex);
		Wall(GLuint tex, float x, float y, float z);
		void draw();
};

