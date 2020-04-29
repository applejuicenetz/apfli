/***************************************************************************
 *   Copyright (C) 2004 by Dominic Scharfe,Felix Müller                    *
 *   apfli.sourceforge.net                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef _CONTENT_H
#define _CONTENT_H
#include <vector>
#include <string>
#include <ncurses.h>
#include <panel.h>
#include "../include/Window.h"
#include "../include/Colors.h"
#include "../include/language.h"

using namespace std;


class Content_Item {
  public:
    Content_Item();
    ~Content_Item();
    vector < string > item_cont;
    void (*fptr) (void *plugin);
    //Weisst ENTER Funktion zu
    void set_enter_function(void (*fptr) (void *plugin));
};

class Content_Item_Cache:public Content_Item {
  public:
    int id;
    void set(Content_Item ci) {
	item_cont = ci.item_cont;
    };
};

class Content {
  public:
    Content();
    //Fuehrt zugewiesen ENTER Funktion aus
    void run();

    //Waehlt das vorige Item aus
    void act_up();

    //Waehlt nächste Item aus
    void act_down();

    //Scrollt nach oben
    void scroll_up();

    //Scrollt nach unten
    void scroll_down();

    //Scrollt an Seitenanfang
    void scroll_home();

    //Scrollt an das Seitenende
    void scroll_end();

    //Gibt Content aus,beginnt ganz oben
    void print();

    //Gibt die Itemanzahl zurueck
    int size();

    //Gibt die Zeilenanzahl des mit pos bestimmten Items zurueck
    int size(int &pos);

    //Weisst ENTER Funktion zu
    void set_enter_function(void (*fptr)
			     (int actual_item, void *plugin));

    //Gibt aktuelles Item zurück
    int get_pos();

    //Fuegt neuen Cont hinzu
    void add_item(string val);

    //fuegt zu letzten cont neuen string hinzu
    void add_string(string val);

    //setzt spezifische enter funktion für letztes Item
    void add_enter_funtion(void (*fptr) (void *plugin));

    //Loescht alle Einstellungen
    void clear();

    //Setzt Positionen zurueck
    void reset();

    //Weißt dem Content ein Window und ein Farbe für die ausgewählten Items zu
    void set_win(Window * act_win, Color color);
    Window *get_win() {
	return act_win;
    };


//      static void set_debug(Debug *debug) {Content::debug = debug;};

    void set_act_plugin(void *plugin);

  private:
    void *act_plugin;
    //schreibt string(content) an draw_start_pos und erhoeht diese Variable um 1
    void print_string(string & content, bool mark);

    //schreibt einen Item komplett
    void print_item(unsigned int pos);

    //ENTER Funktion
    void (*fptr) (int actual_item, void *plugin);

    //Löscht Line
    void clear_line(int pos_y);

    void mark_item();
    void unmark_item();

    // aktuelles Item einfaerben (mit color pair -> nr)
    void change_attrib(int nr);

    //Item
    //Aktuelles Item
    unsigned int act_pos;

    //Erste Item was z.Z. sichtbar ist
    unsigned int first_visible_item;

    //Anzahl der derzeit sichtbaren Items
    unsigned int visible_items;

    //Row
    //Anzahl derzeitig sichtbarer Zeilen
    unsigned int visible_rows;

    //derzeitige zu schreibende Zeile
    unsigned int draw_start_pos;

    //Vector der Items
    vector < Content_Item > cont;

    pthread_t *act_thread;

    Window *act_win;

    Color cp_selected_item;


};


#endif
