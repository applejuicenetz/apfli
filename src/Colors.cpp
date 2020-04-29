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
#include "../include/Colors.h"

/*
 * cat /usr/include/curses.h | grep "#define COLOR_"
 * 
 * #define COLOR_BLACK     0
 * #define COLOR_RED       1
 * #define COLOR_GREEN     2
 * #define COLOR_YELLOW    3
 * #define COLOR_BLUE      4
 * #define COLOR_MAGENTA   5
 * #define COLOR_CYAN      6
 * #define COLOR_WHITE     7
 */

void init_colors()
{
    // init_pair(Schriftfarbe, Hintergrundfarbe)
    init_pair(cp_menu, COLOR_CYAN, COLOR_BLUE);	// Menue
    init_pair(cp_main_win, COLOR_BLACK, COLOR_WHITE);	// Fenster indem die Plugins angezeigt werden
    init_pair(cp_border, COLOR_WHITE, COLOR_BLUE);	// "Grosser Rahmen" (vom stdscr)
    init_pair(cp_msg_win, COLOR_CYAN, COLOR_BLACK);	// Farbe der Message Bar
    init_pair(cp_menubar, COLOR_WHITE, COLOR_BLUE);	// sollte == cp_border sein
    init_pair(cp_select_item, COLOR_BLACK, COLOR_CYAN);
}
