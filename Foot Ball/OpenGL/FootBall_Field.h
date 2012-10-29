#ifndef _FOOTBALL_FIELD_H
#define _FOOTBALL_FIELD_H
#include "Football.h"
#include "GoalKeeper.h"
#include "ScoreBoard.h"
//This class keeps track of all the objects in the Game World, including the Football, and textures of the field, etc.

class FootBallField
{
private:
	Football * football;
	ScoreBoard *scoreBoard;
	//GoalKeeper goalkeeper;

	void drawGround(void);
	void drawSky(void);
	void drawMarkings(void);
	void drawGoalPost(void);
	void drawSun(void);
public:
	FootBallField();
	void draw(void);
	~FootBallField();
};
FootBallField::FootBallField()
{
	this->football = new Football(1,2,3);
	this->scoreBoard = new ScoreBoard(2.0,5.0);
	//this->goalkeeper = new GoalKeeper();
}
void FootBallField::draw()
{
	drawGround();
	drawSky();
	drawMarkings();
	drawGoalPost();
	//goalPost.draw();
	scoreBoard->draw();
	//goalKeeper.draw();
	football->draw();
	drawSun();
	
}
void FootBallField::drawGround(void)
{
	glColor3f(0.0,1.0,0.0);
	glPointSize(8.0);
	glBegin(GL_POLYGON); // Start drawing a line primitive  
	glVertex3f(-5.0f, -5.0f, 0.0f); 
	glVertex3f(-5.0f, 1.0f, 0.0f); 
	glVertex3f(5.0f, 1.0f, 0.0f); 
	glVertex3f(5.0f, -5.0f, 0.0f);
	glEnd();  
}
void FootBallField::drawSky(void)
{
	
	glColor3f(0.7,0.8,0.90);
	glBegin(GL_POLYGON); // Start drawing a line primitive  
	glVertex3f(-5.0f, 0.0f, 0.0f); // The bottom Left corner  
	glVertex3f(-5.0f, 5.0f, 0.0f); // The top left corner  
	glVertex3f(5.0f, 5.0f, 0.0f); // The bottom left corner  
	glVertex3f(5.0f, 0.0f, 0.0f); // The top left corner  
	glEnd(); 

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
void FootBallField::drawGoalPost(void)
{
	glPointSize(4.0);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-1.5f, 0.0f, 0.0f);
	glVertex3f(1.5f, 0.0f, 0.0f); 
	glVertex3f(1.5f, 2.0f, 0.0f);
	glVertex3f(-1.5f, 2.0f, 0.0f);
	glEnd();
	glColor3f(0,0,0);
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

}
void FootBallField::drawSun()
{
	glColor3f(1,1,0);
	glTranslatef(-2.5,3.5,0.0);
	glutSolidSphere(0.5,65,15);
	//glTranslatef(0.0f, 0.0f, -5.0f);
}
FootBallField::~FootBallField()
{
	delete scoreBoard;
}
#endif