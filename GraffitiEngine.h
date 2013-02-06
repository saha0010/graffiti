#ifndef GRAFFITIENGINE
#define GRAFFITIENGINE


#include "PolyLineView.h"
#include "TriangleView.h"
#include "CircleLineView.h"

/*! Observer f�r den Hintergrund*/
#include "WallView.h"

/*! Observer f�r die Stamps*/
#include "StampView.h"


#include "CircleView.h"
#include "vlgSubject.h"
#include <vlgVRPNEngine.h>
#include <vector>
#include <vlgUtil.h>

#include "Color.h"

//! Klasse einer OpenGL-Anwendung mit VRPN-Support
class GraffitiEngine : public vlgVRPNEngine
{
public:
	//!OpenGL Initialisierung
	void initContext(void);

	//!VRPN-Device Handler
		//!Analog-Device(Maus)
	virtual void handleAnalog(void* userData, const vrpn_ANALOGCB a);
		/*!Button-Devices(Tastatur oder WiiMote muss je nach Device im Code umgeschaltet und neu gebaut werden,
						 da aktuelle VRPN-Version keine 2 Verschiedene Button Devices unterst�tzt)*/
	virtual void handleButton(void* userData, const vrpn_BUTTONCB b);
		//!Tracker-Device(Kinect)
    virtual void handleTracker(void* userData, const vrpn_TRACKERCB t);

//"Normale" vlg-Funktionen
	//!Keyboardfunktion
	void keyboard(unsigned char key, int x, int y);
	//!Anwendungsbeschreibung
	void about(void);
	//!Singelton
	static GraffitiEngine* Instance(void);

private:
	//!Liste der gemalten PolyLines
	vector<Line> lineList;		
	//!Liste der gemalten Stamps
	std::vector<Stamp> stampList;
	//!Liste der gemalten Kreise
	std::vector<Circle> circleList;
	//!Liste der gemalten Dreiecke
	std::vector<Triangle> triangleList;

	Line *tLine;

	//!Zeiger auf den Hintergrund
	Wall *wall;

	//!View f�r die Linien Ausgabe als Polylines
	PolyLineView polyLineView;
	//!View f�r die Stamps(Bitmaps drauf kleben)
	StampView stampView;
	//!View f�r Kreise
	CircleView circleView;
	//!View f�r Dreiecke
	TriangleView triangleView;	
	//!View f�r die im Ausgabe als Kreise
	CircleLineView circleLineView;		
	//!View f�r den Hintergrund und Interface Elemente
	WallView wallView;

	
	bool pressed; //!< Variable um zu erkennen ob "Sp�htaste gedr�ckt ist"
	
	//!< Variable umn zu erknnen mit welcher View die Linien angezeigt werden sollen.
	/*!
	 *	0 = CircleLineView, 
	 *	1 = PolyLineView
	 */
	int whichView;	
	bool tracker; //!< Varibale um zu erkennen ob Tracker oder Maus benutzt wird

	// Einkommende Werte der Maus bzw. des Trackers	
	float wX;		//!< X-Wert der Maus bzw. des Tracker
	float wY;		//!< Y-Wert der Maus bzw. des Tracker
	float wZ;		//!< Z-Wert der Maus bzw. des Tracker

	// Monitorkoordinaten (4:3, 16:9, etc.) seperat zuweisen
	float xMin;		//!< kleinster x-Wert der Monitor-/Leinwand-Koordinate
	float xMax;		//!< gr��ter x-Wert der Monitor-/Leinwand-Koordinate
	float yMin;		//!< kleinster y-Wert der Monitor-/Leinwand-Koordinate
	float yMax;		//!< gr��ter y-Wert der Monitor-/Leinwand-Koordinate
	
	float deltaX;	//!< Differenz aus \a xMax und \a xMin
	float deltaY;	//!< Differenz aus \a yMax und \a yMin

	
	float pitch;	//!< Neigungswinkel der Kinect	
	float sinPitch;	//!< sinus von pitch Neigungswinkel der Kinect
	float cosPitch;	//!< cosinus von pitch Neigungswinkel der Kinect
	
	int saveCounter;	//!< Anzahl der Speicherungen
	
	int colorIndex;	//!< Variable um aktuelle Farben zu setzen
	
	int colorCount; //!< Anzahl der Farben der Klasse Color
	
	float trackAry[3];	//!< Array um einkommende Tracker-Werte f�r rechte Hand zuspeichern
	float trackAryLeft[2];	//!< Array um einkommende Tracker-Werte f�r linke Hand zuspeichern
	float trackAryLeftShoulder[2];	//!< Array um einkommende Tracker-Werte f�r linke Schulter zuspeichern
	
	float temp;		//!< x-Startwert zum erkennen der Wischen-Geste
	float delta;	//!< zur�ckgelegter Weg zum erkennen der Wischen-Geste
	float xGeste;	//!< x-Werte zum erkennen der Wischen-Geste
	float yGeste;	//!< y-Werte zum erkennen der Wischen-Geste
	bool leftHand;	//!< Boolean zum erkennen der Wischen-Startgeste

	float zUndoSize;	//new globale z-Ebene f�r Subjekte

	//! Liste f�r die undo() Funktion
		/*!Immer wenn ein Objekt gemalt wird wird zus�tzlich je nach Objekt ein int in den vector gepusht.
		   0 = PolyLine
		   1 = Stamp
		   2 = Circle
		*/
	vector<int> undoList; 

	//!Alle Observer hinzuf�gen(wird in initContext() einmalig aufgerufen)
	void attachObserver(void);

	//!VRPN-Ger�te aktivieren(wird in initContext() einmalig aufgerufen)
	/*!
		* Manuell VRPN-Ger�te aktivieren, jene sind auskommentiert.
		*
		* \sa aktive VRPN-Ger�te  
	*/
	void VRPNGeraete(void);

	//! Test-Funktion zur Gestenerkennung per Maus oder Tracker, �ndern der Hintergrund-Textur
	/*!
		* Die nextTextureGestureMouse-Funktion pr�ft ob Tracker oder Maus-Daten 
		* empfangen werden. Dies geschieht mithilfe vom bool \a tracker. Ist der 
		* Tracker aktiv werden die xy-Werte mit \a coordAdjuTracker() der Leinwand
		* angepasst oder analog falls inaktiv mit \a coordAdjuMouse dem Monitor angepasst.
		* Die Position der Linken Hand, bzw. Maus wird in der y-Achse mit einem Ereignisbereich
		* verglichen. Sobald die Hand im Ereignisbereich erkannt wird beginnt der Gestenstart. 
		* Die Startposition in der x-Achse wird festgehalten, der Bool leftHand wird auf true gesetzt.
		* Dies dient der Erkennung des Gestenstarts, jener wird beim verletzten der Kriterien auf
		* false gesetzt. Der Aufruf der Funktion erfolgt entweder im Sensor-Block des Trackers f�r
		* die linke Hand, oder im handleAnalog f�r die Maus, so erhalten wir die aktuellen
		* y und x-Werte. Gemessen wird der zur�ckgelegte Weg der linken Hand, bzw. Maus im Bezug auf
		* die Startposition in der x-Achse, solange die Hand bzw. Maus immernoch im Ereignisbereich sind. 
		* Ist ein zuvor definierter Abstand erreicht, wird die \a nextTexture() des Hintergrund-Subjekts
		* aufgerufen und der bool leftHand auf false, sowie die Startpostion der Geste in der x-Achse 
		* zur�ck gesetzt. 
		* 
		* \sa nextTextureGestureTracker(), coordAdjuMouse(), coordAdjuTracker(), nextTexture()
	*/
	void nextTextureGestureMouse(void);

	//! Funktion zur Gestenerkennung per Tracker, �ndern der Hintergrund-Textur
	/*!
		* Die nextTextureGestureTracker-Funktion pr�ft ob Tracker oder Maus-Daten 
		* empfangen werden. Dies geschieht mithilfe vom bool \a tracker. Ist der 
		* Tracker aktiv werden die Y-Werte von der linken Hand und linken Schulter
		* verglichen. Zuvor im \a handleTracker() werden diesen Y-Werten die Rotation
		* hinzuaddiert (siehe Kapitel 5: Koordinatentransformationen), so erhalten wir
		* die M�glichkeit die Y-Werte von Hand und Schulter in ihrer H�he zu unterscheiden
		* sobald beide mit einer kleinen Tolleranzgrenze in gleicher H�he gemessen werden,
		* beginnt der Gestenstart. Die Startposition in der x-Achse wird festgehalten,
		* per Aufruf von \a coordAdjuTracker die Bewegung der Leinwand angepasst und 
		* der Bool leftHand wird auf true gesetzt. Dies dient der Erkennung des Gestenstarts,
		* jener wird beim verletzten der Kriterien auf false gesetzt. Der Aufruf der Funktion
		* erfolgt im Sensor-Block des Trackers f�r die linke Hand, so erhalten wir die aktuellen
		* X-Werte. Gemessen wird der zur�ckgelegte Weg der linken Hand im Bezug auf die Startposition
		* in der x-Achse, solange die Hand und Schulter immernoch in gleicher H�he sind. 
		* Ist ein zuvor definierter Abstand erreicht, wird die \a nextTexture() des Hintergrund-Subjekts
		* aufgerufen und der bool leftHand auf false, sowie die Startpostion der Geste in der x-Achse 
		* zur�ck gesetzt. 
		* 
		* \sa nextTextureGestureMouse(), coordAdjuTracker(), nextTexture()
	*/
	void nextTextureGestureTracker(void);

	//! Funktion um den colorIndex vor zuschalten
	/*!
		* Die incNextColorIndex-Funktion schaltet den \a colorIndex um eins weiter.
		* Ist das Ende des Arrayindex bereits erreicht, wird colorIndex wieder
		* auf den kleinsten Arrayindex gesetzt.
		*
		* \param colorIndex int der zur�ckliefert welche Farbe gesetzt wird.
		* \return \a incNextColorIndex() liefert den neuen \a colorIndex zur�ck.
		* \sa nextColor(), decColorIndex()
	*/
	int incColorIndex(int c);

	//! Funktion um den colorIndex zur�ck zuschalten
	/*!
		* Die decColorIndex-Funktion schaltet den \a colorIndex um eins zur�ck.
		* Ist der Anfang des Arrayindex bereits erreicht, wird colorIndex wieder
		* auf den letzten Arrayindex gesetzt.
		*
		* \param colorIndex int der zur�ckliefert welche Farbe gesetzt wird.
		* \return \a decColorIndex() liefert den neuen \a colorIndex zur�ck.
		* \sa previousColor(), incColorIndex()
	*/
	int decColorIndex(int c);

	//!Gibt Anzahl der gemalenten PolyLines aus
	/*!
		* Die printLists-Funktion gibt die Gr��e der Subjektlisten auf der
		* Konsole als String zur�ck.
	*/
	void printLists(void);

	//!L�scht alle gemalten PolyLines
	/*!
		* Die clearAll-Funktion l�scht die Inhalte aller Subjekt-Listen, das aktuelle
		* Subjekt, sowie die Undo-Liste.
		*
		* \sa undo()
	*/
	void clearAll(void);

	//! Funktionen um die Farbe f�r PolyLines und Circles vor zuschalten
	/*!
		* Die nextColor-Funktion ruft die \a incNextColorIndex() auf und erh�lt
		* den neuen Farbindex. Dieser Index wird der neu erzeugten Linie �bergeben
		* und dem Hintergrund-Subjekt wird die aktuelle Farbe mitgeteilt.
		*
		* \param colorIndex int der zur�ckliefert welche Farbe gesetzt wird.
		* \sa nextColor(), incNextColorIndex()
	*/
	void nextColor(void);

	//! Funktionen um die Farbe f�r PolyLines und Circles zur�ck zuschalten
	/*!
		* Die previousColor-Funktion ruft die \a decNextColorIndex() auf und erh�lt
		* den neuen Farbindex. Dieser Index wird der neu erzeugten Linie �bergeben
		* und dem Hintergrund-Subjekt wird die aktuelle Farbe mitgeteilt.
		*
		* \param colorIndex int der zur�ckliefert welche Farbe gesetzt wird.
		* \sa nextColor(), decNextColorIndex()
	*/
	void previousColor(void);

	//! Funktion um einen Kreis zu erstellen
	/*!
		* Die addCircle-Funktion pr�ft ob Tracker oder Maus-Daten empfangen werden.
		* Dies geschieht mithilfe vom bool \a tracker. In Abh�ngigkeit der Daten 
		* werden die Daten entsprechenden umgerechnet und einer neuer \a Circle()
		* wird erstellt, seiner zugeh�rigen Liste �bergeben, an der aktuellen Position
		* gezeichnet und der Undo-Liste als Index = 2 angeh�ngt.
		*
		* \param tracker bool der zur�ckliefert ob Tracker oder Maus-Daten empfangen werden.
		* \sa coordAdjuTracker(), coordAdjuMouse(), addCircle()
	*/
	void addCircle(void);

	//! Funktion um ein Dreieck zu erstellen
	void addTriangle(void);



	//! Funktion um ein Bitmap anzuh�ngen
		/*!
		* Die addStamp-Funktion pr�ft ob Tracker oder Maus-Daten empfangen werden.
		* Dies geschieht mithilfe vom bool \a tracker. In Abh�ngigkeit der Daten 
		* werden die Daten entsprechenden umgerechnet und einer neuer \a Stamp()
		* wird erstellt, seiner zugeh�rigen Liste �bergeben, an der aktuellen Position
		* gezeichnet und der Undo-Liste als Index = 1 angeh�ngt.
		*
		* \param tracker bool der zur�ckliefert ob Tracker oder Maus-Daten empfangen werden
		* \sa coordAdjuTracker(), coordAdjuMouse(), addCircle()
	*/
	void addStamp(void);

	//! Funktion zum Malen, Spr�hmodus aktiv
		/*!
		* Die sprayPressed-Funktion setzt den Boolean pressed auf true und erstellt 
		* eine neue Linie mit dem aktiven Farbindex als Parameter. Anschlie�end teilt 
		* sie dem Observer f�r das aktuelle Liniensubjekt die zu beobachtende Linie mit.
		*
		* \sa sprayReleased()
	*/
	void sprayPressed(void);

	//! Funktion zum Malen, Spr�hmodus inaktiv
		/*!
		* Die sprayReleased-Funktion gibt die aktuelle Linie in die Linienliste weiter.
		* Die aktuelle Linie wird der Undo-Liste als Index = 0 angeh�ngt und der 
		* Boolean pressed wird auf false gesetzt.
		*
		* \sa sprayPressed()
	*/
	void sprayReleased(void);

	//! Funktion zum L�schen des zuletzt erstellten Subjekts
		/*!
		* Die undo-Funktion wird nur ausgef�hrt wenn Subjekte vorhanden sind.
		* Je nach Subjekttyp unterschieden durch int-Zuweisung in der Undo-Liste, wird das dort 
		* zuletzt erstellte Subjekt gel�scht.
		*
		* \sa clearAll()
	*/
	void undo(void);

	//!Umrechnen des Koordinatensystems VRPN-Maus -> Monitor
	/*!
		* Die coordAdjuMouse-Funktion rechnet die erhaltenen 
		* Maus-Daten in unser Koordinatensystem um. 
		* x = \a xMin + \a xY * (\a xMax - \a xMin)
		* y = \a ymin + (1 + \a wY) * (\a yMax - \a yMin)
		* Mithilfe von Bias erhalten wir so die f�r uns relevanten
		* Koordinaten, nicht um Bezug auf den Bildschirm, sondern
		* im Bezug auf unser Koordinatensystem [-3,3], [-4,4].
		* Nach dem Ansatz immer im Verh�ltnis 4:3 die View anzuzeigen.
		*
		* \param chooseVariable boolean zum Steuern der Ausgabe von x oder y
		* \return \a coordAdjuTracker liefert den Transformierten x oder y Wert zur�ck
		* \sa coordAdjuTracker()
	*/

	void coordAdjuMouse(float coords[]); 
	//!Umrechnen des Koordinatensystems VRPN-Tracker(Kinect) -> Leinwand
	/*!
		* Die coordAdjuTracker-Funktion rechnet die erhaltenen 
		* Tracker-Daten in unser Koordinatensystem um. 
		* (siehe Kapitel 5: Koordinatentransformationen)
		* Mithilfe von \a yAnNeigungswinkelAnpassen() wird 
		* die Rotation heraus gerechnet.
		*
		* \param chooseVariable boolean zum Steuern der Ausgabe von x oder y
		* \return \a coordAdjuTracker liefert den Transformierten x oder y Wert zur�ck
		* \sa coordAdjuMouse()
	*/
	//float coordAdjuTracker(bool chooseVariable);

	//! Y-Werte an den Neigungswinkel der Kinect anpassen, z-Rotation hinzuaddieren
	/*!
		* Die yAnNeigungswinkelAnpassen-Funktion rechnet den erhaltenen
		* Rotationsanteil (Neigung der Kinect, Pitchwinkel) in Abh�ngigkeit 
		* zur Z-Postition heraus (siehe Kapitel 5: Koordinatentransformationen)
		*
		* \return \a yAnNeigungswinkelAnpassen liefert den y-Wert, ohne Rotationanteil zur�ck
		* \sa coordAdjuTracker()
	*/
	//float yAnNeigungswinkelAnpassen(void);

	void coordAdju(float[3]);

	//! Funktion zum Bild speichern im DDS-Format in den Buildordner
		/*!
		* Die savePicture-Funktion liest den Framebuffer aus, um so die aktuelle
		* Darstellung abzuspeicern. Mehrmaliges speichern f�hrt dazu das jedes Mal
		* ein Bild im DDS-Format abgespeichert wird. Die Bild-Datei wird dem 
		* Buildordner angeh�ngt.
	*/
	void savePicture(void);

	//!Instanzvariable f�r das Singleton-Muster 
	static GraffitiEngine* instance;

	//! Defaultkontruktor
	GraffitiEngine(void);
};
#endif