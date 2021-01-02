#include "Football.h"

Football::Football(GLuint tex) : GameObject(), m_texture(tex)
{
	
}

Football::Football(GLuint tex, float r) : GameObject(), m_texture(tex), m_radius(r)
{
	transform.scale.x = m_radius;
	transform.scale.y = m_radius;
	transform.scale.z = m_radius;
}

Football::Football(GLuint tex, float r, float x, float y, float z  ) : GameObject(x,y,z), m_texture(tex), m_radius(r)
{
	transform.scale.x = m_radius;
	transform.scale.y = m_radius;
	transform.scale.z = m_radius;
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
	glBindTexture(GL_TEXTURE_2D, m_texture);
	// glDisable(GL_LIGHTING);
	glColor3f(0.5, 0.5, 0.5);
	m_quadricBall = gluNewQuadric();
	gluQuadricDrawStyle(m_quadricBall, GLU_FILL);
	gluQuadricNormals(m_quadricBall, GLU_SMOOTH);
	gluQuadricOrientation(m_quadricBall, GLU_OUTSIDE);
	gluQuadricTexture(m_quadricBall, GL_TRUE);
	gluSphere(m_quadricBall, m_radius, 50, 35);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
