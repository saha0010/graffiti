#ifndef WALLVIEW
#define WALLVIEW

#include <iostream>
#include <vlgGLObserver.h>
#include "Wall.h"

//! View mit einer OpenGL-Ausgabe
class WallView : public vlgGLObserver
{

public:
	//!Default-Konstruktor zur Initialisierung
	WallView(void);
	//!Konstruktor mit einem Zeiger auf das Subject, das wir beobachten. Wird Hauptsächlich benutzt
	WallView(Wall *w);
	//!Kopierkonstruktor
	WallView(Wall& w);
	//! Kopierzuweisungskonstruktor
	WallView& operator=(WallView &w);

	//! Grafische Ausgabe, wird anstatt Display() aufgerufen
	/*!
		* Die draw-Funktion der WallView schaltet die 2D-Texturen frei und
		* bindet die aktuelle Hintergrund-Textur an ein erstelltes Rechteck,
		* jenes das von uns bestimmte Koordinatensystem im 4:3-Format ausfüllt.
		* Danach werden die 2D-Texturen wieder ausgeschaltet um kein Fehlverhalten
		* mit glColor hervorzurufen. Mithilfe des Bool \a showDataReceived wird 
		* entschieden ob \a visionMode(), \a dataReceivedCircle() und \a chosenColor()
		* angezeigt werden sollen.
		*
		* \sa visionMode(), dataReceivedCircle(), choosenColor()
	*/
	virtual void draw(void);

	//! Update, Änderungen werden angepasst
	virtual bool update(const vlgSubject &changedSubject);

	//! Tracker-Signal-Kreis visuelle Ausgabe
	/*!
		* Die dataReceivedCircle-Funktion zeichnet mithilfe von
		* GL_TRIANGLE_FAN und GL_PolygonMode(GL_FRONT, GL_FILL)
		* einen Kreis der in die untere rechte Ecke der Darstellung
		* translatiert wird. In Abhängigkeit ob Daten vom Tracker
		* der Kinect erhalten werden, färbt sich der Kreis rot oder 
		* grün. Diese Information erhalten wir mit dem Aufruf von
		* \a dataReceived(). Diese visuelle Rückgabe kann über das
		* false setzten des Bool showDataReceived ausgeblendet werden.
		*
		* \sa dataReceived()
	*/
	virtual void dataReceivedCircle(void);

	//! Tracker-Signal vorhanden(grün)/verloren(rot)
	/*!
		* Die dataReceived-Funktion erhält über den Parameter \a received
		* des Hintergrund-Subjekts die Information ob Tracker-Daten
		* empfangen werden und setzt dementsprechend glColor auf rot
		* oder grün.
		*
		* \param received liefert Information ob Tracker-Daten empfangen werden.
		* \sa dataReceivedCircle(), visionMode()
	*/
	virtual void dataReceived(bool data);

	//! Visuelle Rückgabe der ausgewählten Farbe
	/*!
		* Die chosenColor-Funktion der WallView zeichnet und translatiert
		* ein Rechteck in die untere linke Ecke der Darstellung. Sie färbt
		* das Rechteck mit den RGB-Anteilen der aktiven Farbe. Diese visuelle
		* Rückgabe kann über das false setzten des Bool showDataReceived
		* ausgeblendet werden.
		*
		* \sa dataReceivedCircle(), visionMode()
	*/
	void chosenColor(void);

	//! Visuelle Hilfe zur Erkennung der aktuellen Position der Haupthand
	/*!
		* Die visionMode-Funktion stellt an der aktuellen Position der
		* Anwendungsrelativen Hand (Standard: rechte Hand) einen Kreis dar.
		* Mithilfe dieses Kreises lässt sich das bedienen der Anwendung 
		* vereinfachen.  Diese visuelle Rückgabe kann über das false
		* setzten des Bool showDataReceived ausgeblendet werden.
		*
		* \sa dataReceivedCircle(), chosenColor()
	*/
	void visionMode(void);


private:
	//! Das Subject, das wir beobachten
	Wall *wall;

};
#endif