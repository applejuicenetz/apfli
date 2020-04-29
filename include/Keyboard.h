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
#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <curses.h>
#include "keys.h"
//#include "debug.h"
#include "Menu.h"
/**
Keyboard Implementation

@author Dominic Scharfe, Felix Mueller
*/

class Keyboard {
  public:
    Keyboard();
    ~Keyboard();

    void init();
    void update();

    // eventuell performance verschwendung weil is_open immer uebergeben wird
    KEY get_state(bool is_open);
    int get_actual_key();

  private:
    int actual_key;
    //Debug &debug;
    KEY state;
};

#endif
