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
#include "../include/Content.h"
#include <iostream>
//#include "Plugin.h"
//#include "../include/gui_functions.h"

#define DRAW_START_POS 0

//extern pthread_mutex_t mutex2;
//Debug * Content::debug = NULL;        // fuer Debug Modus

using namespace std;
//extern Debug debug;

void
Content::clear ()
{
	cont.clear ();
	set_enter_function (NULL);
	draw_start_pos = DRAW_START_POS;
//	act_pos = 0;
//	first_visible_item = 0;
}

void
Content::reset ()
{
	draw_start_pos = DRAW_START_POS;
	act_pos = 0;
	first_visible_item = 0;
}


Content::Content ()
{
	clear ();
	reset ();
}

void
Content::run ()
{
	if (fptr != NULL)
	{
		if (cont[act_pos].fptr != NULL)
			cont[act_pos].fptr ((void *) act_plugin);
		else
			fptr (act_pos, (void *) act_plugin);
	}
	cerr << "end Content::run" << endl;
	return;
}


void
Content::change_attrib (int nr)
{
	if (fptr != NULL)
	{
		int line = cont[act_pos].item_cont.size ();
		line *= (act_pos - first_visible_item);
		line += DRAW_START_POS;
		if (act_pos >= first_visible_item
		    && act_pos <= (first_visible_item + visible_items))
		{
			// weil ein item ja mehrere zeilen umfassen kann
			for (unsigned int i = 0;
			     i < cont[act_pos].item_cont.size (); i++)
			{
				act_win->set_row (line + i, nr);
			}
		}
	}
}

void
Content::mark_item ()
{
	change_attrib (cp_selected_item);
}

void
Content::unmark_item ()
{
	change_attrib (cp_main_win);
}

void
Content::act_down ()
{
	if (fptr != NULL)
	{
		if (act_pos < (cont.size () - 1))
		{
			if (first_visible_item + visible_items == act_pos + 1)
				scroll_down ();
			unmark_item ();
			act_pos++;
			mark_item ();
			act_win->__noutrefresh ();
		}
	}
	else
		scroll_down ();
}


void
Content::act_up ()
{
	if (fptr != NULL)
	{
		if (act_pos > 0)
		{
			if (first_visible_item == act_pos)
				scroll_up ();
			unmark_item ();
			act_pos--;
			mark_item ();
			act_win->__noutrefresh ();
		}
	}
	else
		scroll_up ();
}

void
Content::scroll_down ()
{
	int item_to_add = first_visible_item + visible_items;
	if (item_to_add < size ())
	{
		int to_add = cont[item_to_add].item_cont.size ();
		if (act_pos <= first_visible_item && fptr != NULL)
		{
			unmark_item ();
			act_pos = first_visible_item + 1;
			mark_item ();
		}
		act_win->__scrl (to_add);
		if (DRAW_START_POS > 0)
			clear_line (DRAW_START_POS - 1);
		first_visible_item++;
		visible_items--;
		visible_rows -= to_add;
		draw_start_pos = visible_rows + DRAW_START_POS;
		print_item (item_to_add);
		act_win->__noutrefresh ();
	}
}

void
Content::scroll_up ()
{
	if (first_visible_item > 0)
	{
		first_visible_item--;
		int item_to_add = first_visible_item;
		int to_add = cont[item_to_add].item_cont.size ();
		act_win->__scrl (-to_add);
		visible_items--;
		visible_rows -= to_add;
		draw_start_pos = DRAW_START_POS;
		print_item (item_to_add);
		if ((act_pos >= first_visible_item + visible_items)
		    && fptr != NULL)
		{
			unmark_item ();
			act_pos = first_visible_item + visible_items - 1;
			mark_item ();
		}
		act_win->__noutrefresh ();
	}
}

void
Content::scroll_home ()
{
	first_visible_item = 0;
	draw_start_pos = DRAW_START_POS;
	print ();

}

void
Content::scroll_end ()
{
	draw_start_pos = DRAW_START_POS;
//!     first_visible_item = size () - main_win->_maxy;
	print ();
}

int
Content::size ()
{
	return (cont.size ());
}

int
Content::size (int &pos)
{
	if (pos >= 0 && pos < (int) cont.size ())
		return (cont[pos].item_cont.size ());
	return (0);
}

void
Content::set_enter_function (void (*fptr) (int actual_item, void *plugin))
{
	this->fptr = fptr;
}

int
Content::get_pos ()
{
	return act_pos;
}

void
Content::add_item (string val)
{
	Content_Item buf;
	cont.push_back (buf);
	add_string (val);
}

void
Content::add_string (string val)
{
	cont[cont.size () - 1].item_cont.push_back (val);
}

void
Content::add_enter_funtion (void (*fptr) (void *plugin))
{
	cont[cont.size () - 1].set_enter_function (fptr);
}

/*
 *	void Content::print_page (int first_line)
 *
 *	gibt im main_win eine Seite (soviele zeilen, wie auf den Bildschirm passen) aus einem String Vector aus, der als Referenz uebergeben wird.
 *	first_line gibt an, ab welcher zeile die Seite auszugeben ist
 *
 */

void
Content::print ()
{
	visible_items = 0;
	visible_rows = 0;
	draw_start_pos = DRAW_START_POS;
	if (cont.size () == 0)
	{
		string no_it = L_NO_ITEMS;
		print_string (no_it, false);
		visible_rows = 0;
		draw_start_pos = DRAW_START_POS;
	}
	else
	{
		for (int i = first_visible_item; i < size ()
		     && visible_rows <=
		     (act_win->__getmaxy () + DRAW_START_POS); i++)
		{
			print_item (i);
		}

		for (unsigned int i = visible_rows + DRAW_START_POS;
		     i <= act_win->__getmaxy () + DRAW_START_POS; i++)
			clear_line (i);
		mark_item ();
		act_win->__noutrefresh ();
	}
}

void
Content::print_item (unsigned int pos)
{
	int item_cont_size = cont[pos].item_cont.size ();

	for (int i = 0; i < item_cont_size
	     && visible_rows <= act_win->__getmaxy () - DRAW_START_POS; i++)
	{
		print_string (cont[pos].item_cont[i], true);
	}

	visible_items++;
}

void
Content::clear_line (int pos_y)
{
	act_win->__clrtoeol (0, pos_y);
}


void
Content::print_string (string & content, bool mark)
{
	clear_line (draw_start_pos);
	act_win->__mvaddstr (content, 1, draw_start_pos);
	visible_rows++;
	draw_start_pos++;
}

void
Content::set_win (Window * act_win, Color color)
{
	this->act_win = act_win;
	cp_selected_item = color;
}

Content_Item::Content_Item ()
{
	fptr = NULL;
}

Content_Item::~Content_Item ()
{
	item_cont.clear ();
}

void
Content_Item::set_enter_function (void (*fptr) (void *plugin))
{
	this->fptr = fptr;
}

void
Content::set_act_plugin (void *plugin)
{
	act_plugin = plugin;
}
