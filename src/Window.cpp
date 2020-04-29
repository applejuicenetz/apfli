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
#include "../include/Window.h"
#include <iostream>
bool Window::ncurses_initalized = false;

void
 Window::__hline(chtype ch, int n)
{
    whline(handle, ch, n);
}

void Window::__vline(int x, int y, int ch, int n)
{
    mvwvline(handle, y, x, ACS_VLINE, n);
}

void Window::__vline(int x)
{
    __vline(x, 0, 0, __getmaxx());
}


void Window::__addstr(char *str)
{
    waddstr(handle, str);
}

void Window::__addstr(int x, int y, char *str)
{
    mvwaddstr(handle, y, x, str);
    __noutrefresh();
}

void Window::__stdscr_border()
{
    border(0, 0, 0, 0, 0, 0, 0, 0);
}

void Window::init_ncurses()
{
    if (Window::ncurses_initalized == false) {
	initscr();
	start_color();
	init_colors();

	wbkgd(stdscr, COLOR_PAIR(cp_border));
	__stdscr_border();
	ncurses_initalized = true;
    } else {

    }
}

void Window::deinit_ncurses()
{
    ncurses_initalized = false;
    endwin();
}


Window::Window()
{

}

void Window::init(int x, int y, int width, int height, Color color)
{
    create(x, y, width, height);
    set_cols(color);
}

Window::Window(int x, int y, int width, int height, Color color)
{
    init(x, y, width, height, color);
}

bool Window::create(int x, int y, int width, int height)
{
    //debug->out("Window->create");
    keypad(stdscr, TRUE);
    if (width == -1) {
	width = stdscr->_maxx + 1;
    };
    if (height == -1) {
	height = stdscr->_maxy + 1;
    };
    handle = newwin(height, width, y, x);
    if (handle == NULL) {
	y = 0;
	x = 2;
	handle = newwin(height, width, y, x);
    }
    panel = new_panel(handle);
    keypad(handle, TRUE);
    scrollok(handle, true);

    show();
    return true;
}

bool Window::create_sub(int x, int y, int width, int height)
{

    keypad(stdscr, TRUE);
    if (width == -1) {
	width = stdscr->_maxx + 1;
    };
    if (height == -1) {
	height = stdscr->_maxy + 1;
    };
    handle = subwin(stdscr, height, width, y, x);
    panel = new_panel(handle);
    keypad(handle, TRUE);

    show();
    return true;
}

bool Window::create(int x, int y, int width, int height, Color color)
{
    create(x, y, width, height);
    set_cols(color);
    return true;
}

void Window::kill()
{
    delwin(handle);
    handle = NULL;
}

void Window::__mvaddstr(string outstr, int x, int y)
{
	mvwaddnstr(handle, y, x, outstr.c_str(), handle->_maxx-x);
}

void Window::set_cols(unsigned int color_pair)
{
    wbkgd(handle, COLOR_PAIR(color_pair));
    __noutrefresh();
}

void Window::__refresh()
{
    wrefresh(handle);
}

void Window::__noutrefresh()
{
    wnoutrefresh(handle);
}

void Window::force_refresh()
{
    touchwin(handle);
    refresh();
}

void Window::__erase()
{
    werase(handle);
}

void Window::__border()
{
    box(handle, 0, 0);
}

void Window::__border(int a, int b, int c, int d, int e, int f, int g,
		      int h)
{
    wborder(handle, a, b, c, d, e, f, g, h);
}

Window::~Window()
{
    kill();
}

void
 Window::__touch()
{
    touchwin(handle);
}

void Window::redraw_all()
{
    touchwin(stdscr);
}

int Window::__stdscr_getmaxx()
{
    return stdscr->_maxx;
}

int Window::__stdscr_getmaxy()
{
    return stdscr->_maxy;
}

unsigned int Window::__getmaxx()
{
    return handle->_maxx;
}

unsigned int Window::__getmaxy()
{
    return handle->_maxy;
}

void Window::__stdscr_doupdate()
{
    doupdate();
}


void Window::show()
{
    show_panel(panel);
    update_panels();
}

void Window::hide()
{
    hide_panel(panel);
    update_panels();
}

void Window::__attroff(attr_t attrs)
{
    wattroff(handle, attrs);
}

void Window::__attron(attr_t attrs)
{
    wattron(handle, attrs);
}

void Window::__clrtoeol(int x, int y)
{
    //debug->out("Window:clrtoeol");
    if (handle != NULL) {
	wmove(handle, y, x);
    } else {
	//debug->out("Kein Window handle! Wahrscheinlich Content::set_win vergessen");
    }
    wclrtoeol(handle);
}


void Window::__move(int startx, int starty)
{
    move_panel(panel, starty, startx);
}


void Window::set_row(int line, int color_pair)
{
    //cerr<<"set_row:"<<line<<"-"<<color_pair<<endl;
    mvwchgat(handle, line, 0, -1, A_NORMAL, color_pair, NULL);
    touchline(handle, line, __stdscr_getmaxx());
}

void Window::__scrl(int n)
{
    //cerr<<"scrl:"<<n<<endl;
    wscrl(handle, n);
}

void Window::__resize(int lines, int colums)
{
    set_is_resized(true);
    wresize(handle, lines, colums);
}


void Window::__addch(chtype ch)
{
    waddch(handle, ch);
}


void Window::__addch(int x, int y, chtype ch)
{
    mvwaddch(handle, y, x, ch);
}

void Window::__curs_set (unsigned short int i)
{
	curs_set(i);
}
