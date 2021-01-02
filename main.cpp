//Windows includes - DO NOT EDIT AS LOTS OF INTERDEPENDENCE


#include <math.h>						
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>	//Needed for console output (debugging)
#include <gl/freeglut.h>
#include <iostream>

#include "Football.h"

#ifdef WIN32
#include "gltools.h"
#include <windows.h>		// Must have for Windows platform builds
#include <gl\gl.h>			// Microsoft OpenGL headers (version 1.1 by themselves)
#include <gl\glu.h>			// OpenGL Utilities
#include "glm.h"
#endif

//  Created by Philip Trwoga on 09/11/2012. Modified on 20/1/16 to include the many VS2015 changes
//  Copyright (c) 2012 __Philip Trwoga__. All rights reserved.
// DO NOT DISTRIBUTE WITHOUT THE AUTHOR'S PERMISSION


//note that this needs gltools.h and gltools.cpp to be included in the shared/library directory

//can define any number of textures here - we just have 2 images
//these are just integers so you can use them as such
#define IMAGE1      0
#define IMAGE2      1
#define IMAGE3      2
#define IMAGE4      3
#define TEXTURE_BALL 6    //football map
#define TEXTURE_COUNT 5
GLuint  textures[TEXTURE_COUNT];

//below is simply a character array to hold the file names
//note that you may need to replace the below with the full directory root depending on where you put your image files
//if you put them where the exe is then you just need the name as below - THESE IMAGES  ARE IN THE DEBUG FOLDER, YOU CAN ADD ANY NEW ONES THERE 
const char* textureFiles[TEXTURE_COUNT] = { "pingu.tga", "horse.tga","floor.tga","stone.tga","FootballCompleteMap.tga" };


//for lighting if you want to experiment with these
GLfloat mKa[4] = { 0.11f,0.06f,0.11f,1.0f }; //ambient
GLfloat mKd[4] = { 0.43f,0.47f,0.54f,1.0f }; //diffuse
GLfloat mKs[4] = { 1.0f,1.0f,1.0f,1.0f }; //specular
GLfloat mKe[4] = { 0.5f,0.5f,0.0f,1.0f }; //emission

//spot position and direction
GLfloat	 lightPos[] = { 0.0, 100.0, 300.0, 0.0f };
GLfloat  spotDir[] = { 50.0, 25.0, 0.0 };

GLfloat	 lightPos2[] = { 50.0, 100.0, 300.0, 0.0f };
GLfloat  spotDir2[] = { 50.0, 15.0, 0.0 };

GLfloat	 lightPos3[] = { -50.0, 100.0, 300.0, 0.0f };
GLfloat  spotDir3[] = { 50.0, 15.0, 0.0 };


// Useful lighting colour values
GLfloat  whiteLightBright[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat  redLight[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat  greenLight[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat  blueLight[] = { 0.0f, 1.0f, 1.0f, 1.0f };
GLfloat  whiteLightLessBright[] = { 0.8f, 0.8f, 0.8f, 1.0f };


//we need these for the texture loader
//they are to do with the image format and size
GLint iWidth, iHeight, iComponents;
GLenum eFormat;
// this is a pointer to memory where the image bytes will be held 
GLbyte* pBytes0;

Football* ball = new Football(TEXTURE_BALL, 20, 50, 25, 280);

//camera
GLfloat cameraX = 0.0;
GLfloat cameraY = 100.0;
GLfloat cameraZ = 500.0;

bool repeatOn = false;
bool repeatWallOn = false;
bool moveCamera = false;


//end of intialisation 

//---------------This function is used for Images 1 and 2---------------------//
void drawTexturedQuad(int image)
{
	//add some lighting normals for each vertex
	//draw the texture on the front
	glEnable(GL_TEXTURE_2D);
	// glFrontFace(GL_CW); //use glFrontFace(GL_CW) to texture the other side - not needed here as we set this elsewhere
	glColor3f(0.8, 0.8, 0.8);
	glEnable(GL_TEXTURE_2D);
	//bind the texture 
	glBindTexture(GL_TEXTURE_2D, textures[image]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-50.0, 0.0, 100.0);
	glTexCoord3f(1.0, 0.0, 0.0);
	glVertex3f(50.0, 0.0, 100.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(50.0, 100.0, 100.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-50.0, 100.0, 100.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

//---------------The following two function are used for Images 3 and 4---------------------//
//----This is with tilling-----//
void drawTexturedSurface(int image)
{
	//add some lighting normals for each vertex
	//draw the texture on the front
	//draw face up and then rotated
	glEnable(GL_TEXTURE_2D);
	// glFrontFace(GL_CW); //use glFrontFace(GL_CW) to texture the other side - not needed here as we set this elsewhere
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	//bind the texture
	glBindTexture(GL_TEXTURE_2D, textures[image]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(-4.0, -4.0);//repeated texture
	glVertex3f(-800.0, -800.0, 0.0);
	glTexCoord2f(4.0, -4.0);
	glVertex3f(800.0, -800.0, 0.0);
	glTexCoord2f(4.0, 4.0);
	glVertex3f(800.0, 800.0, 0.0);
	glTexCoord2f(-4.0, 4.0);
	glVertex3f(-800.0, 800.0, 0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

}

//----This is without tilling-----//
void drawTexturedSurfaceNoTiling(int image)
{
	//add some lighting normals for each vertex
	//draw the texture on the front
	//draw face up and then rotated
	glEnable(GL_TEXTURE_2D);
	// glFrontFace(GL_CW); //use glFrontFace(GL_CW) to texture the other side - not needed here as we set this elsewhere
	glColor3f(0.8, 0.8, 0.8);
	glEnable(GL_TEXTURE_2D);
	//bind the texture
	glBindTexture(GL_TEXTURE_2D, textures[image]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0, 0);//repeated texture
	glVertex3f(-800.0, -800.0, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(800.0, -800.0, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(800.0, 800.0, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-800.0, 800.0, 0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

//---------This is used for the football ball-------//

// Called to draw scene
void RenderScene(void)
{
	ball.transform.position.z += 2;
	ball.transform.rotation.x += 2;
	
	// Clear the window with current clearing colour
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// view the scene
	gluLookAt(ball.transform.position.x , ball.transform.position.y +50, ball.transform.position.z + 50,//eye
		ball.transform.position.x, ball.transform.position.y, ball.transform.position.z,//centre
		0.00, 1.00, 0.00);//up


	glPushMatrix();
	//rotate and then translate the quad 
	//glTranslatef(0.0, -100.0, 0.0);
	////try setting to -185.0 to see the back of the quad
	//glRotatef(-15.0, 0.0, 1.0, 0.0);

	glTranslatef(-150.0, -100.0, 100.0);
	glRotatef(-80, 1.0, 0.0, 0.0);
	drawTexturedQuad(IMAGE2);
	glPopMatrix();


	//new position after roating and translating
	glPushMatrix();
	//rotate the quad slightly
	glTranslatef(0.0, 30.0, -100.0);
	glRotatef(15.0, 0.0, 1.0, 0.0);
	glRotatef(5.0, 1.0, 0.0, 0.0);
	glRotatef(3.0, 0.0, 0.0, 1.0);
	drawTexturedQuad(IMAGE1);
	glPopMatrix();

	ball.draw();
	
	glPushMatrix();
	glTranslatef(0.0, 0.0, -400.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	//drawTexturedSurfaceNoTiling(IMAGE3);
	if (repeatOn)
	{
		drawTexturedSurface(IMAGE3);
	}
	else
	{
		drawTexturedSurfaceNoTiling(IMAGE3);
	}
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.0, 0.0, -350.0);
	//drawTexturedSurfaceNoTiling(IMAGE4);
	if (repeatWallOn)
	{
		drawTexturedSurface(IMAGE4);
	}
	else
	{
		drawTexturedSurfaceNoTiling(IMAGE4);
	}
	glPopMatrix();

	glutSwapBuffers();
}


// This function does any needed initialization on the rendering
// context.
void SetupRC()
{
	//textures

	GLuint texture;
	// allocate a texture name
	glGenTextures(1, &texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// photoshop is a good converter to targa (TGA)
	//the gltLoadTGA method is found in gltools.cpp and is orignally from the OpenGL SuperBible book
	//there are quite a few ways of loading images
	// Load textures in a for loop
	glGenTextures(TEXTURE_COUNT, textures);
	//this puts the texture into OpenGL texture memory
 //   glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); - not defined so probably need to update GLEW - not needed here so ignore
	for (int iLoop = 0; iLoop < TEXTURE_COUNT; iLoop++)
	{
		// Bind to next texture object
		glBindTexture(GL_TEXTURE_2D, textures[iLoop]);

		// Load texture data, set filter and wrap modes
		//note that gltLoadTGA is in the glm.cpp file and not a built-in openGL function
		pBytes0 = gltLoadTGA(textureFiles[iLoop], &iWidth, &iHeight,
			&iComponents, &eFormat);

		glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBytes0);

		//set up texture parameters

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		//try these too
	   // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
		// glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		free(pBytes0);
	}

	//enable textures
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_DEPTH_TEST);	// Hidden surface removal    
	glFrontFace(GL_CCW);// Counter clock-wise polygons face out
 //	glEnable(GL_CULL_FACE);		// Do not calculate inside

//    glCullFace(GL_FRONT_AND_BACK);

// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_POINT_SMOOTH);
	// Setup and enable light 0
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLightBright);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLightBright);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mKs);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0f);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, whiteLightBright);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, mKs);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 60.0f);
	//glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT2, GL_DIFFUSE, whiteLightBright);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos3);
	glLightfv(GL_LIGHT2, GL_SPECULAR, mKs);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 60.0f);
	//glEnable(GL_LIGHT2);

	// Enable colour tracking
	glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// All materials hereafter have full specular reflectivity
	// with a high shine
	glMaterialfv(GL_FRONT, GL_SPECULAR, mKs);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	// Black blue background clear colour
	glClearColor(0.0f, 0.0f, 0.03f, 1.0f);
}


void TimerFunc(int value)
{
	//move camera
	if (moveCamera)
	{
		cameraZ = cameraZ - 2;
		if (cameraZ > 300.0)
		{
			cameraY = cameraY + 0.3;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(25, TimerFunc, 1);
}

void ProcessMenu(int choice)
{

	switch (choice)
	{
	case 1:
		repeatOn = !repeatOn;
		break;
	case 2:
		repeatWallOn = !repeatWallOn;
		break;
	case 3:
		moveCamera = !moveCamera;
		if (!moveCamera)
		{
			cameraX = 0.0;
			cameraY = 100.0;
			cameraZ = 500.0;
		}
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
	GLfloat fAspect;

	// Prevent a divide by zero
	if (h == 0)
		h = 1;

	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	// Calculate aspect ratio of the window
	fAspect = (GLfloat)w / (GLfloat)h;

	// Set the perspective coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// field of view of 45 degrees, near and far planes 1.0 and 1000
	//that znear and zfar should typically have a ratio of 1000:1 to make sorting out z depth easier for the GPU
	gluPerspective(55.0f, fAspect, 1.0, 1000.0);

	// Modelview matrix reset
	glMatrixMode(GL_MODELVIEW);
}

// Object and other generic initialization to prevent clutter from SetupRC
void init()
{

}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);// a 16:9 ratio
	glutCreateWindow("Football Game");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(25, TimerFunc, 1);
	// Create the Menu (right click on window)
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Toggle repeated texture", 1);
	glutAddMenuEntry("Toggle repeated wall", 2);
	glutAddMenuEntry("Toggle camera movement", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	SetupRC();
	init();
	glutMainLoop();
	return 0;
}





