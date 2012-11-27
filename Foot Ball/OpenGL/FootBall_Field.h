#ifndef _FOOTBALL_FIELD_H
#define _FOOTBALL_FIELD_H

#include "Football.h"
#include "GoalKeeper.h"
#include "ScoreBoard.h"
#include "HorizontalSlider.h"
#include "VerticalSlider.h"

//This class keeps track of all the objects in the Game World, including the Football, and textures of the field, etc.

class FootBallField
{
private:
	Football * football;
	ScoreBoard *scoreBoard;
	HorizontalSlider *initialVelocitySlider;
	VerticalSlider *initialAngleSlider;
	
	//Indices of stationery objects in the display list
	GLuint sunDisplayListIndex;
	GLuint skyDisplayListIndex;
	GLuint groundDisplayListIndex;
	GLuint goalPostDisplayListIndex;

	//Methods for Stationery Objects with respect to the Camera
	void initGround(void);
	void initSky(void);
	void initSun(void);
	void drawGroundAndSky(void);
	void drawSun(void);	

	//Methods for Moving Objects with respect to the Camera	
	void initGoalPost(void);
	void drawGoalPost(void);
	void drawMarkings(void);	

public:
	FootBallField();
	void drawStationeryObjects(void);
	void drawMovingObjects();

	//Required to update relative motion of any object in the football field
	void update();

	Football *getFootball();
	HorizontalSlider *getVelocitySlider();
	VerticalSlider *getAngleSlider();

	~FootBallField();
};
FootBallField::FootBallField()
{
	this->scoreBoard = new ScoreBoard(2.0, 5.0);
	this->football = new Football(0, 0, 0, scoreBoard);	
	this->initialVelocitySlider = new HorizontalSlider(2);
	this->initialAngleSlider = new VerticalSlider();
	//this->goalkeeper = new GoalKeeper();

	sunDisplayListIndex = -1;
	skyDisplayListIndex = -1;
	groundDisplayListIndex= -1;
	goalPostDisplayListIndex = -1;
}
void FootBallField::drawStationeryObjects()
{
	drawSun();
	drawGroundAndSky();
	scoreBoard->draw();
	//scoreBoard->drawScore("SCORE: ", 100,100,100);

	//drawMarkings();
	//drawGoalPost();
	//goalPost.draw();
	//scoreBoard->draw();
	//goalKeeper.draw();

	initialVelocitySlider->draw();
	initialAngleSlider->draw();
}

void FootBallField::drawMovingObjects()
{
	football->draw();
	drawGoalPost();	
}

void FootBallField::update()
{
	football->update();
	initialVelocitySlider->update();
	initialAngleSlider->update();
}

Football *FootBallField::getFootball()
{
	return football;
}


HorizontalSlider *FootBallField::getVelocitySlider()
{
	return initialVelocitySlider;
}

VerticalSlider *FootBallField::getAngleSlider()
{
	return initialAngleSlider;
}


void FootBallField::drawMarkings(void)
{
	glColor3f(0,0,0);
	
	glBegin(GL_LINE_LOOP);
	glVertex3f(-1.5f, 0.0f, 0.0f);
	glVertex3f(1.5f, 0.0f, 0.0f); 
	glVertex3f(1.5f, -2.0f, 0.0f); 
	glVertex3f(-1.5f, -2.0f, 0.0f);
	glEnd();
	glColor3f(1,1,1);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glVertex3f(0.0,-1,0);
	glEnd();

}

void FootBallField::initGoalPost(void)
{
	glPointSize(4.0);
	glLineWidth(3.0);
	glPushAttrib(GL_COLOR_BUFFER_BIT);
	goalPostDisplayListIndex = glGenLists(1);
	glNewList(goalPostDisplayListIndex,GL_COMPILE); //compile the new list
		glPushMatrix();
			glColor3f(0,0,0);
			glLineWidth(3.0);
			glBegin(GL_LINE_LOOP);
			glVertex3f(-1.5f, 0.0f, 0.0f);
			glVertex3f(1.5f, 0.0f, 0.0f); 
			glVertex3f(1.5f, 2.0f, 0.0f);
			glVertex3f(-1.5f, 2.0f, 0.0f);
			glEnd();
			glColor3f(0,0,0);
			glLineWidth(1.0);
			for(float i = 2.0, j=-1.5; i>0 && j<=1.5; i-=0.1,j+=0.15)
			{
				glBegin(GL_LINES);
				glVertex3f(1.5f,i,0.0f);
				glVertex3f(-1.5f,i, 0.0f);
				glVertex3f(j,0.0f,0.0f);
				glVertex3f(j,2.0f,0.0f);
				glEnd();
				cout<<"Here"<<endl;
			}
		glPopMatrix();
    glEndList(); //end the list	
	glPopAttrib();
}

void FootBallField::drawGoalPost(void)
{
	//These two statements have to be included here...cannot put them in the Constructor because of the SHITTY state machine
	if(goalPostDisplayListIndex == -1)
		initGoalPost();
		
	glPushMatrix();
		glTranslated(1.5, 0, -100); //translate the cube
		glScalef(5, 5, 5);
		glCallList(goalPostDisplayListIndex);
	glPopMatrix();

}










void FootBallField::initSun()
{
	//Putting the sun into the display list
	glPushAttrib(GL_COLOR_BUFFER_BIT);
	sunDisplayListIndex = glGenLists(1);
	glNewList(sunDisplayListIndex,GL_COMPILE); //compile the new list
		glPushMatrix();
		glColor3f(1, 1, 0);
		glutSolidSphere(0.5,65,15);
		glPopMatrix();
    glEndList(); //end the list	
	glPopAttrib();
}

void FootBallField::drawSun()
{
	//These two statements have to be included here...cannot put them in the Constructor because of the SHITTY state machine
	if(sunDisplayListIndex == -1)
		initSun();

	glPushMatrix();
		glTranslatef(0, 0, -5);
		glTranslatef(-10,10,-10);
		glCallList(sunDisplayListIndex);
	glPopMatrix();
}

void FootBallField::initSky()
{
	//Putting the sky in a display list
	glPushAttrib(GL_COLOR_BUFFER_BIT);
	skyDisplayListIndex= glGenLists(1);
	glNewList(skyDisplayListIndex,GL_COMPILE); //compile the new list
		glPushMatrix();
		glColor3f(0.7,0.8,0.90);
		glRectf(0, 0, 5000, 5000);
		glPopMatrix();
    glEndList(); //end the list	
	glPopAttrib();
}

void FootBallField::initGround()
{
	//Putting the ground in a display list
	glPushAttrib(GL_COLOR_BUFFER_BIT);
	groundDisplayListIndex = glGenLists(1);
	glNewList(groundDisplayListIndex,GL_COMPILE); //compile the new list
		glPushMatrix();
		glColor3f(0.0, 0.7, 0);
		glRectf(0, 0, 5000, 5000);
		glPopMatrix();
    glEndList(); //end the list	
	glPopAttrib();
}

void FootBallField::drawGroundAndSky()
{
	//These two statements have to be included here...cannot put them in the Constructor because of the SHITTY state machine
	if(skyDisplayListIndex == -1 && groundDisplayListIndex == -1)
	{
		initSky();
		initGround();
	}

	glPushMatrix();
		glTranslatef(0, 0, -10);		
		glTranslatef(-1000, 0, -500);
		glCallList(skyDisplayListIndex);
		glTranslatef(0, -1000, 0);
		glCallList(groundDisplayListIndex);
	glPopMatrix();
}











FootBallField::~FootBallField()
{
	//delete scoreBoard;
}
#endif