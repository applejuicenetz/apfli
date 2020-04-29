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
#ifndef WINDOW_H
#define WINDOW_H

#include <curses.h>
#include <string>
#include "Colors.h"
#include <panel.h>
//#include "Debug.h"
using namespace std;

/**
Window implementation

@author Dominic Scharfe

!!! Funktionen die ausschliesslich ncursesfunktionen aufrufen beginnen mit __!!!
    sollten diese dazu noch statisch sein beginnen sie mit __stdscr_

*/

class Window {
  public:
    Window();
    Window(int x, int y, int width, int height, Color color);

    ~Window();

    void init(int x, int y, int width, int height, Color color);

    bool create(int x, int y, int width, int height);
    bool create(int x, int y, int width, int height, Color color);
    bool create_sub(int x, int y, int width, int height);
    void set_cols(unsigned int color_pair);
    void set_row(int line, int color_pair);
    void kill();
    void force_refresh();

    void hide();
    void show();

    void __refresh();
    void __noutrefresh();

    void __erase();

    void __addstr(char *str);
    void __addstr(int x, int y, char *str);

    void __attron(attr_t attrs);
    void __attroff(attr_t attrs);

    void __clrtoeol(int x, int y);
    void __scrl(int n);
    void __resize(int lines, int colums);
    void __move(int startx, int starty);
    void __hline(chtype ch, int n);
    void __vline(int x, int y, int ch, int n);
    void __vline(int x);

    void __addch(chtype ch);
    void __addch(int x, int y, chtype ch);

    void __border();
    void __border(int a, int b, int c, int d, int e, int f, int g, int h);
    void __touch();


    unsigned int __getmaxx();
    unsigned int __getmaxy();

    static void __stdscr_border();

    void __mvaddstr(string outstr, int x, int y);

    /*      Statische Funktionen der Window Klasse handlen alle Windows.
     */
    static void init_ncurses();
    static void deinit_ncurses();
    static void redraw_all();
    static void __stdscr_doupdate();
    static int __stdscr_getmaxx();
    static int __stdscr_getmaxy();
	static void __curs_set (unsigned short int i);

    // wird vorrangig gebraucht um menues ein Window zuzuweisen
    WINDOW *get_handle() {
	return handle;
    };
    bool get_is_resized() {
	return is_resized;
    };
    void set_is_resized(bool is) {
	is_resized = is;
    };
  private:
    WINDOW * handle;
    PANEL *panel;
    bool is_resized;
    static bool ncurses_initalized;
};
#endif
