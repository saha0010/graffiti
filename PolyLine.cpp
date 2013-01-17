#include "PolyLine.h"

//!Default Konstruktor - wird hauptsächlich verwendet
PolyLine::PolyLine(void): mode(0)
{
	std::cout << "PolyLine()" << std::endl;
	setActiveColor(new vlgColor(0.0f, 0.0f, 0.0f));
}

PolyLine::PolyLine(int i): mode(0)
{
	std::cout << "PolyLine(int "<<i<<")"<< std::endl;
	setActiveColorByIndex(i);
}


void PolyLine::changePolyLineMode(void)
{
	mode++;
	if(mode == 2)
		mode = -1;
	notify();
	std::cout<<"mode: "<< mode<<std::endl;
}

int PolyLine::getMode(void)
{return mode;}