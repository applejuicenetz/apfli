/***************************************************************************
 *   Copyright (C) 2004 by Dominic Scharfe, Felix Müller                   *
 *   http://apfli.sourceforge.net                                          *
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
#ifndef MENU_H
#define MENU_H

#include "../include/Window.h"
#include <curses.h>
#include <menu.h>
#include <vector>
#include <string>
#include <panel.h>
#include "../include/Colors.h"
#include <pthread.h>
#include "../include/Plugin.h"
using namespace std;

/**
@author Dominic Scharfe
*/

// Attribut fuer Caption des aktuellen Menues
#define ATTR_HIGHLIGHT	(A_BOLD)

class Menu {
  public:
    Menu();
    ~Menu();

    // noetige Einstellungen machen bevor Menue erstellt wird:
    void set_vars_default();
    void set_caption(char *caption);
    void set_position(int x, int y);
    void set_cols(Color color);

    // Menueeintraege erstellen bevor(!!) es erstellt wird
    void add_entry(Plugin * plugin);
    void add_entry(string caption, void (*fptr) (int argc, void **argv));

    // ruft alle set_funktionen mit dem jeweiligen Parameter auf:
    void init(int x, int y, Color color, char *caption);

    // Namen und zielnfunktionen der einzelnen Menueeintraege setzen
    void init_entries();

    // Menue entgueltig erstellen
    int create();

    // gibt einen Pointer auf das benutzte Window zurueck
    Window *win_handle();

    // aktuelles Menue umschalten (offen->schliessen; geschlossen->oeffnen)
    void swap();
    void open();
    void close();

    bool get_is_open();

    // das logische naechste/vorherige Menue zurueckgeben
    Menu *next();
    Menu *prev();


    // auf naechsten Eintrag im Menue springen
    void next_entry();
    void prev_entry();

    void exec_entry();
    void exec_no_thread(int argc, void **argv);

    // fuers Debuggen
    void show_debug_info();

    // dieses Menue schliessen und naechstes/letztes oeffnen (ausserdem wird
    // ein Pointer auf das naechste bzw. das vorherige zurueckgegeben
    Menu *open_next();
    Menu *open_prev();

    void draw_caption();
    void draw_caption_highlight();
    Plugin *get_act_plugin();

// Statische Funktionen
    // Pointer auf das erste Menue
    static Menu *get_first();

    // Anzahl aller Menues
    static int get_menu_count() {
	return Menu::menu_count;
    };

    static void resize_menubar();

    static void set_thread(pthread_t * thread);

  private:

    // p_next des vorgaengers auf aktuelles Menue setzen und p_prev
    // des aktuellen Menues auf Vorgaenger setzen
    void create_links();

    Window window;
    static Window menubar;	// fuer die menue titel
    static bool menu_initalized;
    ITEM **items;
    unsigned int item_num;
    MENU *menu;
    Menu *p_next;
    Menu *p_prev;
    char *caption;
    static Menu *p_first;
    static Menu *p_last;
    static unsigned int menu_count;
    Color color;
    bool is_open;
    int x, y;
    int width, height;
    PANEL *panel;
    ITEM *act;
    bool is_mainmenu;
    void *(*p) (void *);
    unsigned int act_entry;
    vector < Plugin * >plugins;
    static pthread_t *fkt_thread;
};

#endif
