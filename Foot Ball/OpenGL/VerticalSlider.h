#ifndef _VERTICAL_SLIDER_H
#define _VERTICAL_SLIDER_H

#include <sstream>
#include <string>
#include <iostream>
#include <GL/glut.h>
#include "Coordinates.h"
#include "RotationAngle.h"
#include "Constants.h"

using namespace std;

class VerticalSlider
{
private:
	float initialAngle;	
	bool isMoving;
	bool isIncreasing;

	void drawStrokeString(float value);

public:
	VerticalSlider();

	void draw();
	void update();
	void setInMotion();
	void stopMotion();
	void toggleMotion();

	float getInitialAngle();
};

VerticalSlider::VerticalSlider()
{
	initialAngle = 0;
	isMoving = false;
	isIncreasing = true;
}

void VerticalSlider::setInMotion()
{
	isMoving = true;
}

void VerticalSlider::stopMotion()
{
	isMoving = false;
}

void VerticalSlider::toggleMotion()
{
	isMoving = !isMoving;
}

void VerticalSlider::update()
{
	if(isMoving)
	{
		if(isIncreasing)
			initialAngle += 1;
		else
			initialAngle -= 1;

		if(initialAngle >= MAXIMUM_ANGLE)
			isIncreasing = false;
		else 
			if(initialAngle < 0)
				isIncreasing = true;
	}
}

void VerticalSlider::drawStrokeString(float value)
{
   stringstream ss;
   ss << value;
   string valueString = "a = " + ss.str();

   for(int i=0; i<valueString.length(); i++)
	   glutStrokeCharacter(GLUT_STROKE_ROMAN, valueString[i]);
}

void VerticalSlider::draw()
{
	glColor3f(1.0,1.0,0.0);
	glPushMatrix();
		glTranslatef(0, 50, 0);
		glTranslatef(-100, initialAngle / MAXIMUM_ANGLE * 10 - 100, -100);

		glColor3f(1, 1, 0);
		glutWireTeapot(3);
		glTranslatef(5, 0, 0);
		glScalef(0.05, 0.05, 0.05);

		drawStrokeString(initialAngle);
		

	glPopMatrix();
}


float VerticalSlider::getInitialAngle()
{
	return initialAngle;
}



#endif