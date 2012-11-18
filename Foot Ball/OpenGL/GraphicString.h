#ifndef _GRAPHIC_STRING_H
#define _GRAPHIC_STRING_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <GL/glut.h>

#include "Coordinates.h"

using namespace std;

class GraphicString
{
private:
	string str;
	vector<Coordinates> coords;
	string pool;

	void drawStrokeString(float value);
	void drawStrokeString(string str);
public:
	GraphicString(){}
	GraphicString(string s);
	void setPool(string p);
	bool isPoolNewLine();
	string getString();
	void setString(string s);
	void append();
	void append(Coordinates coord);
	void draw();
};

GraphicString::GraphicString(string pool)
{
	this->pool = pool;
}

string GraphicString::getString()
{
	return str;
}

void GraphicString::setString(string s)
{
	str = s;
}

void GraphicString::setPool(string p)
{
	pool = p;
}

bool GraphicString::isPoolNewLine()
{
	if(pool.length() == 0)
		return false;

	if(pool[0] == '\n')
		return true;
	return false;
}

void GraphicString::append(Coordinates coord)
{
	if(pool.length() == 0)
		return;

	str += pool[0];
	pool = pool.substr(1);


	coords.push_back(coord);
}

void GraphicString::append()
{
	if(pool.length() == 0)
		return;

	str += pool[0];
	pool = pool.substr(1);

	Coordinates prev = coords[coords.size() - 1];
	Coordinates coord(prev.get(X_AXIS) + 100, prev.get(Y_AXIS), prev.get(Z_AXIS) - 100);
	if(str[str.length() - 1] == '\n')
	{
		coord.set(X_AXIS, 0);
		coord.set(Y_AXIS, coord.get(Y_AXIS) - 200);
		coord.set(Z_AXIS, 50);
	}
	coords.push_back(coord);

	//glColor3f(rand() / 255.0, rand() / 255.0, rand() / 255.0);
}

void GraphicString::drawStrokeString(float value)
{
   stringstream ss;
   ss << value;
   string valueString = "v = " + ss.str();

   drawStrokeString(valueString);
}

void GraphicString::drawStrokeString(string str)
{
	for(int i=0; i<str.length(); i++)
	   glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
}

void GraphicString::draw()
{	
	for(int i=0; i<coords.size(); i++)
	{
		glPushMatrix();
			glTranslatef(coords[i].get(X_AXIS), coords[i].get(Y_AXIS), coords[i].get(Z_AXIS));
			glColor3f(0, 1, 0);
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str[i]);
		glPopMatrix();
	}
}

#endif