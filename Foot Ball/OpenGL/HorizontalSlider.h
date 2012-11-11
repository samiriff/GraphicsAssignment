#ifndef _HORIZONTAL_SLIDER_H
#define _HORIZONTAL_SLIDER_H

#include <sstream>
#include <string>
#include <iostream>
#include <GL/glut.h>
#include "Coordinates.h"
#include "RotationAngle.h"
#include "Constants.h"

using namespace std;

class HorizontalSlider
{
private:
	float initialVelocity;	
	int width;
	bool isMoving;
	bool isIncreasing;

	void drawStrokeString(float value);

public:
	HorizontalSlider(int width);

	void draw();
	void update();
	void setInMotion();
	void stopMotion();
	void toggleMotion();

	float getInitialVelocity();
};

HorizontalSlider::HorizontalSlider(int width)
{
	initialVelocity = 0;
	this->width = width;
	isMoving = false;
	isIncreasing = true;
}

void HorizontalSlider::setInMotion()
{
	isMoving = true;
}

void HorizontalSlider::stopMotion()
{
	isMoving = false;
}

void HorizontalSlider::toggleMotion()
{
	isMoving = !isMoving;
}

void HorizontalSlider::update()
{
	if(isMoving)
	{
		if(isIncreasing)
			initialVelocity += 1;
		else
			initialVelocity -= 1;

		if(initialVelocity >= MAXIMUM_VELOCITY)
			isIncreasing = false;
		else 
			if(initialVelocity < 0)
				isIncreasing = true;
	}
}

void HorizontalSlider::drawStrokeString(float value)
{
   stringstream ss;
   ss << value;
   string valueString = "v = " + ss.str();

   for(int i=0; i<valueString.length(); i++)
	   glutStrokeCharacter(GLUT_STROKE_ROMAN, valueString[i]);
}

void HorizontalSlider::draw()
{
	glColor3f(1.0,1.0,0.0);
	glPushMatrix();
	glTranslatef(initialVelocity / MAXIMUM_VELOCITY * 10 - 100, -50, -100);

		glColor3f(1, 1, 1);
		glutWireTeapot(3);
		glTranslatef(5, 0, 0);
		glScalef(0.05, 0.05, 0.05);

		drawStrokeString(initialVelocity);
		

	glPopMatrix();
}


float HorizontalSlider::getInitialVelocity()
{
	return initialVelocity;
}



#endif