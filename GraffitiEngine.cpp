#include "GraffitiEngine.h"

#include <vlgStillCamera.h>
#include <vlgOrtho.h>
#include <cmath>

// Default-Konstruktor
GraffitiEngine::GraffitiEngine(void) :  glLinesObs(lineList), glStampObs(stampList), glCircleObs(circleList),
										glDrawObs(lineList),
                                        pressed(false), tracker(false),
										wX(0.0f), wY(0.0f), wZ(0.0f), xMin(-4.0), xMax(4.0f), yMin(-3.0f),
										yMax(3.0f), deltaX(xMax-xMin), deltaY(yMax-yMin), pitch(16.0f), colorIndex(0),												saveCounter(1), 
										xGeste(0.0f), yGeste(0.0f), temp(0.0f), delta(0.0f), leftHand(false), zUndoSize(0.0f)
{
std::cout<<"GraffitiEngine()"<<std::endl;
tLine = new Line(colorIndex);
lineList.push_back(*tLine);

//! Wall erzeugen und Observer zuweisen
	wall = new Wall();
	glWallObs = WallView(wall);
	
//!Array initialisieren
	trackAry[0] = 0.0f;
	trackAry[1] = 0.0f;
	trackAry[2] = 0.0f;	// z-Wert

	trackAryLeft[0] = 0.0f;
	trackAryLeft[1] = 0.0f;

	trackAryLeftShoulder[0] = 0.0f;
	trackAryLeftShoulder[1] = 0.0f;

//! Konstante-Werte sin und cos von Neigungswinkel der Kinect
	sinPitch = sin(vlgDeg2Rad(pitch));
	cosPitch = cos(vlgDeg2Rad(pitch));
	

}

//!OpenGL Initialisierung 
void GraffitiEngine::initContext(void) 
{
	std::cout << "InitContext() begin!" << std::endl;

//! Orthogonalprojektion einstellen
    vlgOrtho *ortho = new vlgOrtho(xMin, xMax, yMin, yMax);
    setViewProjection(ortho);
	useStillCamera(3.0f, 0.0f, 0.0f);

//!	Allgemeine OpenGL einstellungen
	wks->noShow();
	grid->noShow();
	setWindowTitle("Virtual Graffiti");
	wall->init();
	//glLineWidth(12.0f);
	
	attachObserver();
	VRPNGeraete();
}
//!OpenGL-Observer hinzufuegen (Aus InitConext auslagern)
void GraffitiEngine::attachObserver(void)
{ 
	std::cout << "attachGLObserver(&glDrawObs)" << std::endl;
    attachGLObserver(&glDrawObs);
	std::cout << "attachGLObserver(&glLinesObs)" << std::endl;
    attachGLObserver(&glLinesObs);
	

	std::cout << "attachGLObserver(&glWallObs)" << std::endl;
    attachGLObserver(&glWallObs);
	std::cout << "attachGLObserver(&glStampObs)" << std::endl;
    attachGLObserver(&glStampObs);
	std::cout << "attachGLObserver(&glCircleObs)" << std::endl;
    attachGLObserver(&glCircleObs);
}


//!VRPN-Geräte aktivieren
void GraffitiEngine::VRPNGeraete(void)
{	
	useAnalogDevice("Mouse0@localhost");
	useButtonDevice("Keyboard0@localhost");	
//	useButtonDevice("WiiMote0@localhost");
//	useTrackerDevice("Tracker0@zwo210-GONZO.ds.fh-kl.de");
//	useButtonDevice("WiiMote0@davis.ds.fh-kl.de");
//	useTrackerDevice("Tracker0@miles.ds.fh-kl.de");


	//  useAnalogDevice("Mouse0@AcerTablet");
	//  useButtonDevice("Keyboard0@AcerTablet");
}


//!Callback für Maus0
void GraffitiEngine::handleAnalog(void *userData, const vrpn_ANALOGCB a)
{ 
	wX = a.channel[0];
	wY = a.channel[1];
	wZ = 0.15f;

	zUndoSize = undoList.size();
//!Wenn Sprühknopf gedrückt und tracker ausgeschaltet ist
	if(!tracker)
	{
		wall->setX(coordAdjuMouse(true));
		wall->setY(coordAdjuMouse(false));
		if(pressed)
		{
			
			lineList.front().myX.push_back(coordAdjuMouse(true));
			//std::cout<<"x="<<coordAdjuMouse(true)<<std::endl;
			lineList.front().myY.push_back(coordAdjuMouse(false));
			//std::cout<<"y="<<coordAdjuMouse(false)<<std::endl;
			lineList.front().myZ.push_back(wZ);		// Z-Wert-Radius fix für Analog //new
			lineList.front().myUndoSizeZ = zUndoSize;	// Listenposition Z-Ebene	//new
			//std::cout << "zTmp ist: " << zUndoSize << std::endl;
		}
		lineList.front().notify();
		//"Wisch Geste" 
		nextTextureGestureMouse();
	}
}



//!Callback für Tastatur0 oder WiiMote0
void GraffitiEngine::handleButton(void *userData, const vrpn_BUTTONCB b)
{
//!Tastatur
	if(!tracker){
		if(b.button == 57 && b.state==1) // solange "SPACE" gedrückt ist

		{	
			sprayPressed();
			std::cout<< "Button: "<< b.button<<std::endl;
		}
		else if(b.button == 57 && b.state==0)// wenn "SPACE" losgelassen wird
		{
			sprayReleased();
		}
		else
		{
			pressed  = false;

		}
	}else{
//!WiiMote

		if(b.button == 0 && b.state== 1)//Home
			savePicture();

		if(b.button == 1 && b.state== 1)//1
			addCircle();

		if(b.button == 2 && b.state== 1)//2
			addStamp();

	//SprayButton 
		if(b.button == 3 && b.state==1){//A
			sprayPressed();
		}
		else if(b.button == 3 && b.state==0){//A
			sprayReleased();
		}
		else{
			pressed  = false;
		}

		if(b.button == 4 && b.state== 1)//B
			undo();

		if(b.button == 5 && b.state == 1)//Minus
			clearAll();

		if(b.button == 6 && b.state== 1){//+
			//if(!lineList.empty())	
				
				//lineList.back().changePolyLineMode();	
		}

		if(b.button == 7 && b.state == 1)//links
			previousColor();

		if(b.button == 8 && b.state == 1)//rechts
			nextColor();

		if(b.button == 9 && b.state == 1)//runter
			wall->showDataReceived = !wall->showDataReceived; 

		if(b.button == 10 && b.state == 1)//hoch
			wall->nextTexture();
	}
}

//!Callback für Tracker0
void GraffitiEngine::handleTracker(void* userData, const vrpn_TRACKERCB t)
{
	
	// Tracker-Signal vorhanden
	wall->received=true;
	if(tracker)
	{
/*		trackAry[0] = t.pos[0];
		trackAry[1] = t.pos[1];
		trackAry[2] = t.pos[2];
		wX = trackAry[0];
		wY = trackAry[1];
		wZ = trackAry[2];		*/

		if(t.sensor == 14)//Rechte Hand
		{
			trackAry[0] = t.pos[0];
			trackAry[1] = t.pos[1];
			trackAry[2] = t.pos[2];
			wX = trackAry[0];
			wY = trackAry[1];
			wZ = trackAry[2];
			zUndoSize = undoList.size();
			wall->setX(coordAdjuTracker(true));
			wall->setY(coordAdjuTracker(false));
		}
		
		if(pressed && t.sensor == 14)//Spray gedrückt und linke Hand
		{
			trackAry[0] = t.pos[0];
			trackAry[1] = t.pos[1];
			trackAry[2] = t.pos[2];
			wX = trackAry[0];
			wY = trackAry[1];
			wZ = trackAry[2];
			zUndoSize = undoList.size();
			//line->myX.push_back(coordAdjuTracker(true));
			//line->myY.push_back(coordAdjuTracker(false));	

			lineList.front().myX.push_back(coordAdjuTracker(true));
			lineList.front().myY.push_back(coordAdjuTracker(false));
			lineList.front().myZ.push_back(wZ);		//new

		}

		if(t.sensor == 8) //Linke Hand
		{
			//nextTextureGesture();		//Tracker- und Maus-fähig

			//trackAryLeft[1] = t.pos[1];
			trackAry[0] = t.pos[0];
			trackAry[1] = t.pos[1];
			trackAry[2] = t.pos[2];
			wX = trackAry[0];
			wY = trackAry[1];
			wZ = trackAry[2];
			zUndoSize = undoList.size();

			trackAryLeft[1] = (cosPitch * t.pos[1] + sinPitch * t.pos[2]) -0.82f;

			nextTextureGestureTracker();//Tracker abhängig
		}

		if (t.sensor == 5) //Linke Schulter
		{
			trackAryLeftShoulder[1] = (cosPitch * t.pos[1] + sinPitch * t.pos[2]) -0.82f;
		}
	}
}

void GraffitiEngine::nextTextureGestureMouse(void)
{
	string s;
	if(tracker){
	xGeste = coordAdjuTracker(true);
	yGeste = coordAdjuTracker(false);
	s = "Hand";
	}
	else{	
	xGeste = coordAdjuMouse(true);
	yGeste = coordAdjuMouse(false);
	s = "Maus";
	}
	if((yGeste >= 0.5f && yGeste <= 3.0f) && !pressed)
	{
	/*	std::cout<<"----------------------------"<<std::endl;
		std::cout<< s <<" in Gestenbereich! Y = "    <<yGeste<<std::endl;
		std::cout<< s <<" in Gestenbereich! X = "    <<xGeste<<std::endl;
		std::cout<< s <<" in Gestenbereich! delta = " <<delta<<std::endl;
		std::cout<<"----------------------------"<<std::endl;*/
		delta = xGeste - temp;
		if(!leftHand)
		{
			//std::cout<<"if(!leftHand)"<<std::endl;
			temp = xGeste;
			leftHand =true;
		}
		else
		{
			if(delta >= 4.5)
			{
				wall->nextTexture();
				delta = 0.0f;
				temp = 0.0f;
				leftHand = false;
			}else if(delta <= -4.5f)
			{
				wall->previousTexture();
				delta = 0.0f;
				temp = 0.0f;
				leftHand = false;
			}
		}
	}
	else
		leftHand = false;
}

void GraffitiEngine::nextTextureGestureTracker(void)
{
	string s;
	if (tracker)
	{

		if(fabs (trackAryLeft[1] - trackAryLeftShoulder[1]) <= 0.14f) //absoluter Betrag von yLinkeHand - yLinkeSchulter mit einer erlaubten Varianz von 0.15f
		{
			xGeste = coordAdjuTracker(true);
			//yGeste = coordAdjuTracker(false);
			s = "Hand";
			std::cout<<"----------------------------"<<std::endl;
			//std::cout<< s <<" in Gestenbereich! Y = "    <<yGeste<<std::endl;
			std::cout<< s <<" in Gestenbereich! X = "    <<xGeste<<std::endl;
			std::cout<< s <<" in Gestenbereich! delta = " <<delta<<std::endl;
			std::cout<<"----------------------------"<<std::endl;
			std::cout<< s <<" nextTexturGestureTracker"<<std::endl;
	
			if(!pressed)
			{
				
				delta = xGeste - temp;
				if(!leftHand)
				{
					std::cout<<"if(!leftHand), Start der Geste"<<std::endl;
					temp = xGeste;
					leftHand =true;
				}
				else
				{
					if(delta >= 2.25f)
					{
						wall->nextTexture();
						delta = 0.0f;
						//temp = 0.0f;
						leftHand = false;
					}else if(delta <= -2.25f)
					{
						wall->previousTexture();
						delta = 0.0f;
						//temp = 0.0f;
						leftHand = false;
					}
				}
			}
			else
				leftHand = false;
			
		} else
			{
			leftHand = false;
			temp = 0.0f;
			}
	}

}

//! Anzahl der gemalten PolyLines ausgeben
void GraffitiEngine::printLists()
{
	std::cout <<"Anzahl PolyLines: "<< lineList.size()-1<<std::endl;
	std::cout <<"Anzahl Stamps: "<< stampList.size()<<std::endl;
	std::cout <<"Anzahl Circles: "<< circleList.size()<<std::endl;
	std::cout <<"Insgesamt: "<< undoList.size() <<std::endl;
}

//!Tastatur handler von GLUT-Engine(Localhost)
void GraffitiEngine::keyboard(unsigned char key, int x, int y)
{
	switch (key) 
	{
	case 'p':
		std::cout << "VRPN Daten werden verarbeitet!" << std::endl;
		idleOn();
	break;	
	case 's':
		std::cout << "VRPN Daten werden nicht verarbeitet!" << std::endl;
		idleOff();
	break;
	case 'g':
		printLists();
	break;
	case 'c':
		clearAll();
	break;
	case 't':
		if(!tracker)
		{
			tracker = true;
			cout << "Trackerdaten werden verarbeitet!" << endl;}
		else
		{
			tracker = false;
			cout << "Trackerdaten werden nicht mehr verarbeitet!" << endl;
		}
		break;
	case 'w':
		wall->nextTexture();
		break;
	case 'W':
		wall->previousTexture();
		break;
	case 'o':
		if(!lineList.empty())
			//lineList.back().changePolyLineMode();
		break;
	case'd':
		nextColor();	
		break;
	case'a':
		previousColor();
		break;
	case'k':
		addCircle();
		break;
	case'r':
		savePicture();
		break;
	case'j':
		wall->showDataReceived = !wall->showDataReceived;
		break;
	case'h':
		addStamp();
		break;
	case'z':
		undo();
		break;
	}
}
int GraffitiEngine::incColorIndex(int c)
{
	
	if(c >= 5)
		return 0;
	else 
		//std::cout<<"incNCI(int c): "<<(c+1)<<std::endl;
		return ++c;
}
int GraffitiEngine::decColorIndex(int c)
{
	if(c <= 0)
		return 5;
	else
		return --c;
}
//!Bild verwerfen
void GraffitiEngine::clearAll(void)
{
	lineList.clear();
	lineList.push_back(*tLine);
	stampList.clear();
	circleList.clear();
	undoList.clear();
}
void GraffitiEngine::nextColor()
{
	colorIndex = incColorIndex(colorIndex);
	wall->setActiveColorByIndex(colorIndex);
}
void GraffitiEngine::previousColor()
{
	colorIndex = decColorIndex(colorIndex);	
	wall->setActiveColorByIndex(colorIndex);
}

void GraffitiEngine::addStamp()
{	
	Stamp *s;
	if(!tracker){
		s = new Stamp(coordAdjuMouse(true), coordAdjuMouse(false));
	}
	else {
		s = new Stamp(coordAdjuTracker(true), coordAdjuTracker(false));
	}

	stampList.push_back(*s);
	undoList.push_back(1);
}
void GraffitiEngine::addCircle()
{	
	Circle *c;
	if(!tracker)
		// z-Wert eingebaut undoList.size() +1 um an die tatsächliche Position zu zeichnen
	   c = new Circle(0.5f, coordAdjuMouse(true),coordAdjuMouse(false),(float) ((zUndoSize +1)), colorIndex);
	else
	   c = new Circle(0.5f, coordAdjuTracker(true),coordAdjuTracker(false), (float) (zUndoSize +1), colorIndex);
	
	circleList.push_back(*c);
	undoList.push_back(2);
}

void GraffitiEngine::sprayPressed()
{
	std::cout << "Spray ist gedrückt " << std::endl;
	lineList.front().setActiveColorByIndex(colorIndex);
	pressed  = true;
}
void GraffitiEngine::sprayReleased()
{
	std::cout << "Space wurde logelassen " << std::endl;
	lineList.push_back(lineList.front());
	lineList.front().myX.clear();
	lineList.front().myY.clear();
	lineList.front().myZ.clear();	//new
	undoList.push_back(0);
	pressed = false;
	
}

void GraffitiEngine::undo(void)
{
	if(!undoList.empty())
	{
		switch(undoList.back())
		{
		case 0:
			lineList.pop_back();
			break;
		case 1:
			stampList.pop_back();
			break;
		case 2:
			circleList.pop_back();
			break;
		}
		undoList.pop_back();
		this->updateOpenGL();
	}
}
//!Umrechnen der Welt und Monitorkoordinate im Bezug auf das Koordinatensystem der Anwendung
float GraffitiEngine::coordAdjuMouse(bool chooseVariable)
{
	if(chooseVariable)
		return xMin+wX*deltaX;
	else
		return (yMin+(1-wY)*deltaY);
 }

float GraffitiEngine::coordAdjuTracker(bool chooseVariable)
{
	if(chooseVariable)
		return (-4.0f + ((wX+1.13f)/2.26f) * 8.0f); //Abbildung[-1.13, 1.13] -> [-4, 4] 
	else
	{
		//std::cout << "Wert " << -3.0f + ((yAnNeigungswinkelAnpassen()+0.65f)/1.7f) * 6.0f << std::endl;
		return (-3.0f + ((yAnNeigungswinkelAnpassen()+0.65f)/1.7f) * 6.0f); //Abbildung [-0.65, 0.65]->[-3, 3]
	}
}

float GraffitiEngine::yAnNeigungswinkelAnpassen(void)
{
		return ((cosPitch*wY + sinPitch*wZ) -0.82f);	
}


//!Speichern des Bildes
void GraffitiEngine::savePicture(void)
{
	int w,h;
	vlgTextureMap2D *capture = new vlgTextureMap2D;
	this->getWindowSize(w,h);
	capture->wholeFramebufferRead(w,h);
	std::string s;
	s = "Bild";
	char a[20];
	itoa(saveCounter,a,10);
	s.append(a);
	s.append(".dds");
	//capture->write("Picture"<<saveCounter<<".dds");
	capture->write(s);
	std::cout<<"Bild "<<saveCounter<<" wurde gespeichert!"<<std::endl;
	saveCounter++;
}
//!Info ausgeben ueber die Tastaturbelegung               
void GraffitiEngine::about(void)
{
	std::cout << "--------------------------------------------" << std::endl;
    std::cout << " Virtuelle Graffiti Wand " << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "                                            " << std::endl;
    std::cout << " Tastaturkommandos:                         " << std::endl;
	std::cout << "  p	   : VRPN ausgabe aktiviren           " << std::endl;	
	std::cout << "  s	   : VRPN ausgabe deaktivieren        " << std::endl;
    std::cout << "  SPACE  : Sprühknopf                    	  " << std::endl;
	std::cout << "  g  	   : Ausgabe lineList.size(), also Anzahl der gemalten Objekte" << std::endl;
	std::cout << "  c  	   : Bild Resetten							 " << std::endl;
	std::cout << "  t  	   : toggle Tracker/Maus					 "  << std::endl;
	std::cout << "  w  	   : nächster Hintergrund					 "  << std::endl;
	std::cout << "  W 	   : vorheriger Hintergrund					 "  << std::endl;
	std::cout << "  a  	   : nächste Farbe							 "  << std::endl;
	std::cout << "  d 	   : vorherige Farbe						 "  << std::endl;
	std::cout << "  o  	   : Zuletzt gemalte PolyLine öffnen, schließen oder zum Polygon machen"  << std::endl;
	std::cout << "  h  	   : Logo/Bitmap anhängen					 "  << std::endl;
	std::cout << "  k  	   : Kreis malen							 "  << std::endl;
	std::cout << "  z  	   : undo									 "  << std::endl;
	std::cout << "  j  	   : Interface ein/ausblenden				 "  << std::endl;
	std::cout << "  r  	   : Bild abspeichern						 "  << std::endl;
    std::cout << endl;
    std::cout << " ESC,                                       " << std::endl;
    std::cout << " q/Q: Programm beenden                      " << std::endl;
    std::cout << "--------------------------------------------" << std::endl; 
}

//!Singelton
GraffitiEngine* GraffitiEngine::instance = 0;
GraffitiEngine* GraffitiEngine::Instance(void)
{
	if (instance == 0) {
		GraffitiEngine::instance = new GraffitiEngine;
		vlgVRPNEngine::instance = GraffitiEngine::instance;
		vlgGlutEngine::instance = GraffitiEngine::instance;
	}
	return instance;
}