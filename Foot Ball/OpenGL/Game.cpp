#include <cstdlib>
#include <iostream>

#include <GL/glut.h>

#include "Camera.h"

using namespace std;

Camera camera;				


//The following is only for testing purposes.
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

//draw the cube
void cube (void) 
{
	static float angle = 0;

    for (int i = -1; i < 10; i++)
    {
		glPushMatrix();		
			glTranslated(-cubesCoordinates[i+1].get(X_AXIS), 0, -cubesCoordinates[i+1].get(Z_AXIS)); //translate the cube
			glRotatef(angle, 1, 0, 0);
			glutSolidCube(2); //draw the cube
		glPopMatrix();
    }

	angle += 1;
}

void init (void) 
{
	camera.initPrimitive();
    cubepositions();
}








void enable (void) 
{
    glEnable(GL_DEPTH_TEST); //enable the depth testing
    glEnable(GL_LIGHTING); //enable the lighting
    glEnable(GL_LIGHT0); //enable LIGHT0, our Diffuse Light
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH); //set the shader to smooth shader
}

void display (void) {
    glClearColor (0.0,0.0,0.0,1.0); 
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    enable();
    
    glLoadIdentity();    
	camera.render();

    glColor3f(1.0f, 1.0f, 1.0f);
    cube(); 

    glutSwapBuffers(); //swap the buffers
}

void reshape (int w, int h) 
{
    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications

    glMatrixMode (GL_PROJECTION); //set the matrix to projection
    glLoadIdentity ();
    gluPerspective (90, (GLfloat)w / (GLfloat)h, 0.1, 100.0); //set the perspective (angle of sight, width, height, , depth)
	//gluLookAt(0,0,5,0,0,0,0,1,0);
    glMatrixMode (GL_MODELVIEW); //set the matrix back to model
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
	case 27:
    	exit(0);
	}
}

void tester()
{
	Coordinates coord(2.3, 1.2, 4.3);
	cout << coord;

	RotationAngle angle(0, 1.2, 4.6);
	cout << angle;

	camera = Camera(coord, angle);
	camera.rotateAbout(X_AXIS, 2);
	camera.moveForward();
	camera.rotateAbout(Y_AXIS, 2.44);
	camera.slideLeft();
	cout << endl << camera;
}


int main(int argc, char **argv)
{
	glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("A basic OpenGL Window");
    init();

    glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);

	glutKeyboardFunc (keyboard);
	//tester();		
    
    glutMainLoop ();

}