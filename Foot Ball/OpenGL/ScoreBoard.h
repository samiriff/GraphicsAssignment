#ifndef _SCORE_H
#define _SCORE_H
#include<string.h>
#include <iostream>
#include <sstream>
#include <string>
#include<stdlib.h>
#include "Football.h"
using namespace std;
//This class keeps track of the Human player's score.

class ScoreBoard
{
private:
	int numGoals;
	GLfloat xco_ordinate, yco_ordinate;
	GLfloat width, height;
	string numGoalsConverted;
	//int intScore;
	
    
	 
	
	public:
	ScoreBoard(GLfloat x, GLfloat y);
	inline void setNumOfGoals(int);
	inline int getNumOfGoals(void);
	void drawScore();
	void drawScore(char *, int, int, int);
	void draw(void);
	void appendScore(int);
};
ScoreBoard::ScoreBoard(GLfloat x, GLfloat y)
{
	numGoals = 0;
	xco_ordinate = x;
	yco_ordinate = y;
	width = 0.5;
	height = 0.3;
	//char *intStr;
	char intStr[10];
	_itoa(numGoals,intStr,10);
	string score = string(intStr);
}
void ScoreBoard::setNumOfGoals(int goals)
{
	numGoals = goals;
}

int ScoreBoard::getNumOfGoals(void)
{
	return numGoals;
}
void ScoreBoard::draw(void)
{
	glColor3f(0, 0, 0);
	drawScore();

	glColor3f(1.0,0.0,-2.0);
	glBegin(GL_POLYGON);
		glVertex3f(3.0f, 3.0f, 0.0f); // The top left corner  
		glVertex3f(3.0f, 2.0f, 0.0f); // The bottom left corner 
		glVertex3f(5.0f, 2.0f, 0.0f); // The top right corner  
		glVertex3f(5.0f, 3.0f, 0.0f); // The bottom right corner  
	glEnd();
}

void ScoreBoard::appendScore(int numGoalsConverted)
{
		
}

void ScoreBoard::drawScore()
{
	stringstream ss;
	ss << numGoals;
	string valueString = "Score = " + ss.str();

	glPushMatrix();
		glTranslatef(3.2, 2.5, 0);
		glScalef(0.002, 0.002, 0.02);
		for(int i=0; i<valueString.length(); i++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, valueString[i]);
	glPopMatrix();
}

void ScoreBoard::drawScore(char* string,int x,int y,int z) // Draw the score
{
	char *c;
	glPushMatrix();	
	//glTranslatef(x, y+8,z);
	//glScalef(0.09f,-0.08f,z);

	draw();
	for (c=string; *c != '\0'; c++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
	}
	glPopMatrix();
}	
#endif