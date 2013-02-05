#include "Color.h"
#include <iostream>
Color::Color(void)
{	
colorList.push_back(new vlgColor(1.0f, 0.0f, 0.0f));	//red, default 
colorList.push_back(new vlgColor(0.0f, 1.0f, 0.0f));	//green
colorList.push_back(new vlgColor(0.0f, 0.0f, 1.0f));	//blue
colorList.push_back(new vlgColor(1.0f, 1.0f, 1.0f));	//white
colorList.push_back(new vlgColor(0.0f, 0.0f, 0.0f));	//black
colorList.push_back(new vlgColor(1.0f, 1.0f, 0.0f));	//yellow
colorList.push_back(new vlgColor(1.0f, 0.48f, 0.0f));	//orange
colorList.push_back(new vlgColor(0.47f, 0.0f,  1.0f));	//purple
}

Color::Color(int i)
{
	Color();
	setActiveColorByIndex(i);
}
void Color::setActiveColorByIndex(int i)
	{

	if(i > colorList.size() || i < 0)
			i=0;
		activeColor = colorList.at(i);
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

int Color::getColorCount(void)
	{
	return (int)colorList.size();
	}