#pragma once
#include "GameObject.h"

class GUI :
		public GameObject
{
	GLuint m_texture;
public:
	float value;
	GUI(GLuint tex);
	GUI(GLuint tex, float x, float y);
	void draw(float w, float h);
	
};

