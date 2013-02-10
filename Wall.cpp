#include "Wall.h"


Wall::Wall(void): backgroundIndex(0), received(false), showDataReceived(true), one(),two(),three(),four(),five(),six(),
				  status(0), anzahlTexturen(6), index(0), moveX(0.0f), moveY(0.0f)
{
	for(int i=0;i<anzahlTexturen;i++)
	{
		texNames[i] = 0;
	}
	setActiveColorByIndex(0);
}


void Wall::init(void)
{
	glEnable(GL_TEXTURE_2D);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(anzahlTexturen, texNames);
	fillTextureListWall();
	fillNameListWall();
	for(int i = 0;i<textureMaps.size();i++)
	{
		status = textureMaps.at(i).read(textureNames.at(i));
		glBindTexture(GL_TEXTURE_2D, texNames[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	   
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		textureMaps[i].setTexture();
	}
	glDisable(GL_TEXTURE_2D);
}

void Wall::fillTextureListWall(void)
{	
	textureMaps.push_back(one);
	textureMaps.push_back(two);
	textureMaps.push_back(three);
	textureMaps.push_back(four);
	textureMaps.push_back(five);
	textureMaps.push_back(six);
}

void Wall::fillNameListWall(void)
{
	textureNames.push_back("../textures/mauer_1.bmp");
	textureNames.push_back("../textures/asphalt_1.bmp");
	textureNames.push_back("../textures/holzwand.bmp");
	textureNames.push_back("../textures/wand_backstein_2.bmp");
	textureNames.push_back("../textures/wand_backstein_3.bmp");
	textureNames.push_back("../textures/credits.bmp");
}

void Wall::nextTexture(void)
{
	if (backgroundIndex < (anzahlTexturen-1))
	{
		++backgroundIndex;
		glBindTexture(GL_TEXTURE_2D, texNames[backgroundIndex]);
	}
	else 
	{
		backgroundIndex = 0;
		glBindTexture(GL_TEXTURE_2D, texNames[backgroundIndex]);
	}
}

void Wall::previousTexture(void)
{
	if(backgroundIndex >0)
	{
		--backgroundIndex;
		glBindTexture(GL_TEXTURE_2D, texNames[backgroundIndex]);
	}
	else
	{
		backgroundIndex = 5;
		glBindTexture(GL_TEXTURE_2D, texNames[backgroundIndex]);
	}
}

float Wall::getX()
{return moveX;}

float Wall::getY()
{return moveY;}

void Wall::setX(float x)
{moveX = x;}

void Wall::setY(float y)
{moveY = y;}
