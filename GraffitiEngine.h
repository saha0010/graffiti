#ifndef GRAFFITIENGINE
#define GRAFFITIENGINE


#include "PolyLineView.h"
#include "TriangleView.h"
#include "CircleLineView.h"

/*! Observer für den Hintergrund*/
#include "WallView.h"

/*! Observer für die Stamps*/
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
	 * da aktuelle VRPN-Version keine 2 Verschiedene Button Devices unterstützt)
	 */
	virtual void handleButton(void* userData, const vrpn_BUTTONCB b);

	//!Tracker-Device(Kinect)
    virtual void handleTracker(void* userData, const vrpn_TRACKERCB t);

	//!Tastatur handler von GLUT-Engine(Localhost)
	/* Alle Aktionen die hier definiert sind, 
	 *	können unabhängig davon ob, 
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

	//!View für die Linien Ausgabe als Polylines
	PolyLineView polyLineView;

	//!View für die Stamps(Bitmaps drauf kleben)
	StampView stampView;

	//!View für Kreise
	CircleView circleView;

	//!View für Dreiecke
	TriangleView triangleView;	

	//!View für die im Ausgabe als Kreise
	CircleLineView circleLineView;	

	//!View für den Hintergrund und Interface Elemente
	WallView wallView;

	bool pressed; //!< Variable um zu erkennen ob "Spühtaste gedrückt ist"
	
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
	float xMax;		//!< größter x-Wert der Monitor-/Leinwand-Koordinate
	float yMin;		//!< kleinster y-Wert der Monitor-/Leinwand-Koordinate
	float yMax;		//!< größter y-Wert der Monitor-/Leinwand-Koordinate
	
	float deltaX;	//!< Differenz aus \a xMax und \a xMin
	float deltaY;	//!< Differenz aus \a yMax und \a yMin

	
	float pitch;	//!< Neigungswinkel der Kinect	
	float sinPitch;	//!< sinus von pitch Neigungswinkel der Kinect
	float cosPitch;	//!< cosinus von pitch Neigungswinkel der Kinect
	
	int saveCounter;	//!< Anzahl der Speicherungen
	
	int colorIndex;	//!< Variable um aktuelle Farben zu setzen
	
	int colorCount; //!< Anzahl der Farben der Klasse Color
	
	float trackAry[3];	//!< Array um einkommende Tracker-Werte für rechte Hand zuspeichern
	float trackAryLeft[2];	//!< Array um einkommende Tracker-Werte für linke Hand zuspeichern
	float trackAryLeftShoulder[2];	//!< Array um einkommende Tracker-Werte für linke Schulter zuspeichern
	
	float temp;		//!< x-Startwert zum erkennen der Wischen-Geste
	float delta;	//!< zurückgelegter Weg zum erkennen der Wischen-Geste
	float xGeste;	//!< x-Werte zum erkennen der Wischen-Geste
	float yGeste;	//!< y-Werte zum erkennen der Wischen-Geste
	bool leftHand;	//!< Boolean zum erkennen der Wischen-Startgeste


	float zUndoSize;	//!< uUndoSize entspricht der Größe von undoList.size()

	//! Liste für die undo() Funktion
	/*!Immer wenn ein Objekt gemalt wird wird zusätzlich je nach Objekt ein int in den vector gepusht.
	 *	0 = PolyLine
	 *	1 = Stamp
	 *	2 = Circle
	 */
	vector<int> undoList; 

	//!Alle Observer hinzufügen(wird in initContext() einmalig aufgerufen)
	void attachObserver(void);

	//!VRPN-Geräte aktivieren(wird in initContext() einmalig aufgerufen)
	/*!
		* Manuell VRPN-Geräte aktivieren und neu kompilieren.
		* \sa aktive VRPN-Geräte  
	*/
	void VRPNGeraete(void);

	//! Test-Funktion zur Gestenerkennung per Maus oder Tracker, ändern der Hintergrund-Textur
	/*!
		* Die nextTextureGestureMouse-Funktion prüft ob Tracker oder Maus-Daten 
		* empfangen werden. Dies geschieht mithilfe vom bool \a tracker. Ist der 
		* Tracker aktiv werden die xy-Werte mit \a coordAdjuTracker() der Leinwand
		* angepasst oder analog falls inaktiv mit \a coordAdjuMouse dem Monitor angepasst.
		* Die Position der Linken Hand, bzw. Maus wird in der y-Achse mit einem Ereignisbereich
		* verglichen. Sobald die Hand im Ereignisbereich erkannt wird beginnt der Gestenstart. 
		* Die Startposition in der x-Achse wird festgehalten, der Bool leftHand wird auf true gesetzt.
		* Dies dient der Erkennung des Gestenstarts, jener wird beim verletzten der Kriterien auf
		* false gesetzt. Der Aufruf der Funktion erfolgt entweder im Sensor-Block des Trackers für
		* die linke Hand, oder im handleAnalog für die Maus, so erhalten wir die aktuellen
		* y und x-Werte. Gemessen wird der zurückgelegte Weg der linken Hand, bzw. Maus im Bezug auf
		* die Startposition in der x-Achse, solange die Hand bzw. Maus immernoch im Ereignisbereich sind. 
		* Ist ein zuvor definierter Abstand erreicht, wird die \a nextTexture() des Hintergrund-Subjekts
		* aufgerufen und der bool leftHand auf false, sowie die Startpostion der Geste in der x-Achse 
		* zurück gesetzt. 
		* 
		* \sa nextTextureGestureTracker(), coordAdjuMouse(), coordAdjuTracker(), nextTexture()
	*/
	void nextTextureGestureMouse(void);

	//! Funktion zur Gestenerkennung per Tracker, ändern der Hintergrund-Textur
	/*!
		* Die nextTextureGestureTracker-Funktion prüft ob Tracker oder Maus-Daten 
		* empfangen werden. Dies geschieht mithilfe vom bool \a tracker. Ist der 
		* Tracker aktiv werden die Y-Werte von der linken Hand und linken Schulter
		* verglichen. Zuvor im \a handleTracker() werden diesen Y-Werten die Rotation
		* hinzuaddiert (siehe Kapitel 5: Koordinatentransformationen), so erhalten wir
		* die Möglichkeit die Y-Werte von Hand und Schulter in ihrer Höhe zu unterscheiden
		* sobald beide mit einer kleinen Tolleranzgrenze in gleicher Höhe gemessen werden,
		* beginnt der Gestenstart. Die Startposition in der x-Achse wird festgehalten,
		* per Aufruf von \a coordAdjuTracker die Bewegung der Leinwand angepasst und 
		* der Bool leftHand wird auf true gesetzt. Dies dient der Erkennung des Gestenstarts,
		* jener wird beim verletzten der Kriterien auf false gesetzt. Der Aufruf der Funktion
		* erfolgt im Sensor-Block des Trackers für die linke Hand, so erhalten wir die aktuellen
		* X-Werte. Gemessen wird der zurückgelegte Weg der linken Hand im Bezug auf die Startposition
		* in der x-Achse, solange die Hand und Schulter immernoch in gleicher Höhe sind. 
		* Ist ein zuvor definierter Abstand erreicht, wird die \a nextTexture() des Hintergrund-Subjekts
		* aufgerufen und der bool leftHand auf false, sowie die Startpostion der Geste in der x-Achse 
		* zurück gesetzt. 
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

	//! Funktion um den colorIndex zurück zuschalten
	/*!
		* Die decColorIndex-Funktion schaltet den \a colorIndex um eins zurück.
		* Ist der Anfang des Arrayindex bereits erreicht, wird colorIndex wieder
		* auf den letzten Arrayindex gesetzt.
		*
		* \return --colorIndex
		* \sa previousColor(), incColorIndex()
	*/
	int decColorIndex(void);

	//!Gibt Anzahl der gemalenten PolyLines aus
	/*!
		* Die printLists-Funktion gibt die Größe der Subjektlisten auf der
		* Konsole als String aus.
	*/
	void printLists(void);

	//!Löscht alle gemalten PolyLines
	/*!
		* Die clearAll-Funktion löscht die Inhalte aller Subjekt-Listen, das aktuelle
		* Subjekt, sowie die Undo-Liste.
		*
		* \sa undo()
	*/
	void clearAll(void);

	//! Funktionen um die Farbe für PolyLines und Circles vor zuschalten
	/*!
		* Die nextColor-Funktion ruft die \a incNextColorIndex() auf und erhält
		* den neuen Farbindex. Dieser Index wird der neu erzeugten Linie übergeben
		* und dem Hintergrund-Subjekt wird die aktuelle Farbe mitgeteilt.
		*
		* \sa nextColor(), incNextColorIndex()
	*/
	void nextColor(void);

	//! Funktionen um die Farbe für PolyLines und Circles zurück zuschalten
	/*!
		* Die previousColor-Funktion ruft die \a decNextColorIndex() auf und erhält
		* den neuen Farbindex. Dieser Index wird der neu erzeugten Linie übergeben
		* und dem Hintergrund-Subjekt wird die aktuelle Farbe mitgeteilt.
		*
		* \sa nextColor(), decNextColorIndex()
	*/
	void previousColor(void);

	//! Funktion um einen Kreis zu erstellen
	/*!
		* Die Funktion greift auf die Variable trackAry und liest x,y und z Werte.
		* Es wird ein neues Circle Objekt erzeugt und in die cirleList gepusht.
		* Anschließend wird in der undoList eine 2 angehängt
		* \sa coordAdjuTracker(), coordAdjuMouse(), addCTriangle(), addStamp()
	*/
	void addCircle(void);

	//! Funktion um ein Dreieck zu erstellen
	/*!
		* Die Funktion greift auf die Variable trackAry und liest x,y und z Werte.
		* Es wird ein neues Triangle Objekt erzeugt und in die triangleList gepusht.
		* Anschließend wird in der undoList eine 3 angehängt.
		*
		* \sa coordAdjuTracker(), coordAdjuMouse(), addCircle()
	*/
	void addTriangle(void);

	//! Funktion um ein Bitmap anzuhängen
		/*!
		* Die Funktion greift auf die Variable trackAry und liest x,y und z Werte.
		* Es wird ein neues Triangle Objekt erzeugt und in die triangleList gepusht.
		* Anschließend wird in der undoList eine 1 angehängt.
		*
		* \sa coordAdjuTracker(), coordAdjuMouse(), addCircle(), addTriangle()
	*/
	void addStamp(void);

	//! Funktion zum Malen, Sprühmodus aktiv
		/*!
		* Die sprayPressed-Funktion setzt den Boolean pressed auf true und setzt den colorIndex
		* der Line an lineList[0].
		* \sa sprayReleased()
	*/
	void sprayPressed(void);

	//! Funktion zum Malen, Sprühmodus inaktiv
		/*!
		* Die sparyRelease-Funktion pusht die Line an lineList[0] um eins weiter und stellt sicher,
		* dass lineList[0] bereit für die nächste Line ist.
		* Es wird der Boolean pressed auf false gesetzt.
		* 
		* \sa sprayPressed()
	*/
	void sprayReleased(void);

	//! Funktion zum Löschen des zuletzt erstellten Subjekts
		/*!
		* Die undo-Funktion wird nur ausgeführt wenn Subjekte vorhanden sind.
		* Je nach Subjekttyp unterschieden durch int-Zuweisung in der Undo-Liste, wird das dort 
		* zuletzt erstellte Subjekt gelöscht.
		*
		* \sa clearAll()
	*/
	void undo(void);

	//!Koordinatentranformationen
	/*!
		* Die coordAdjuMouse-Funktion rechnet die erhaltenen 
		* Analog-Daten in unser Koordinatensystem um.
		*
		* \param float array in dem die Koordinaten verändert werden sollen
		* \sa coordAdju(float[3])
	*/
	void coordAdjuMouse(float coords[]); 

	//!Koordinatentranformationen
	/*!
		* Die coordAdjuTracker-Funktion rechnet die erhaltenen 
		* Tracker-Daten in unser Koordinatensystem um und passt den 
		* Pitch der Kinect an.
		*
		* \param float array in dem die Koordinaten verändert werden sollen
		* \sa coordAdjuMouse(float coords[]
	*/
	void coordAdju(float[3]);

	//! Funktion zum Bild speichern im DDS-Format in den Buildordner
		/*!
		* Die savePicture-Funktion liest den Framebuffer aus, um so die aktuelle
		* Darstellung abzuspeicern. Mehrmaliges speichern führt dazu das jedes Mal
		* ein Bild im DDS-Format abgespeichert wird. Die Bild-Datei wird dem 
		* Buildordner angehängt.
	*/
	void savePicture(void);

	//! Funktion zum ändern der View für Lines
		/*!
		 *	 CircleLineView = 0 (Default)
		 *	 PolyLineView	= 1
		 */
	void changeLineView(void);

	//!Instanzvariable für das Singleton-Muster 
	static GraffitiEngine* instance;

	//! Defaultkontruktor
	GraffitiEngine(void);
};
#endif