#ifndef _FOOTBALL_H
#define _FOOTBALL_H

#include <cmath>
#include <iostream>
#include <GL/glut.h>
#include<Windows.h>
#include "Coordinates.h"
#include "RotationAngle.h"
#include "Constants.h"
#include "ScoreBoard.h"
#include "Wind.h"
#pragma comment(lib, "winmm.lib")

using namespace std;
//This class keeps track of the Football's movements and detects collisions and controls the physics of the ball

class Football
{
private:
	Coordinates coordinates;
	RotationAngle rotation;
	bool isMoving;

	Coordinates velocity;
	RotationAngle angularVelocity;

	float initialVelocity;
	float rateOfDecreaseOfVelocity;
	float projectionAngle;
	float rateOfDecreaseOfProjAngle;
	float rateOfChangeOfTime;

	ScoreBoard *scoreBoard;
	Wind *wind;
	
	void rotateBy(float angle, AxisType aboutAxis);

public:
	Football(float x, float y, float z, ScoreBoard *s);
	void draw(void);
	void setInMotion(RotationAngle omega, float v0, float dv, float alpha, float da, float dt);
	void stopMotion();

	void update();
	void reset();

	void moveBy(float distance, AxisType alongAxis);

};

Football::Football(float x, float y, float z, ScoreBoard *s)
{
	coordinates.set(X_AXIS, x);
	coordinates.set(Y_AXIS, y);
	coordinates.set(Z_AXIS, z);

	isMoving = false;
	scoreBoard = s;

	wind = new Wind(10, 0.02, true);
}

void Football::setInMotion(RotationAngle omega, float v0, float dv, float alpha, float da, float dt)
{
	isMoving = true;
	angularVelocity = omega;

	initialVelocity = v0;
	rateOfDecreaseOfVelocity = dv;
	projectionAngle = alpha;
	rateOfDecreaseOfProjAngle = da;
	rateOfChangeOfTime = dt;
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
	static Coordinates currentOrigin(coordinates);
	static float time = 0;
	
	if(initialVelocity < 0 || projectionAngle < 0)
		isMoving = false;

	if(isMoving && initialVelocity > 0)
	{
		if(coordinates.get(Y_AXIS) < 0)
		{
			initialVelocity -= 2;
			projectionAngle -= 4;
			currentOrigin.set(Z_AXIS, coordinates.get(Z_AXIS));
			cout << "Initial V = " << initialVelocity << "\tAlpha = " << projectionAngle << endl;
			cout << "Current Origin = " << currentOrigin << endl;
			time = 0;
			coordinates.set(Y_AXIS, 0);
		}

		if(coordinates.get(Z_AXIS) <= MAXIMUM_DEPTH)
		{
			isMoving = false;
			
			LPCWSTR str = TEXT("BOMB.WAV");
			PlaySound(str, NULL, SND_ASYNC);
			 str = TEXT("APPLAUSE.WAV");
			PlaySound(str, NULL, SND_ASYNC);

			//Check if ball is within the bounding box of goalpost
			if(coordinates.get(X_AXIS) <= 8.0 && coordinates.get(X_AXIS) >= -6.5)
				scoreBoard->setNumOfGoals(scoreBoard->getNumOfGoals() + 1);

			currentOrigin.set(X_AXIS, 0);
			currentOrigin.set(Y_AXIS, 0);
			currentOrigin.set(Z_AXIS, 0);

			time = 0;
			wind->reset();
			return;
		}

		float alphaRadian = projectionAngle / 180.0 * 3.1415;
		float verticalDisp = (initialVelocity * time * sin(alphaRadian) - 0.5 * 9.8 * time * time);
		float horizontalDisp = (initialVelocity * time * cos(alphaRadian));

		cout << "x = " << coordinates.get(X_AXIS) << "y = " << coordinates.get(Y_AXIS) << endl;;
		coordinates.set(X_AXIS, wind->getSpeed());
		coordinates.set(Y_AXIS, verticalDisp / 100.0);
		coordinates.set(Z_AXIS, currentOrigin.get(Z_AXIS) - horizontalDisp / 100.0);				

		rotateBy(angularVelocity.getTheta(X_AXIS), X_AXIS);
		rotateBy(angularVelocity.getTheta(Y_AXIS), Y_AXIS);
		rotateBy(angularVelocity.getTheta(Z_AXIS), Z_AXIS);

		time += 0.2;
		wind->update();

		//cout << "Time = " << time << endl;
	}
}

void Football::reset()
{
	coordinates.set(X_AXIS, 0);
	coordinates.set(Y_AXIS, 0);
	coordinates.set(Z_AXIS, 0);

	isMoving = false;
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