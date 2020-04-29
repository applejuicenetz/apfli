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
#include "../include/Menu.h"

using namespace std;
pthread_t *Menu::fkt_thread = NULL;
bool Menu::menu_initalized = false;
Window Menu::menubar;

Menu *Menu::p_first = NULL;
Menu *Menu::p_last = NULL;
unsigned int
 Menu::menu_count = 0;

void
 Menu::resize_menubar()
{
    menubar.__resize(Window::__stdscr_getmaxy() - 1,
		     Window::__stdscr_getmaxx() - 1);
    whline(menubar.get_handle(), 0, menubar.__getmaxx());
    Menu *m = get_first();

    menubar.show();

    while (m != NULL) {
	if (m->is_open == false) {
	    m->draw_caption();
	} else {
	    m->draw_caption_highlight();
	}
	m = m->p_next;
    }
}



void Menu::set_caption(char *caption)
{
    cerr << "set_caption: " << caption << endl;
    this->caption = new char[strlen(caption) + 1];
    strcpy(this->caption, caption);
}

void Menu::set_position(int x, int y)
{
    cerr << "set_position: " << x << "|" << y << endl;
    this->x = x;
    this->y = y;
}

void Menu::set_cols(Color color)
{
    cerr << "set_cols" << endl;
    this->color = color;
}

void Menu::init(int x, int y, Color color, char *caption)
{
    cerr << "menu->init(): " << caption << endl;

    if (Menu::menu_initalized == false) {
	menubar.create(1, 0, window.__stdscr_getmaxx() - 1, 1, cp_border);
	whline(menubar.get_handle(), 0, menubar.__stdscr_getmaxx());
	Menu::menu_initalized = true;
    }

    set_vars_default();
    set_caption(caption);
    set_position(x, y);
    set_cols(cp_border);
    init_entries();

    create();

    window.__border();
    post_menu(menu);
    draw_caption();
    window.hide();
}

Menu::Menu()
{

};

void
 Menu::set_vars_default()
{
    act_entry = 0;
    x = 0;
    y = 0;
    width = 15;
    height = 15;
    color = cp_main_win;
    p_next = NULL;
    p_prev = NULL;
    is_open = false;

}

void Menu::set_thread(pthread_t * thread)
{
    fkt_thread = thread;
}

int Menu::create()
{
    cerr << "Menu->create" << endl;
    menu = new_menu((ITEM **) items);
    int rows, cols;
    scale_menu(menu, &rows, &cols);

    // falls menuecaption gross ist (das +4 ist wegen dem '[F1]'
    if ((size_t) cols < strlen(caption) + 4)
	cols = strlen(caption) + 4;

    window.create(x, y, cols + 8, rows + 2, color);
    set_menu_win(menu, window.get_handle());
    set_menu_sub(menu, derwin(window.get_handle(), rows, cols + 6, 1, 1));
    set_menu_mark(menu, " * ");
    set_menu_back(menu, COLOR_PAIR(cp_border) | A_BOLD);
    set_menu_fore(menu, COLOR_PAIR(cp_border) | A_BOLD | A_REVERSE);
    return 0;
}

void Menu::open()
{
    is_open = true;
    Plugin::set_draw(false);
    plugins[act_entry]->set_draw(false);
    window.show();
    draw_caption_highlight();
}

void Menu::close()
{
    window.hide();
    menubar.show();
    is_open = false;
    Plugin::set_draw(true);
    plugins[act_entry]->set_draw(true);
}

Menu::~Menu()
{
    delete[]caption;
}

Window *Menu::win_handle()
{
    return &window;
}


void Menu::next_entry()
{
    if (act_entry < plugins.size()) {
	act_entry++;
	menu_driver(menu, REQ_DOWN_ITEM);
	window.__refresh();
    }

}

void Menu::prev_entry()
{
    if (act_entry > 0) {
	act_entry--;
	menu_driver(menu, REQ_UP_ITEM);
	window.__noutrefresh();
    }
}

void Menu::draw_caption()
{
    mvwhline(menubar.get_handle(), 0, x, 0, window.__getmaxx());
    int pos = (window.__getmaxx() - strlen(caption)) / 2;
    menubar.__addstr(x + pos, y, caption);
}

void Menu::draw_caption_highlight()
{
    int pos;
    char *caption2 = new char[strlen(caption) + 5];
    //  strcpy(caption2,"[F1]");
    strcpy(caption2, caption);
    pos = (window.__getmaxx() - strlen(caption2)) / 2;
    menubar.__attron(ATTR_HIGHLIGHT);
    menubar.__addstr(x + 1, y, "[F1]");
    menubar.__addstr(x + pos, y, caption2);
    menubar.__attroff(ATTR_HIGHLIGHT);
    delete[]caption2;
}



void Menu::create_links()
{
    // huebsche Zeigerarithmetik (C) D.Scharfe
    /*
     * p_next und p_prev Zeiger des vorherigen Menues wird umgebogen
     */

    if (Menu::menu_count == 0) {	// dieses ist das ertse Menue
	Menu::p_first = this;
    } else {
	this->p_prev = Menu::p_last;
	Menu::p_last->p_next = this;
    }
    Menu::p_last = this;
}

void Menu::init_entries()
{
    cerr << "init_entries" << endl;
    item_num = Menu::plugins.size();
    items = new ITEM *[item_num + 1];	//+1?
    for (unsigned int i = 0; i < item_num; ++i) {
	plugins[i]->set_act();
	void (*p) ();
	p = Plugin::call_func;

	items[i] = new_item((plugins[i]->get_name()).c_str(), "");
	set_item_userptr(items[i], (void *) p);
    }
    items[item_num] = (ITEM *) NULL;

    create_links();
    Menu::menu_count++;
}


void Menu::add_entry(Plugin * plugin)
{
    plugins.push_back(plugin);
    cerr << "add_entry: " << plugin->get_name() << endl;
}

void Menu::add_entry(string caption, void (*fptr) (int argc, void **argv))
{
    Plugin *plugin = new Plugin;
    plugin->set_name((char *) caption.c_str());
    plugin->set_fptr(fptr);

    //      cerr << "FPTR: " << fptr << endl;

    add_entry(plugin);
}

Menu *Menu::get_first()
{
    return Menu::p_first;
}


Menu *Menu::next()
{
    if (p_next == NULL) {
	return Menu::p_first;
    }
    return p_next;
}

Menu *Menu::prev()
{
    if (p_prev == NULL) {
	return Menu::p_last;
    }
    return p_prev;
}

void Menu::swap()
{
    if (is_open == true) {
	close();
    } else {
	open();
    }
}

void Menu::show_debug_info()
{
    cerr << "adresse: " << this << endl;
    cerr << "prev   : " << this->p_prev << endl;
    cerr << "next   : " << this->p_next << endl;
    cerr << "is_open: ";
    if (is_open == false) {
	cerr << "false";
    } else {
	cerr << "true";
    }
    cerr << endl;
}


Menu *Menu::open_next()
{
    draw_caption();
    close();
    next()->open();
    next()->draw_caption_highlight();
    return next();
}

Menu *Menu::open_prev()
{
    draw_caption();
    close();
    prev()->open();
    prev()->draw_caption_highlight();
    return prev();

}

bool Menu::get_is_open()
{
    return is_open;
}

Plugin *Menu::get_act_plugin()
{
    return Plugin::get_act();
}

void Menu::exec_entry()
{
    plugins[act_entry]->set_act();
    plugins[act_entry]->set_running(true);

    // Pointer auf die Menuefunktion
    (void *) p = item_userptr(current_item(menu));
	//(void *) p = (plugins[act_entry]->get_fptr());

    if (p != NULL && fkt_thread != NULL) {
	//thread beenden signal schicken
	pthread_cancel(*fkt_thread);

	//Warten bis Thread beendet ist
	pthread_join(*fkt_thread, NULL);

	// erstelle neuen thread mit der funktion des menue eintrages
	pthread_create(fkt_thread, NULL, p, NULL);

	pos_menu_cursor(menu);
	close();
    }
}


void Menu::exec_no_thread(int argc, void **argv)
{
	/*
    void (*p) (int argc, void **argv);
    (void *) p = plugins[act_entry]->get_fptr();
    if (p != NULL) {
	p(argc, argv);
    }
	*/
	void (*p);// (int argc, void **argv);
    p = (plugins[act_entry]->get_fptr());
    
    if (p != NULL) {
    plugins[act_entry]->exec(argc,argv);
    }
}
