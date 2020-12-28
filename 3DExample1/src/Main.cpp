//mac osx includes
//#include <iostream>
//#include <stdio.h>
//#include <OpenGL/gl.h>
//#include <OpenGL/glu.h>
//#include <OpenGL/glext.h>
//#include <GLUT/glut.h>

// OpenGL toolkit for PC
#include <freeglut_std.h>
#include <freeglut.h>
#include <iostream>
#include <math.h>
// (c) Philip Trwoga projection tutorial - week 11 -


//foward declare functions
void resetPerspectiveProjection();
void drawAngleWithScaledText(GLfloat scale);
void setOrthographicProjection();
void ChangeSize(int w, int h);
void RenderScene(void);
void TimerFunc(int value);


GLint Wwidth;
GLint Wheight;
GLfloat teapotRotation = 0.0;
//used for the framerate
GLint frame = 0, timeTot = 0, timebase = 0;
char frameRate[12];

//this function pops back to the last projection
void resetPerspectiveProjection()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}


//used for drawing text
void displayText(GLfloat x, GLfloat y, GLint r, GLint g, GLint b, const char* string, bool stroke)
{
	GLint j = strlen(string);

	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	for (GLint i = 0; i < j; i++)
	{
		if (stroke)
		{
			glutStrokeCharacter(GLUT_STROKE_ROMAN, string[i]);
		}
		else
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
		}

	}
}

char teapotRotationString[12];

void drawAngleWithScaledText(GLfloat scale)
{
	glPushMatrix();

	//draw the text offset from the box
	glTranslatef(500.0, 120.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	sprintf_s(teapotRotationString, "Angle:%3.0f", teapotRotation);

	//flip
	glRotatef(180.0, 1.0, 0.0, 0.0);
	glScalef(scale, scale, scale);
	//if stroke = true then use the tranlate above to move the text
	//if stroke = false then use the first two values of displayText

	displayText(500, 100, 0, 1, 0, teapotRotationString, true);
	glPopMatrix();
}

void drawFrameRate()
{
	//this draws the framerate on the screen - useful for testing animation
	frame++;
	timeTot = glutGet(GLUT_ELAPSED_TIME);
	if (timeTot - timebase > 1000)
	{
		sprintf_s(frameRate, "FPS: %4.2f", frame * 1000.0 / (timeTot - timebase));

		timebase = timeTot;
		frame = 0;
	}

	//set the text to white
	glColor3f(1.0f, 1.0f, 1.0f);

	//this stop the text being affected by the current tranformation by reseting it
	glLoadIdentity();
	displayText(30, 30, 1, 0, 0, frameRate, false);
}


//sets up the orthographics projection for 2D overlay
void setOrthographicProjection()
{
	// switch to projection mode
	glMatrixMode(GL_PROJECTION);
	// save the previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();
	// reset matrix
	glLoadIdentity();
	// set a 2D orthographic projection
	gluOrtho2D(0, Wwidth, 0, Wheight);
	// invert the y axis, down is positive
	glScalef(1, -1, 1);
	// mover the origin from the bottom left corner
	// to the upper left corner
	glTranslatef(0, -Wheight, 0);
	//set for drawing again
	glMatrixMode(GL_MODELVIEW);
}


void ChangeSize(int w, int h)
{
	GLfloat fAspect;
	Wwidth = w;
	Wheight = h;
	// Prevent a divide by zero
	if (h == 0)
		h = 1;
	//need this for changing projection

	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	// Calculate aspect ratio of the window
	fAspect = (GLfloat)w / (GLfloat)h;

	// Set the perspective coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// field of view of 45 degrees, near and far planes 1.0 and 625
	gluPerspective(60.0f, fAspect, 1.0, 1600.0);
	// Modelview matrix reset
	glMatrixMode(GL_MODELVIEW);
}



void RenderScene(void)
{
	// Clear the window with current clearing colour
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	// Save the matrix state and do the rotations
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.0, 0.0, -200.0);

	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	//draw a teapot
	glRotatef(teapotRotation, 0.0f, -1.0f, 0.0f);
	
	glPopMatrix();

	//draw the 2D overlay
	glPushMatrix();
	glLoadIdentity();
	setOrthographicProjection();
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(20.0, 40.0);
	glVertex2f(100.0, 40.0);
	glEnd();
	drawFrameRate();
	drawAngleWithScaledText(0.5f);
	glPopMatrix();
	resetPerspectiveProjection();
	glutSwapBuffers();
}


void TimerFunc(int value)
{
	glutTimerFunc(25, TimerFunc, 1);
	glutPostRedisplay();
	teapotRotation++;
	if (teapotRotation > 360.0f)
	{
		teapotRotation = 0.0f;
	}
	printf("teapot rotation is  %f \n", teapotRotation);

}


void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}



int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);// a 16:9 ratio
	glutCreateWindow("2D Overlay");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(25, TimerFunc, 1);
	init();
	glutMainLoop();
	return 0;
}
