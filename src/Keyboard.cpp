/***************************************************************************
 *   Copyright (C) 2004 by Dominic Scharfe, Felix Mueller                  *
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
#include "../include/Keyboard.h"
//#include "Screen.h"
//#include "../include/Debug.h"
//#extern Screen screen;
//#extern Debug  debug;


Keyboard::Keyboard()
{
    init();
}


Keyboard::~Keyboard()
{
}

void
 Keyboard::init()
{
    keypad(stdscr, TRUE);
    leaveok(stdscr, TRUE);
    noecho();
    cbreak();
    halfdelay(2);
    curs_set(0);
}

void Keyboard::update()
{
    actual_key = (KEY) getch();
    //debug.out("KEY PRESSED");
}

int Keyboard::get_actual_key()
{
    return actual_key;
}

KEY Keyboard::get_state(bool is_open)
{
    state = K_UNDEFINED;

    // hier tastenabfragen bei denen es egal ist ob
    // das menue offen oder geschlossen ist

    switch (actual_key) {

    case KEY_F(1):
    case KEY_F(2):
	state = K_MENU_SWAP;
	break;

    case KEY_F(10):
    case KEY_F(11):
    case KEY_F(12):
	state = K_EXIT;
	break;

    }

    // hier bei offen/geschlossen

    if (is_open == true) {

	switch (actual_key) {

	case KEY_RIGHT:
	    state = K_MENU_NEXT;
	    break;
	case KEY_LEFT:
	    state = K_MENU_PREV;
	    break;
	case KEY_UP:
	    state = K_MENU_PREV_ENTRY;
	    break;

	case KEY_DOWN:
	    state = K_MENU_NEXT_ENTRY;
	    break;
	case KEY_ENTER:
	    state = K_MENU_EXEC_ENTRY;
	    break;
	}
    } else {
	switch (actual_key) {
	case KEY_UP:
	    state = K_MAIN_PREV_ITEM;
	    break;
	case KEY_DOWN:
	    state = K_MAIN_NEXT_ITEM;
	    break;
	case KEY_NPAGE:
	    state = K_MAIN_SCROLL_DOWN;
	    break;
	case KEY_PPAGE:
	    state = K_MAIN_SCROLL_UP;
	    break;
	case KEY_ENTER:
	    state = K_MAIN_ITEM_EXEC;
	    break;
	}
    }

    actual_key = K_UNDEFINED;

    return state;
}
