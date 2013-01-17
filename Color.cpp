#include "Color.h"
#include <iostream>
Color::Color(void)
{	
	std::cout << "Color(void)" << std::endl;
	colorList[0] = new vlgColor(1.0f, 0.0f, 0.0f); //red, default 
	colorList[1] = new vlgColor(0.0f, 1.0f, 0.0f); //green
	colorList[2] = new vlgColor(0.0f, 0.0f, 1.0f); //blue
	colorList[3] = new vlgColor(1.0f, 1.0f, 1.0f); //white
	colorList[4] = new vlgColor(0.0f, 0.0f, 0.0f); //black
	colorList[5] = new vlgColor(1.0f, 1.0f, 0.0f); //yellow
}

Color::Color(int i)
{
	std::cout << "Color(i= "<<i<<")" << std::endl;
	Color();
	setActiveColorByIndex(i);
}
void Color::setActiveColorByIndex(int i)//! Range 0-5
	{
//std::cout << "setActiveColorByIndex(i= "<<i<<")" << std::endl;
		if(i > 5 || i < 0)
			i=0;
		activeColor = colorList[i];
		notify();
	}

void Color::setActiveColor(vlgColor *color)
{
	activeColor = color;
	notify();
}

vlgColor* Color::getActiveColor(void)
	{
		return activeColor;
	}