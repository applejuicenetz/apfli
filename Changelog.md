bekannte bugs:
- blinkender Cursor beim resizen
- manchmal kommt wenn man edit_settings macht das download fenster
- einige casts in Menu.cpp nicht ISO-C++ conform --> kompilieren mit g++ > 3.4.0 funktioniert nicht

17/08/2004 <Twix>
- Verbesserung in Edit Core Settings

17/08/2004 <dscharfe>
- Os Flag im Makefile entfernt. Binary Groesse ist dadurch um einige kb gewachsen, aber es funktioniert und ein wenig Performancevorteil sollte es bringen
- Scrolling bei Form
- Ein Cursor Bug nach dem resizen wurde behoben

16/08/2004 <dscharfe>
-g++<=2.95 kompatibel gemacht
-warnings entfernt
-Form achtet auf Laenge der idents

16/08/2004 <twix>
Content.cpp
-Bug entfernt
Plugin_Download.cpp
-Download abbrechen implementiert
Form.cpp:
-Anzeige Bug entfern
Apfli.cpp:
-Bug entfernt der u.U. linkprocessing verhindert hat
Plugin_Download.cpp:
-Menue schliessen hinzugefuegt

14/08/2004 <twix>
Content.cpp:
-Scrolling bug gefixed

-settings_ask wurde wieder aktiviert, bis grafische loesung implementiert wurde

13/08/2004
Makefile:
-verbessert (make vom apfli hauptverzeichnis funzt jetzt ordentlich)
-rbin erstellt binary release und rsource source release (erstellt in releases ordner)

Window.cpp (betrifft auch Download):
-__mvaddstr führt mvaddnstr aus sodass immer nur soviel geschrieben wird
 wie ins fenster passt -> das fixt gleich 2 bugs:
     -Downloadscrolling (gab problem, wenn Item Strings zu groß waren)
     -Taskbar: wenn nicht alles draufgepasst hat gabs Anzeigeprobleme

Content.cpp:
-Code verbessert
-unnötigen Code entfernt (z.B.print_item(), wo die hälfte der funktion völlig überflüssig war)

sockfunc.cpp:
-Errorhandler eingebaut -> apfli stürzt jetzt nichtmehr ab wenn der core nicht läuft
---> hab asksettings geändert, es startet jetzt normal das prog wenn keine konfig da is
     und man kann dann das ganze über das settings dings einstellen

Form.cpp:
-Code verbessert

10/08/2004
<d.scharfe>
allgemin:
- viel von deinem miesen Coding Style ausgebessert

Apfli.h/cpp
-MIN_ROWS,MIN_COLS -> einstellbare Mindestgröße des Terminals
-der Signalhandler in der main.cpp hat nurnoch einfluss ein eine bool variablen in der apfli klasse die bestimmt ob resized wird. Dadurch stürzt es auch nicht bei hardcore-resizing ab 
-Probleme beim resizen (grafikfehler danach) teilweise gefixt
	
Edit_Box.cpp:	
-Darstellung optimiert
-(incl. settings.cpp) -> ipv4 feld eintrag
-mit meinem replace script in Form.cpp umgewandelt

Menu.cpp
-Menuegrosse wird jetzt ueber scale_menu generiert (alte methode war ne potentielle fehlerquelle)
-Hintergrund funktioninert ordentlich (der gesuchte Befehl war set_menu_fore - hab ewig in der menu.h gesucht bis ichs zufällig gefunden hab)
-Falls das Terminal zu klein ist und das menü nicht hinpasst (was normalerweise zu nem absturz führt) generierts das menue neu mit den koordinaten x=2, y=0
	
type.cpp/h
-hier kommen alle typen rein
-neuer typ table_t beinhaltet die spaltengroessen einer tabelle (fuer den download)
-> Core_Download_Item.cpp/h modifiziert, dynamische formatierung somit ist es auch möglich zur laufzeit die spaltenbreite zu ändern, etc.


Plugin_Download.cpp
-Formatierte Tabelle, inclusive resize funktion -> tabelle nutzt immer gesamtes fenster aus

Plugin_Main.cpp
-wait_time dazugemacht (btw, das settings system funzt echt gut!)
	
settings:
-napms anstatt sleep -> waittime abjetzt in ms
-stuerzt nichtmehr ab wenn man upload setting verändert

Makefile:
-make rbin erstellt ein binary release (mit installationsscript)

replace script:
-ge-updated
-damit auch die ganzen Namen der Funktionen in der Menu.cpp geändert
