#include "Football.h"

Football::Football(GLuint tex) : GameObject(), texture(tex)
{
	
}

Football::Football(GLuint tex, float r) : texture(tex), GameObject(), radius(r)
{
	transform.scale.x = radius;
	transform.scale.y = radius;
	transform.scale.z = radius;
}

Football::Football(GLuint tex, float r, float x, float y, float z  ) : texture(tex), GameObject(x,y,z), radius(r)
{
	transform.scale.x = radius;
	transform.scale.y = radius;
	transform.scale.z = radius;
}

void Football::draw()
{
	glPushMatrix();
	glFrontFace(GL_CCW);
	glTranslatef(transform.position.x, transform.position.y, transform.position.z);
	glRotatef(transform.rotation.x, 1,0,0);
	glRotatef(transform.rotation.y, 0, 1, 0);
	glRotatef(transform.rotation.z, 0, 0, 1);
	// Create and texture the ball
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	// glDisable(GL_LIGHTING);
	glColor3f(0.5, 0.5, 0.5);
	quadricBall = gluNewQuadric();
	gluQuadricDrawStyle(quadricBall, GLU_FILL);
	gluQuadricNormals(quadricBall, GLU_SMOOTH);
	gluQuadricOrientation(quadricBall, GLU_OUTSIDE);
	gluQuadricTexture(quadricBall, GL_TRUE);
	gluSphere(quadricBall, radius, 50, 35);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
