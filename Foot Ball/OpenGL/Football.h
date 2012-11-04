#ifndef _FOOTBALL_H
#define _FOOTBALL_H

#include <cmath>

#include "Coordinates.h"
#include "RotationAngle.h"
#include "Constants.h"

//This class keeps track of the Football's movements and detects collisions and controls the physics of the ball

class Football
{
private:
	Coordinates coordinates;
	RotationAngle rotation;
	bool isMoving;
	Coordinates velocity;
	RotationAngle angularVelocity;

	
	void moveBy(float distance, AxisType alongAxis);
	void rotateBy(float angle, AxisType aboutAxis);

public:
	Football(float x, float y, float z);
	void draw(void);
	void setInMotion(Coordinates v, RotationAngle omega);
	void stopMotion();


	void update();
	//To be filled

};

Football::Football(float x, float y, float z)
{
	coordinates.set(X_AXIS, x);
	coordinates.set(Y_AXIS, y);
	coordinates.set(Z_AXIS, z);

	isMoving = false;
}

void Football::setInMotion(Coordinates v, RotationAngle omega)
{
	isMoving = true;
	velocity = v;
	angularVelocity = omega;
}

void Football::stopMotion()
{
	isMoving = false;
}

void Football::moveBy(float distance, AxisType alongAxis)
{
	coordinates.set(alongAxis, coordinates.get(alongAxis) + distance);
}

void Football::rotateBy(float angle, AxisType aboutAxis)
{
	rotation.setTheta(aboutAxis, rotation.getTheta(aboutAxis) + angle);
}

void Football::update()
{
	static float alpha = 0.5;
	static bool alphaIncreasing = true;

	if(isMoving)
	{
		//moveBy(velocity.get(X_AXIS), X_AXIS);
		//moveBy(velocity.get(Y_AXIS), Y_AXIS);
		//moveBy(velocity.get(Z_AXIS), Z_AXIS);

		float alphaRadian = alpha / 180.0 * 3.1415;
		moveBy(sin(alphaRadian) / 10.0, Y_AXIS);
		moveBy(velocity.get(Z_AXIS), Z_AXIS);

		cout << alpha << "\t" << sin(alpha) << '\t';
		cout << coordinates.get(Y_AXIS) << endl;

		rotateBy(angularVelocity.getTheta(X_AXIS), X_AXIS);
		rotateBy(angularVelocity.getTheta(Y_AXIS), Y_AXIS);
		rotateBy(angularVelocity.getTheta(Z_AXIS), Z_AXIS);

		alpha = fmod(alpha + 1, 360);		
	}
}


void Football::draw()
{
	glColor3f(1.0,1.0,0.0);
	//glTranslatef(0,-1,0.0);
	glPushMatrix();
		glTranslatef(coordinates.get(X_AXIS), coordinates.get(Y_AXIS), coordinates.get(Z_AXIS));

		glRotatef(rotation.getTheta(X_AXIS), 1, 0, 0);
		glRotatef(rotation.getTheta(Y_AXIS), 0, 1, 0);
		glRotatef(rotation.getTheta(Z_AXIS), 0, 0, 1);


		glColor3f(1, 1, 1);
		glutSolidSphere(0.59, 12, 12);
		glColor3f(0, 0, 0);
		glutWireSphere(0.6, 12, 12);

	glPopMatrix();
}

#endif