//Windows includes - DO NOT EDIT AS LOTS OF INTERDEPENDENCE


#include <math.h>						
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>	//Needed for console output (debugging)
#include <gl/freeglut.h>
#include <iostream>
#include <string>

#include "Vector3.h"

#include "Football.h"
#include "GUI.h"
#include "Target.h"
#include "TexturedPlane.h"
#include "Wall.h"

#ifdef WIN32
#include "gltools.h"
#include <windows.h>		// Must have for Windows platform builds
#include <gl\gl.h>			// Microsoft OpenGL headers (version 1.1 by themselves)
#include <gl\glu.h>			// OpenGL Utilities
#include "glm.h"
#endif
//note that this needs gltools.h and gltools.cpp to be included in the shared/library directory

//can define any number of textures here - we just have 2 images
//these are just integers so you can use them as such
#define GRASS_TEX      2
#define WALL_TEX      3
#define WALL_OLD_TEX      4
#define FLOWER_ORANGE_TEX      5
#define FLOWER_PALM_TEX      6
#define FLOWER_YELLOW_TEX      7
#define BALL_TEX 8    //football map
#define SKY_TEX 9
#define TARGET_BLUE_TEX 10
#define TARGET_RED_TEX 11
#define TARGET_GREEN_TEX 12
#define TARGET_DULL_TEX 13
#define GUI_HORIZONTAL 14
#define GUI_VERTICAL 15


#define TEXTURE_COUNT 14
GLuint  textures[TEXTURE_COUNT];

//Game Constants
#define NUMBER_OF_WALLS 3
#define MAX_VELOCITY 4.0f
#define SPIN_MULTIPLIER 3.0f
#define NUM_ATTEMPTS 14;
#define BOUNDARY 250
#define SB_SIZE 500.0f
#define SB_ROTATION 0.01f

const Vector3 vertBarPos = { 100, 600, 0 };
const Vector3 horzBarPos = { 200, 625, 0 };


// Global object initialization
Football ball = Football(BALL_TEX, 5);
TexturedPlane lawn = TexturedPlane(GRASS_TEX);

TexturedPlane flower = TexturedPlane(FLOWER_ORANGE_TEX);
TexturedPlane flower2 = TexturedPlane(FLOWER_YELLOW_TEX);
TexturedPlane flower3 = TexturedPlane(FLOWER_YELLOW_TEX);

TexturedPlane fern1 = TexturedPlane(FLOWER_PALM_TEX);
TexturedPlane fern2 = TexturedPlane(FLOWER_PALM_TEX);
TexturedPlane fern3 = TexturedPlane(FLOWER_PALM_TEX);
TexturedPlane fern4 = TexturedPlane(FLOWER_PALM_TEX);

TexturedPlane fern5 = TexturedPlane(FLOWER_PALM_TEX);
TexturedPlane fern6 = TexturedPlane(FLOWER_PALM_TEX);
TexturedPlane fern7 = TexturedPlane(FLOWER_PALM_TEX);
TexturedPlane fern8 = TexturedPlane(FLOWER_PALM_TEX);


Target target20_1 = Target(TARGET_BLUE_TEX, 20, 7.5);
Target target20_2 = Target(TARGET_BLUE_TEX, 20, 7.5);
Target target20_3 = Target(TARGET_BLUE_TEX, 20, 7.5);
Target target10_1 = Target(TARGET_GREEN_TEX, 10, 10);
Target target10_2 = Target(TARGET_GREEN_TEX, 10, 10);
Target target10_3 = Target(TARGET_GREEN_TEX, 10, 10);
Target target30_1 = Target(TARGET_RED_TEX, 30, 5);
Target target30_2 = Target(TARGET_RED_TEX, 30, 5);
Target target30_3 = Target(TARGET_RED_TEX, 30, 5);

Wall wall1 = Wall(WALL_TEX);
Wall wall2 = Wall(WALL_TEX);
Wall wall3 = Wall(WALL_TEX);
GUI horzBar = GUI(GUI_HORIZONTAL);
GUI vertBar = GUI(GUI_VERTICAL);

Target* targets[9] = {&target20_1, &target20_2, &target20_3,  &target10_1, &target10_2, &target10_3, &target30_1, &target30_2, &target30_3 };
TexturedPlane* leftFerns[4] = { &fern1, &fern2, &fern3, &fern4 };
TexturedPlane* rightFerns[4] = { &fern5, &fern6, &fern7, &fern8 };


float Wwidth;
float Wheight;

float skyboxAngle = 0;

GLfloat fAspect;

Vector3 kickVelocity = { 0,0,5 };
Vector3 gravity = { 0, -0.11, 0 };
Vector3 ballVelocity;
bool isShooting;

void* font = GLUT_BITMAP_9_BY_15;

int score;
int attempts;

//below is simply a character array to hold the file names
//note that you may need to replace the below with the full directory root depending on where you put your image files
//if you put them where the exe is then you just need the name as below - THESE IMAGES  ARE IN THE DEBUG FOLDER, YOU CAN ADD ANY NEW ONES THERE 
const char* textureFiles[TEXTURE_COUNT] = { "grass_diff.tga", "brick_texture_lo_res.tga","old_wall_texture_TGA.tga","orangeFlowerFinal5.tga",
	"palmBranchA.tga", "yellowFlowerFinal.tga","FootballCompleteMap.tga", "stormydays_large.tga", "targetBlue.tga", "targetRed.tga","targetGreen.tga", "targetDull.tga", "fillBarHorizontal.tga", "fillBarVerticalR.tga"  };


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
GLfloat  orangeLight[] = { 1.0f, 0.9f, 0.85f, 1.0f };


//we need these for the texture loader
//they are to do with the image format and size
GLint iWidth, iHeight, iComponents;
GLenum eFormat;
// this is a pointer to memory where the image bytes will be held 
GLbyte* pBytes0;

void DisplayText(GLfloat x, GLfloat y, std::string message, int num)
{

	glDisable(GL_TEXTURE_2D); //added this
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, Wwidth, 0.0, Wheight);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(10, 10);
	std::string output = message + std::to_string(num); // Score converted to string
	glPushMatrix();
	if (num < 0) { glColor3f(1.0, 0.0, 0.0); } // Red
	else { glColor3f(0.0, 0.0, 0.0); } // Green
	glRasterPos2i(x, y); // changes the raster position for the text to a specified point.

	for (std::string::iterator i = output.begin(); i != output.end(); ++i) // Iterator for message.
	{
		char c = *i;
		glutBitmapCharacter(font, c);
	}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

//camera
GLfloat cameraX = 0.0;
GLfloat cameraY = 150.0;
GLfloat cameraZ = -20.0;

bool repeatOn = false;
bool repeatWallOn = false;
bool moveCamera = false;

// here we declare an array of vertices for the cube
GLfloat cubeVertexData[108] =
{
	//object vertex coordinates for cube made from triangles
	// Data layout for each line below is:
	// positionX, positionY, positionZ
	//wind counter-clockwise

	SB_SIZE, -SB_SIZE, -SB_SIZE,
	SB_SIZE, SB_SIZE, -SB_SIZE,
	SB_SIZE, -SB_SIZE, SB_SIZE,
	SB_SIZE, -SB_SIZE, SB_SIZE,
	SB_SIZE, SB_SIZE, -SB_SIZE,
	SB_SIZE, SB_SIZE, SB_SIZE,

	SB_SIZE, SB_SIZE, -SB_SIZE,
	-SB_SIZE, SB_SIZE, -SB_SIZE,
	SB_SIZE, SB_SIZE, SB_SIZE,
	SB_SIZE, SB_SIZE, SB_SIZE,
	-SB_SIZE, SB_SIZE, -SB_SIZE,
	-SB_SIZE, SB_SIZE, SB_SIZE,

	-SB_SIZE, SB_SIZE, -SB_SIZE,
	-SB_SIZE, -SB_SIZE, -SB_SIZE,
	-SB_SIZE, SB_SIZE, SB_SIZE,
	-SB_SIZE, SB_SIZE, SB_SIZE,
	-SB_SIZE, -SB_SIZE, -SB_SIZE,
	-SB_SIZE, -SB_SIZE, SB_SIZE,
	//4
	-SB_SIZE, -SB_SIZE, -SB_SIZE,
	SB_SIZE, -SB_SIZE, -SB_SIZE,
	-SB_SIZE, -SB_SIZE, SB_SIZE,
	-SB_SIZE, -SB_SIZE, SB_SIZE,
	SB_SIZE, -SB_SIZE, -SB_SIZE,
	SB_SIZE, -SB_SIZE, SB_SIZE,
	//5
	SB_SIZE, SB_SIZE, SB_SIZE,
	-SB_SIZE, SB_SIZE, SB_SIZE,
	SB_SIZE, -SB_SIZE, SB_SIZE,
	SB_SIZE, -SB_SIZE, SB_SIZE,
	-SB_SIZE, SB_SIZE, SB_SIZE,
	-SB_SIZE, -SB_SIZE, SB_SIZE,
	//6
	SB_SIZE, -SB_SIZE, -SB_SIZE,
	-SB_SIZE, -SB_SIZE, -SB_SIZE,
	SB_SIZE, SB_SIZE, -SB_SIZE,
	SB_SIZE, SB_SIZE, -SB_SIZE,
	-SB_SIZE, -SB_SIZE, -SB_SIZE,
	-SB_SIZE, SB_SIZE, -SB_SIZE

};

//the texture coordinates - work will skybox texture of this shape +--

GLfloat textureCoordsSkyBox[72] = {
	//face 1
	0.75,0.33,      //    0,1,
	0.75,0.67,     //    1,1,
	0.5,0.33,     //    0,0,
	0.5,0.33,     //    0,0,
	0.75,0.67,    //    1,0,
	0.5,0.67,   //    1,1,

	//face 2
	0.5,1.0, //    1,1,
	0.25,1, //    0,1,
	0.5,0.67, //    1,0,
	0.5,0.67, //    1,0,
	0.25,1.0, //    0,1,
	0.25,0.67, //    1,1,
	//face 3
	0,0.67,//    1,1,
	0,0.33,//    0,1,
	0.25,0.67,//    1,0,
	0.25,0.67,//    1,0,
	0,0.33,//    0,1,
	0.25,0.33,//    0,0,
	//face 4
	0.25,0.0,//    0,1,
	0.5,0.0,//    1,1,
	0.25,0.33,//    0,0,
	0.25,0.33,//    0,0,
	0.5,0.0,//    1,1,
	0.5,0.33,//    0,0,
	//face 5
	0.5,0.67,//    1,0,
	0.25,0.67,//    0,0,
	0.5,0.33,//    1,1,
	0.5,0.33,//    1,1,
	0.25,0.67,//    0,0,
	0.25,0.33,//    0,1,
	//face 6
	0.75,0.33,//    1,1,
	1.0,0.33,//    0,1,
	0.75,0.67,//    1,0,
	0.75,0.67,//    1,0,
	1.0,0.33,//    0,1,
	1.0,0.67//    0,0


};

//the lighting normals - all facing out from each face
GLfloat gCubeVertexdataNormals[108] =
{
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,

	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,

	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,

	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,

	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f

};

// Scene setup.
void scene()
{
	ball.transform.position = {0, 5, 0};
	lawn.transform.position = Vector3(0, 0, 30);
	lawn.scale(3);
	
	flower.transform.position = Vector3(0, 9, 172);
	flower2.transform.position = Vector3(60, 9, 172);
	flower3.transform.position = Vector3(-60,9,172);
	
	flower.scale(2);
	flower2.scale(2);
	flower3.scale(1.8);

	for (TexturedPlane* fern: leftFerns)
	{		
		(*fern).transform.position = { 75, 9, 25 };
		(*fern).transform.rotation = { 0,90,0 };
		(*fern).scale(2);
	}

	for (TexturedPlane* fern : rightFerns)
	{
		(*fern).transform.position = {-75, 9, 25 };
		(*fern).transform.rotation = {0,90,0};
		(*fern).scale(2);
	}

	fern2.transform.position.z = fern1.transform.position.z + 40;
	fern3.transform.position.z = fern2.transform.position.z + 40;
	fern4.transform.position.z = fern3.transform.position.z + 40;

	fern6.transform.position.z = fern5.transform.position.z + 40;
	fern7.transform.position.z = fern6.transform.position.z + 40;
	fern8.transform.position.z = fern7.transform.position.z + 40;
	
	
	wall1.transform.position = Vector3(-80, 17, 80);
	wall1.transform.rotation.y = 90;
	wall1.transform.scale.x *= 4;

	wall2.transform.position = Vector3(0, 16.9, 177);
	wall2.transform.rotation.y = 180;
	wall2.transform.scale.x *= 3.2;

	wall3.transform.position = Vector3(80, 17, 80);
	wall3.transform.rotation.y = 270;
	wall3.transform.scale.x *= 4;
	
	lawn.transform.scale.x *= 15;
	lawn.transform.scale.y *= 20;
	lawn.transform.rotation.x = 90;
	
	
	
	for (Target* target : targets)
	{
		(*target).transform.position.z = 173;
		(*target).transform.rotation.y = 180;
	}
	
	target20_1.transform.position.y = 25;

	target20_2.transform.position.y = 12;
	target20_2.transform.position.x = 40;

	target20_3.transform.position.y = 32;
	target20_3.transform.position.x = -40;

	target10_1.transform.position.y = 12;
	target10_1.transform.position.x = -45;

	target10_2.transform.position.y = 18;
	target10_2.transform.position.x = -22;

	target10_3.transform.position.y = 22;
	target10_3.transform.position.x = 22;

	target30_1.transform.position.y = 29;
	target30_1.transform.position.x = 42;

	target30_2.transform.position.y = 33;
	target30_2.transform.position.x = -13;

	target30_3.transform.position.y = 20;
	target30_3.transform.position.x = 60;
	
	
	horzBar.transform.position = horzBarPos;
	horzBar.transform.scale.y /= 4;

	vertBar.transform.position = vertBarPos;
	vertBar.transform.scale.y /= 4;

	vertBar.transform.rotation.z = 90;

	score = 0;
	ballVelocity = kickVelocity;
	attempts = NUM_ATTEMPTS
	
}

/* how to use - put below inside your drawSkyBox function
 - remember to apply the texture also and apply it to the inside by using a CW winding */
void drawSkyBox()
{
	glFrontFace(GL_CCW);
	glEnable(GL_TEXTURE_2D);
	//    glFrontFace(GL_CW); //texture the inside
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, SKY_TEX);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, gCubeVertexdataNormals);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, cubeVertexData);
	//   glTexCoordPointer(2, GL_FLOAT, 0, textureCoords);
	glTexCoordPointer(2, GL_FLOAT, 0, textureCoordsSkyBox);
	// draw a cube - type - start number - number of vertices to draw (so 3 for single triangle)
	glDrawArrays(GL_TRIANGLES, 0, 36);
	// deactivate vertex arrays after drawing
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void resetBall()
{
	isShooting = false;
	ball.transform.position = { 0, 5, 0 };
	ball.transform.rotation = { 0,0,0 };
	ballVelocity = kickVelocity;
}


void ChangeSize(int w, int h)
{
	Wwidth = w;
	Wheight = h;
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
	gluPerspective(45.0f, fAspect, 1.0, 1000.0);

	// Modelview matrix reset
	glMatrixMode(GL_MODELVIEW);
}

void resetGame() // Resets the ball and every target. Also sets score back to zero and attempts back to maximum. Resets the Velocity to keep it consistent.
{
	
	for(Target* target: targets)
	{
		(*target).reset();
	}
	score = 0;
	attempts = NUM_ATTEMPTS
	kickVelocity.x = 0;
	kickVelocity.y = 0;
	ballVelocity = kickVelocity;
	resetBall();
}

void checkWin() // Checks if all targets are hit, if yes, resets the game.
{
	bool win = true;
	for(Target* target: targets)
	{
		win = (win && (*target).isHit());
	}
	if (win) { resetGame(); }
}

// Called to draw scene
void RenderScene(void)
{	
	// Clear the window with current clearing colour
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, fAspect, 1.0, 1000.0); // Dumb hacky way to reset the perspective after rendering GUI (Dumb hack was to make fAspect global)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	if (moveCamera) // If bool is true, follows the ball, otherwise, sits at a predetermined position.
	{
		// view the scene
		gluLookAt(ball.transform.position.x + cameraX, ball.transform.position.y + cameraY, ball.transform.position.z + cameraZ,//eye
			ball.transform.position.x, ball.transform.position.y, ball.transform.position.z+50,//centre
			0.00, 1.00, 0.00);//up
	}
	else // Hardcoded, could be improved.
	{
		gluLookAt(0.00, 20.00, -40.00,
			0.00, 15.00, 0.00,
			0.00, 1.00, 0.00);
	}
	// Skybox rotation and rendering handling.
	glPushMatrix();
	glRotatef(skyboxAngle+=SB_ROTATION, 0.0, 1.0, 0.0 );
	drawSkyBox();
	glPopMatrix();
	
	lawn.draw();
	wall1.draw();
	wall2.draw();
	wall3.draw();
	ball.draw();
	target20_1.draw();
	target20_2.draw();
	target20_3.draw();
	target10_1.draw();
	target10_2.draw();
	target10_3.draw();
	target30_1.draw();
	target30_2.draw();
	target30_3.draw();
	
	flower.draw();
	flower2.draw();
	flower3.draw();
	
	fern1.draw();
	fern2.draw();
	fern3.draw();
	fern4.draw();
	fern5.draw();
	fern6.draw();
	fern7.draw();
	fern8.draw();
	
	if(isShooting) // If the ball is currently shooting, sets the position vector of the ball to be the sum of position and velocity.
	{
		ballVelocity = ballVelocity + gravity;
		ball.transform.position = ball.transform.position + ballVelocity;
		ball.transform.rotation.x += ballVelocity.z * SPIN_MULTIPLIER;

		for (Target* target : targets) // Checks collision for targets first, if true, adds score.
		{
			if(ball.checkPlaneCollision(*target) && !(*target).isHit())
			{
				(*target).hit(TARGET_DULL_TEX);
				score += (*target).getScore();
				resetBall();
				attempts--;
			}
		}
		if (ball.checkPlaneCollision(wall1) || ball.checkPlaneCollision(wall2) || ball.checkPlaneCollision(wall3)) // Checks collision for wall boundaries, if colliding, removes attempt and resets ball.
		{
			resetBall();
			attempts--;
		}
		for(int i = 0; i < 3; i++)
		{
			if (abs(ball.transform.position[i]) > BOUNDARY || ball.transform.position.y <= 0 + ball.transform.scale.y/2) // if any of the ball's axes are outside of the boundary limit, resets the ball.
			{
				resetBall();
				attempts--;
			}
		}
		
	}
	checkWin();
	if (attempts <= 0) { resetGame(); }
	

	horzBar.value = kickVelocity.x / MAX_VELOCITY/2;
	vertBar.value = kickVelocity.y / MAX_VELOCITY - 0.5;
	horzBar.draw(Wwidth, Wheight);
	vertBar.draw(Wwidth, Wheight);
	DisplayText(240, Wheight-20, "Score: ", score);
	DisplayText(100, Wheight - 20, "Attempts: ", attempts);

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
	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLightBright); // Spotlight
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mKs);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0f);
	glEnable(GL_LIGHT0);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, orangeLight); // Ambient light
	glLightfv(GL_LIGHT2, GL_DIFFUSE, orangeLight);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos3);
	glLightfv(GL_LIGHT2, GL_SPECULAR, mKa);
	glLightf(GL_LIGHT2, GL_AMBIENT, 200.0f);
	glEnable(GL_LIGHT2);

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
	glutPostRedisplay();
	glutTimerFunc(25, TimerFunc, 1);
}

void specialKeyboard(int key, int x, int y) // Keyboard actions
{
	if (!isShooting) // If not shooting, stops player from cheating after the ball has been shot.
	{
		switch (key)
		{

		case GLUT_KEY_UP:
			if (kickVelocity.y < MAX_VELOCITY) { kickVelocity.y += 0.1; } // Adds velocity to axis-assigned buttton.
			break;
		case GLUT_KEY_DOWN:
			if (kickVelocity.y > 0) { kickVelocity.y -= 0.1; }
			else { kickVelocity.y = 0; }
			break;
		case GLUT_KEY_RIGHT:
			if (kickVelocity.x > -MAX_VELOCITY) { kickVelocity.x -= 0.1; }
			break;
		case GLUT_KEY_LEFT:
			if (kickVelocity.x < MAX_VELOCITY) { kickVelocity.x += 0.1; }
			break;
		}
	}
}

void keyboard(unsigned char key, int x, int y) // Keyboard actions
{
	switch (key)
	{
	case ' ': // space and z shoot
	case 'z':
		isShooting = true;
		ballVelocity = kickVelocity;
		break;
	case 'r': // r to manually reset the game.
		resetGame();
		break;
	case 'f': //f to follow ball with cam.
		moveCamera = !moveCamera;
		break;
	}
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
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	SetupRC();
	scene();
	glutMainLoop();
	return 0;
}





