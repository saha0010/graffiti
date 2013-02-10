#include "Stamp.h"

Stamp::Stamp(float x, float y, float z):status(0),stampIndex(0), one() 							
{
	setX(x);
	setY(y);
	setZ(z);
	setWidth(0.57142f);
	setHeight(0.57142f);
	createTextureMap();
	anzahlStamps = (int)stampMaps.size();
}

void Stamp::createTextureMap(void)
{
	glEnable(GL_TEXTURE_2D);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(anzahlStamps, staNames);

	fillTextureListStamp();
	fillNameListStamp();
	for(int i = 0;i<stampMaps.size();i++)
	{
		status = stampMaps.at(i).read(stampNames.at(i));
		glBindTexture(GL_TEXTURE_2D, staNames[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	   
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		stampMaps[i].setTexture();
	}
	glDisable(GL_TEXTURE_2D);
}

void Stamp::fillTextureListStamp(void)
{	
	stampMaps.push_back(one);
}

void Stamp::fillNameListStamp(void)
{
	stampNames.push_back("../stamps/fhlogo.bmp");
}

void Stamp::nextStamp(void)
{
	std::cout<<"Stamp::nextStamp"<<std::endl;
	if (stampIndex < (anzahlStamps-1))
	{
		++stampIndex;
		glBindTexture(GL_TEXTURE_2D, staNames[stampIndex]);
	}
	else 
	{
		stampIndex = 0;
		glBindTexture(GL_TEXTURE_2D, staNames[stampIndex]);
	}	
}

int Stamp::getStampIndex(void)
{return stampIndex;}

vector<string> Stamp::getStampNames(void)
{return stampNames;}

vector<vlgTextureMap2D> Stamp::getStampMaps(void)
{return stampMaps;}

GLuint* Stamp::getStaNames(void)
{return staNames;}