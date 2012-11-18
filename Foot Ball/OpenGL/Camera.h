#ifndef _CAMERA_H
#define _CAMERA_H

#include <iostream>
#include "Coordinates.h"
#include "RotationAngle.h"
#include "Constants.h"
#include "FootBall_Field.h"

using namespace std;

//This class keeps track of the human player's point of view and display.

class Camera
{
private:
	Coordinates coordinates;
	RotationAngle rotation;
	float distanceFromCam;

	//Indices of stationery objects in the display list
	GLuint displayListIndex;
	GLuint sunDisplayListIndex;
	GLuint skyDisplayListIndex;
	GLuint groundDisplayListIndex;
	
public:
	Camera();
	Camera(Coordinates coord, RotationAngle angle);

	void translateAlong(AxisType axisType, float distance);
	void rotateAbout(AxisType axisType, float angle);

	void moveForward();
	void moveBackward();
	void slideLeft();
	void slideRight();

	void glRotate(AxisType axisType);
	void glTranslateScreenToCamera();

	void initPrimitive();						//Goalkeeper's Image
	void render(FootBallField footballField);
	void render();

	void reset();

	friend ostream& operator<<(ostream& out, Camera &camera);
};

Camera::Camera()
{
	Coordinates coord;
	coordinates = coord;

	RotationAngle angle;
	rotation = angle;

	distanceFromCam = 5;
}

Camera::Camera(Coordinates coord, RotationAngle angle)
{
	coordinates = coord;
	rotation = angle;

	distanceFromCam = 10;
}

void Camera::translateAlong(AxisType axisType, float distance)
{
	float newLoc = coordinates.get(axisType) + distance;
	coordinates.set(axisType, newLoc);
}

void Camera::rotateAbout(AxisType axisType, float angle)
{
	float theta = rotation.getTheta(axisType);
	theta += angle;

	if (theta > 360) 
		theta -= 360;

	rotation.setTheta(axisType, theta);
}

void Camera::moveForward()
{
	float thetaX = rotation.getThetaRadians(X_AXIS);
	float thetaY = rotation.getThetaRadians(Y_AXIS);
	
	translateAlong(X_AXIS, float(sin(thetaY)));
	translateAlong(Y_AXIS, -float(sin(thetaX)));
	translateAlong(Z_AXIS, -float(cos(thetaY)));
}

void Camera::moveBackward()
{
	float thetaX = rotation.getThetaRadians(X_AXIS);
	float thetaY = rotation.getThetaRadians(Y_AXIS);
	
	translateAlong(X_AXIS, -float(sin(thetaY)));
	translateAlong(Y_AXIS, float(sin(thetaX)));
	translateAlong(Z_AXIS, float(cos(thetaY)));
}

void Camera::slideLeft()
{
	float thetaY = rotation.getThetaRadians(Y_AXIS);
    
	translateAlong(X_AXIS, -float(cos(thetaY)) * 0.2);
	translateAlong(Z_AXIS, -float(sin(thetaY)) * 0.2);
}

void Camera::slideRight()
{
	float thetaY = rotation.getThetaRadians(Y_AXIS);
    
	translateAlong(X_AXIS, float(cos(thetaY)) * 0.2);
	translateAlong(Z_AXIS, float(sin(thetaY)) * 0.2);
}

void Camera::glRotate(AxisType axisType)
{
	switch(axisType)
	{
	case X_AXIS:
		glRotatef(rotation.getTheta(X_AXIS), 1.0, 0.0, 0.0);  
		break;
	case Y_AXIS:
		glRotatef(rotation.getTheta(Y_AXIS), 0.0, 1.0, 0.0);  
		break;
	case Z_AXIS:
		glRotatef(rotation.getTheta(Z_AXIS), 0.0, 0.0, 1.0);  
		break;
	}
}

void Camera::glTranslateScreenToCamera()
{
	glTranslated(-coordinates.get(X_AXIS), 0.0f, -coordinates.get(Z_AXIS));
}

void Camera::initPrimitive()
{
	glEnable(GL_DEPTH_TEST); //enable the depth testing
    //glEnable(GL_LIGHTING); //enable the lighting
    //glEnable(GL_LIGHT0); //enable LIGHT0, our Diffuse Light
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH); //set the shader to smooth shader
	

	//Creating a cube for testing
	displayListIndex = glGenLists(1); //set the cube list to Generate a List
	glNewList(displayListIndex,GL_COMPILE); //compile the new list
		glPushMatrix();
		glColor3f(0.5, 0.5, 0.5);
		glutSolidSphere(0.5, 20, 20); //draw the cube
		glPopMatrix();
    glEndList(); //end the list	
}

void Camera::render(FootBallField footballField)
{	
	footballField.drawStationeryObjects();			//Render the sun, sky and ground which appear to be stationery wrt the camera

	glTranslatef(0, 0, -distanceFromCam);
	glRotate(X_AXIS);
	glColor3f(1.0f, 0.0f, 0.0f);
	//glCallList(displayListIndex);

	glRotate(Y_AXIS);
	glTranslateScreenToCamera();    
}

void Camera::render()
{
	glTranslatef(0, 0, -distanceFromCam);
	glRotate(X_AXIS);
	glColor3f(1.0f, 0.0f, 0.0f);
	//glCallList(displayListIndex);

	glRotate(Y_AXIS);
	glTranslateScreenToCamera();    
}

void Camera::reset()
{
	Coordinates c;
	coordinates = c;
	RotationAngle r;
	rotation = r;
}

ostream & operator<<(ostream& out, Camera &camera)
{
    cout << "Coordinates = " << camera.coordinates << "\tAngle = " << camera.rotation;
    return out;
}

#endif