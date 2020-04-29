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

#ifndef _KEYS_H
#define _KEYS_H

// KEY_ENTER von ncurses scheint nicht zu gehen, darum: <dscharfe>
#ifdef KEY_ENTER
#undef KEY_ENTER
#endif

#define KEY_ENTER 10


enum KEY {
    K_EXIT = 23,		// zufall?!
    K_MENU_SWAP,
    K_MENU_NEXT,
    K_MENU_PREV,
    K_MENU_NEXT_ENTRY,
    K_MENU_PREV_ENTRY,
    K_MENU_EXEC_ENTRY,
    K_MAIN_NEXT_ITEM,
    K_MAIN_PREV_ITEM,
    K_MAIN_SCROLL_UP,
    K_MAIN_SCROLL_DOWN,
    K_MAIN_ITEM_EXEC,
    K_UNDEFINED
};


#endif
