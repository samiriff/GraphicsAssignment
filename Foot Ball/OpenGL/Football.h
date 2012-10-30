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
	float x,y;
public:
	Football(float x, float y, float z);
	void draw(void);
	//To be filled

};
Football::Football(float x, float y, float z)
{

}
void Football::draw()
{
	glColor3f(1.0,1.0,0.0);
	glTranslatef(0,-1,0.0);
	glutWireSphere(0.4, 12, 12);
}
#endif