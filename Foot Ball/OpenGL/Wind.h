#ifndef _WIND_H
#define _WIND_H

#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include "Coordinates.h"

using namespace std;

class Wind
{
private:
	float speed;
	bool isIncreasing;
	float limit;
	float rateOfChange;

public:
	Wind(float limit, float rate, bool isInc);

	float getSpeed();
	void setLimit(float l);
	void setRateOfChange(float rate);

	void update();
	void reset();
};

Wind::Wind(float limit, float rate, bool isInc)
{
	speed = 0;
	this->limit = limit;
	rateOfChange = rate;
	isIncreasing = isInc;
}

float Wind::getSpeed()
{
	return speed;
}

void Wind::setLimit(float l)
{
	limit = l;
}

void Wind::setRateOfChange(float rate)
{
	rateOfChange = rate;
}

void Wind::update()
{
	if(isIncreasing)
		speed += sin(rateOfChange);
	else
		speed -= sin(rateOfChange);

	if(abs(speed) >= limit)
		isIncreasing = !isIncreasing;
}

void Wind::reset()
{
	speed = 0;

	if(rand() % 2)
		isIncreasing = !isIncreasing;
}

#endif