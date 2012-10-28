#ifndef _FOOTBALL_H
#define _FOOTBALL_H

#include "Coordinates.h"
#include "RotationAngle.h"
#include "Constants.h"

//This class keeps track of the Football's movements and detects collisions and controls the physics of the ball

class Football
{
private:
	Coordinates coordinates;
	RotationAngle rotation;

public:
	Football(float x, float y, float z);

	//To be filled

};

#endif