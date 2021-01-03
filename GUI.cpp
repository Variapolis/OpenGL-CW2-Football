#include "GUI.h"

GUI::GUI(GLuint tex) : GameObject(), m_texture(tex)
{
	scale(0.1);
}

GUI::GUI(GLuint tex, float x, float y) : GameObject(x, y, 0), m_texture(tex)
{
	scale(0.1);
}

void GUI::draw()
{
	glPushMatrix();
	//add some lighting normals for each vertex
	//draw the texture on the front
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 10, 10, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	// glFrontFace(GL_CW); //use glFrontFace(GL_CW) to texture the other side - not needed here as we set this elsewhere
	glColor3f(0.8, 0.8, 0.8);
	

	// translates to object position. TODO MY OWN COMMENT
	glTranslatef(transform.position.x, transform.position.y, 0);
	glRotatef(transform.rotation.x, 1, 0, 0);
	glRotatef(transform.rotation.y, 0, 1, 0);
	glRotatef(transform.rotation.z, 0, 0, 1);

	//binds the texture 
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-transform.scale.x / 2, -transform.scale.y / 2, 0);
	glTexCoord3f(1.0, 0.0, 0.0);
	glVertex3f(transform.scale.x / 2, -transform.scale.y / 2, 0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(transform.scale.x / 2, transform.scale.y / 2, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-transform.scale.x / 2, transform.scale.y / 2, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glFlush();
}
