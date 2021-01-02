#pragma once
#include "TexturedPlane.h"
class Target :
    public TexturedPlane
{
private:
	int m_score;
public:
	Target(GLuint tex);
	Target(GLuint tex, float x, float y, float z);
	int getScore();
};

