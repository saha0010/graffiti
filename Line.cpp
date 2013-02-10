#include "Line.h"
#include <iostream>
Line::Line(void)
{
	setActiveColorByIndex(0);
}

Line::Line(int i)
{
	setActiveColorByIndex(i);
}

void Line::clear()
{
	getMyX().clear();
	getMyY().clear();
	getMyZ().clear();	
	myUndoSizeZ = 0.0f;
	notify();
}

std::vector<float> Line::getMyX()
{return myX;}

std::vector<float> Line::getMyY()
{return myY;}

std::vector<float> Line::getMyZ() 
{return myZ;}

float Line::getMyUndoSizeZ()	
{return myUndoSizeZ;}
