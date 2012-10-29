#ifndef _SCORE_H
#define _SCORE_H

//This class keeps track of the Human player's score.

class ScoreBoard
{
private:
	int numGoals;
	GLfloat xco_ordinate, yco_ordinate;
	GLfloat width, height;
public:
	ScoreBoard(GLfloat x, GLfloat y);
	inline void setNumOfGoals(int);
	inline int getNumOfGoals(void);
	void draw(void);
};
ScoreBoard::ScoreBoard(GLfloat x, GLfloat y)
{
	numGoals = 0;
	xco_ordinate = x;
	yco_ordinate = y;
	width = 0.5;
	height = 0.3;
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
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POLYGON);
	glVertex3f(3.0f, 3.0f, 0.0f); // The top left corner  
	glVertex3f(3.0f, 2.0f, 0.0f); // The bottom left corner 
	glVertex3f(5.0f, 2.0f, 0.0f); // The top right corner  
	glVertex3f(5.0f, 3.0f, 0.0f); // The bottom right corner  
	glEnd();
}
#endif