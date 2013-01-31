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

	colorList[6] = new vlgColor(1.0f, 0.48f, 0.0f);	   //orange
	colorList[7] = new vlgColor(0.47f, 0.0f,  1.0f);//purple

}

Color::Color(int i)
{
	Color();
	setActiveColorByIndex(i);
}
void Color::setActiveColorByIndex(int i)//! Range 0-7
	{
//std::cout << "setActiveColorByIndex(i= "<<i<<")" << std::endl;
		if(i > 7 || i < 0)
			i=0;
		activeColor = colorList[i];
		std::cout << "color: " << colorList[i]<<std::endl;

			std::cout<<"color red:"<<(float)activeColor->getRed()<<std::endl;
			std::cout<<"color green:"<<(float)activeColor->getGreen()<<std::endl;
			std::cout<<"color blue:"<<(float)activeColor->getBlue()<<std::endl;
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