#include "Line.h"
#include <iostream>
Line::Line(void)
{
	setActiveColorByIndex(0);
}

Line::Line(int i)
{
	std::cout << "Line(int "<<i<<")"<< std::endl;
	setActiveColorByIndex(i);
}

void Line::clear()
{
	getMyX().clear();
	getMyY().clear();
	getMyZ().clear();	//new
	//getMyUndoSizeZ().clear();	//new
	myUndoSizeZ = 0.0f;
	notify();
}

std::vector<float> Line::getMyX()
{return myX;}

std::vector<float> Line::getMyY()
{return myY;}

std::vector<float> Line::getMyZ() //new
{return myZ;}

float Line::getMyUndoSizeZ()	//new
{return myUndoSizeZ;}
