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

//! Anwendungsklasse einer OpenGL-Anwendung mit VRPN-Support
class GraffitiEngine : public vlgVRPNEngine
{
public:
	//!OpenGL Initialisierung
	void initContext(void);

	//!Analog-Device(Maus)
	virtual void handleAnalog(void* userData, const vrpn_ANALOGCB a);

	/*!Button-Devices(Tastatur oder WiiMote muss je nach Device im Code umgeschaltet und neu gebaut werden,
	 * da aktuelle VRPN-Version keine 2 Verschiedene Button Devices unterst�tzt)
	 */
	virtual void handleButton(void* userData, const vrpn_BUTTONCB b);

	//!Tracker-Device(Kinect)
    virtual void handleTracker(void* userData, const vrpn_TRACKERCB t);

	//!Tastatur handler von GLUT-Engine(Localhost)
	/* Alle Aktionen die hier definiert sind, 
	 *	k�nnen unabh�ngig davon ob, 
	 *	Tracker oder Maus eingestellt ist,
	 *	benutzt werden.
	 */
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

	//!Variable einer Linie mit der gearbeitet wird
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

	// Monitorkoordinaten (4:3, 16:9, etc.) seperat im Konstruktor zuweisen 
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


	float zUndoSize;	//!< uUndoSize entspricht der Gr��e von undoList.size()

	//! Liste f�r die undo() Funktion
	/*!Immer wenn ein Objekt gemalt wird wird zus�tzlich je nach Objekt ein int in den vector gepusht.
	 *	0 = PolyLine
	 *	1 = Stamp
	 *	2 = Circle
	 */
	vector<int> undoList; 

	//!Alle Observer hinzuf�gen(wird in initContext() einmalig aufgerufen)
	void attachObserver(void);

	//!VRPN-Ger�te aktivieren(wird in initContext() einmalig aufgerufen)
	/*!
		* Manuell VRPN-Ger�te aktivieren und neu kompilieren.
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
		* \return ++colorIndex
		* \sa nextColor(), decColorIndex()
	*/
	int incColorIndex(void);

	//! Funktion um den colorIndex zur�ck zuschalten
	/*!
		* Die decColorIndex-Funktion schaltet den \a colorIndex um eins zur�ck.
		* Ist der Anfang des Arrayindex bereits erreicht, wird colorIndex wieder
		* auf den letzten Arrayindex gesetzt.
		*
		* \return --colorIndex
		* \sa previousColor(), incColorIndex()
	*/
	int decColorIndex(void);

	//!Gibt Anzahl der gemalenten PolyLines aus
	/*!
		* Die printLists-Funktion gibt die Gr��e der Subjektlisten auf der
		* Konsole als String aus.
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
		* \sa nextColor(), incNextColorIndex()
	*/
	void nextColor(void);

	//! Funktionen um die Farbe f�r PolyLines und Circles zur�ck zuschalten
	/*!
		* Die previousColor-Funktion ruft die \a decNextColorIndex() auf und erh�lt
		* den neuen Farbindex. Dieser Index wird der neu erzeugten Linie �bergeben
		* und dem Hintergrund-Subjekt wird die aktuelle Farbe mitgeteilt.
		*
		* \sa nextColor(), decNextColorIndex()
	*/
	void previousColor(void);

	//! Funktion um einen Kreis zu erstellen
	/*!
		* Die Funktion greift auf die Variable trackAry und liest x,y und z Werte.
		* Es wird ein neues Circle Objekt erzeugt und in die cirleList gepusht.
		* Anschlie�end wird in der undoList eine 2 angeh�ngt
		* \sa coordAdjuTracker(), coordAdjuMouse(), addCTriangle(), addStamp()
	*/
	void addCircle(void);

	//! Funktion um ein Dreieck zu erstellen
	/*!
		* Die Funktion greift auf die Variable trackAry und liest x,y und z Werte.
		* Es wird ein neues Triangle Objekt erzeugt und in die triangleList gepusht.
		* Anschlie�end wird in der undoList eine 3 angeh�ngt.
		*
		* \sa coordAdjuTracker(), coordAdjuMouse(), addCircle()
	*/
	void addTriangle(void);

	//! Funktion um ein Bitmap anzuh�ngen
		/*!
		* Die Funktion greift auf die Variable trackAry und liest x,y und z Werte.
		* Es wird ein neues Triangle Objekt erzeugt und in die triangleList gepusht.
		* Anschlie�end wird in der undoList eine 1 angeh�ngt.
		*
		* \sa coordAdjuTracker(), coordAdjuMouse(), addCircle(), addTriangle()
	*/
	void addStamp(void);

	//! Funktion zum Malen, Spr�hmodus aktiv
		/*!
		* Die sprayPressed-Funktion setzt den Boolean pressed auf true und setzt den colorIndex
		* der Line an lineList[0].
		* \sa sprayReleased()
	*/
	void sprayPressed(void);

	//! Funktion zum Malen, Spr�hmodus inaktiv
		/*!
		* Die sparyRelease-Funktion pusht die Line an lineList[0] um eins weiter und stellt sicher,
		* dass lineList[0] bereit f�r die n�chste Line ist.
		* Es wird der Boolean pressed auf false gesetzt.
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

	//!Koordinatentranformationen
	/*!
		* Die coordAdjuMouse-Funktion rechnet die erhaltenen 
		* Analog-Daten in unser Koordinatensystem um.
		*
		* \param float array in dem die Koordinaten ver�ndert werden sollen
		* \sa coordAdju(float[3])
	*/
	void coordAdjuMouse(float coords[]); 

	//!Koordinatentranformationen
	/*!
		* Die coordAdjuTracker-Funktion rechnet die erhaltenen 
		* Tracker-Daten in unser Koordinatensystem um und passt den 
		* Pitch der Kinect an.
		*
		* \param float array in dem die Koordinaten ver�ndert werden sollen
		* \sa coordAdjuMouse(float coords[]
	*/
	void coordAdju(float[3]);

	//! Funktion zum Bild speichern im DDS-Format in den Buildordner
		/*!
		* Die savePicture-Funktion liest den Framebuffer aus, um so die aktuelle
		* Darstellung abzuspeicern. Mehrmaliges speichern f�hrt dazu das jedes Mal
		* ein Bild im DDS-Format abgespeichert wird. Die Bild-Datei wird dem 
		* Buildordner angeh�ngt.
	*/
	void savePicture(void);

	//! Funktion zum �ndern der View f�r Lines
		/*!
		 *	 CircleLineView = 0 (Default)
		 *	 PolyLineView	= 1
		 */
	void changeLineView(void);

	//!Instanzvariable f�r das Singleton-Muster 
	static GraffitiEngine* instance;

	//! Defaultkontruktor
	GraffitiEngine(void);
};
#endif