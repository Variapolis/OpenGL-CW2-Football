#include "TexturedPlane.h"

TexturedPlane::TexturedPlane(GLuint tex) : GameObject(), m_texture(tex)
{
}

TexturedPlane::TexturedPlane(GLuint tex, float x, float y, float z) : GameObject(x, y, z), m_texture(tex)
{
}

void TexturedPlane::draw()
{
	glPushMatrix();
	//add some lighting normals for each vertex
	//draw the texture on the front
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glFrontFace(GL_CW); //use glFrontFace(GL_CW) to texture the other side - not needed here as we set this elsewhere
	glColor3f(0.8, 0.8, 0.8);
	glEnable(GL_TEXTURE_2D);

	// translates to object position.
	glTranslatef(transform.position.x, transform.position.y, transform.position.z);
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
}
