#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include "stdafx.h"
#include <GL/glut.h>
#include "Camera.h"
#include "FootBall_Field.h"
#include "ScoreBoard.h"
#include "GraphicString.h"
using namespace std;

#define FULL_SCREEN 1

Camera camera;				
FootBallField fbField;

bool isIntro = true;
GraphicString *graphicString;


//The following is only for testing purposes.

// ---------------------------------CUBES ONLY FOR TESTING...REMOVE LATER ---------------------------------------------
//Positions of the cubes
Coordinates cubesCoordinates[10];

//set the positions of the cubes
void cubepositions (void) 
{ 
    for (int i=0;i<10;i++)
    {
		cubesCoordinates[i].set(X_AXIS, (rand() % 5 + 1) * 10);
		cubesCoordinates[i].set(Z_AXIS, (rand() % 5 + 1) * 10);
    }
}

void init (void) 
{
	camera.initPrimitive();
    cubepositions();

	string pool = "Code Kshetra Inc. \nPresents\nA game that you've never played before\n\
		and one that you may never play again\nSay Hello to\nTHE FOOTBALL GAME\nPress 'o' to continue...\
		\nDeveloped by Samir, Satvik and Vaishakh";
	graphicString = new GraphicString(pool);	
	Coordinates c(-100, 0, 0);
	graphicString->append(c);
}


//draw the cube
void cube (void) 
{
	static float angle = 0;

	for (int i = -1; i < 10; i++)
    {
		glPushMatrix();		
			glTranslated(-cubesCoordinates[i+1].get(X_AXIS) - 4, 10, -cubesCoordinates[i+1].get(Z_AXIS)); //translate the cube
			glRotatef(angle, 1, 0, 0);
			glutSolidCube(2); //draw the cube
		glPopMatrix();
    }
	
	angle += 1;
}

//------------------------------------------END OF CODE FOR TESTING CUBES...REMOVE LATER ------------------------------------







//------------------------------------------ACTUAL CODE-----------------------------------------------------------------------

void enable (void) 
{
    glEnable(GL_DEPTH_TEST); //enable the depth testing
    glEnable(GL_LIGHTING); //enable the lighting
	glEnable(GL_LIGHT0); //enable LIGHT0, our Diffuse Light
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH); //set the shader to smooth shader
}

void displayIntro()
{	
	static Coordinates coordinates;

	camera.render();
	glPushMatrix();
		glTranslatef(-25, 25, -75);
		glTranslatef(coordinates.get(X_AXIS), coordinates.get(Y_AXIS), coordinates.get(Z_AXIS));
		glScalef(0.05, 0.05, 0.05);
		graphicString->draw();
	glPopMatrix();

	static float toAppend = 0;
	if(toAppend >= 10)
	{
		graphicString->append();
		toAppend = 0;
	}
	toAppend += 1;

	static float projectionAngle = 100.0;

	float alphaRadian = projectionAngle / 180.0 * 3.1415;		
	float verticalDisp = 75 * sin(alphaRadian);
	float horizontalDisp = cos(alphaRadian);
	projectionAngle += 6;

	coordinates.set(Y_AXIS, verticalDisp / 10.0);	
	coordinates.set(X_AXIS, horizontalDisp);					
}

void display (void) 
{
    glClearColor (1.0,1.0,1.0,0.0); 
	glClearColor (0.0,0.0,0.0,0.0); 
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
	//enable();

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);

	if(isIntro)
	{
		displayIntro();	
		/*if(graphicString->isPoolNewLine())
			camera.reset();
		camera.slideRight();
		camera.slideRight();
		camera.slideRight();
		camera.rotateAbout(X_AXIS, 0.05);
		camera.rotateAbout(Y_AXIS, -0.05);*/
	}
	else
	{
		camera.render(fbField);
		fbField.drawMovingObjects();
		
		glColor3f(1, 1, 1);
		cube();
	}

	

	glutSwapBuffers(); // Flush the OpenGL buffers to the window 

	fbField.update();
}

void reshape (int width, int height) 
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window  
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed  
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)  
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 0.1, 1000.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes  
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly  

}

void createFootballTrajectory()
{
	RotationAngle footballAngularVelocity(-5, -2, -1);

	fbField.getVelocitySlider()->stopMotion();
	fbField.getAngleSlider()->stopMotion();
	fbField.getFootball()->setInMotion(footballAngularVelocity, fbField.getVelocitySlider()->getInitialVelocity(), 2, fbField.getAngleSlider()->getInitialAngle(), 3, 0.1);

}

void keyboard (unsigned char key, int x, int y) 
{	
	switch(key)
	{
	case 'q':
		camera.rotateAbout(X_AXIS, 1);
		break;
	case 'z':
		camera.rotateAbout(X_AXIS, -1);
		break;
	case 'j':
		camera.rotateAbout(Y_AXIS, 1);
		break;
	case 'l':
		camera.rotateAbout(Y_AXIS, -1);
		break;
	case 'w':
    	camera.moveForward();    
		break;
	case 's':
		camera.moveBackward();
		break;
	case 'd':
		camera.slideRight();
		break;
	case 'a':
    	camera.slideLeft();
		break;
	case ' ':		
		createFootballTrajectory();
		break;
	case ',':
		fbField.getVelocitySlider()->toggleMotion();
		break;
	case '.':
		fbField.getAngleSlider()->toggleMotion();
		break;
	case 'r':
		fbField.getFootball()->reset();
		break;
	case 'o':
		isIntro = false;
		camera.reset();
		break;
	case 27:
    	exit(0);
	}
}

int main(int argc, char **argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);

	if(FULL_SCREEN)
	{
		glutGameModeString("1920x1080:32@75"); //the settings for fullscreen mode
		glutEnterGameMode(); //set glut to fullscreen using the settings in the line above
	}
	else
	{
		glutInitWindowSize (500, 500);
		glutInitWindowPosition (100, 100);
		glutCreateWindow ("Jinkchak Football Game");
	}


	init();

    glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
    glutMainLoop ();

}