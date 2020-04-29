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
#include "../include/Apfli.h"
#include "../include/Core_Data.h"

#define DEBUG_MODE

bool
	Apfli::waiting = false;


Apfli::Apfli ()
{
	cerr << "Apfli Konstruktor" << endl;
	init ();
}

Apfli::~Apfli ()
{
	cerr << "Apfli Destruktor" << endl;
	deinit ();
}


bool
Apfli::process_links (int argc, char **argv)
{
	cerr << "process_links" << endl;
	vector < settype_t > settings;
	parse_cmdline (argc, argv, settings);
	string link;
	string path;
	for (unsigned int i = 0; i < settings.size (); i++)
	{
		switch (settings[i].type)
		{
		case set_link:
			for (unsigned int j = 0;
			     j < settings[i].values.size (); j++)
			{
				link = settings[i].values[j];
				for (unsigned int count = 0;
				     count < link.length (); count++)
				{
					if (link[count] == ' ')
						link.replace (count, 1,
							      "%20");

				}
				path = "/function/processlink?link=" + link;
				cerr << "path:" << path << endl;
				path = aj_do_xml ("GET", path);
			}
			return true;
			break;
		case set_version:
			cout << APFLI_VERSION << endl;
			return true;
			break;
		default:
			for (unsigned int j = 0;
			     j < settings[i].values.size (); j++)
			{
				cerr << "settings:" << settings[i].
					values[j] << endl;
			}
			cout << APFLI_HELP << endl;
			return true;
			break;
		}
	}
	cerr << "process_links->ende" << endl;
	return false;
}

void *
msgbar_func (void *argv)
{
	Apfli *apfli = reinterpret_cast < Apfli * >(argv);
	apfli->plug_status->function ();
	return NULL;
}

void
Apfli::init_threads ()
{
	cerr << "Apfli->init_threads:" << endl;
	fkt_thread = new pthread_t;
	msgbar_thread = new pthread_t;
}

void
Apfli::deinit_threads ()
{
	cerr << "Apfli->deinit_threads" << endl;

	pthread_cancel (*fkt_thread);
	pthread_cancel (*msgbar_thread);
	delete fkt_thread;
	delete msgbar_thread;
	fkt_thread = NULL;
	msgbar_thread = NULL;
}

void
Apfli::init_windows ()
{
	cerr << "Apfli->init_windows" << endl;

	// wichtig !!! ncurses stuff initalisieren
	Window::init_ncurses ();

	// Fenster erstellen
	main_win.init (1, 1, Window::__stdscr_getmaxx () - 1,
		       Window::__stdscr_getmaxy () - 2, cp_main_win);
	msgbar_win.init (1, Window::__stdscr_getmaxy () - 1,
			 Window::__stdscr_getmaxx () - 1, 1, cp_msg_win);
}


void
Apfli::deinit_windows ()
{
	cerr << "Apfli->deinit_windows" << endl;
	Window::deinit_ncurses ();
}

void
Apfli::init_plugins ()
{
	cerr << "Apfli->init_plugins" << endl;

	//Plugins
	plug_down = new Plugin_Download;
	plug_down->set_content (main_content);

	plug_about = new Plugin_About;
	plug_about->set_content (main_content);

	plug_lizens = new Plugin_Lizens;
	plug_lizens->set_content (main_content);

	plug_help = new Plugin_Help;
	plug_help->set_content (main_content);

	plug_main = new Plugin_Main;
	plug_main->set_content (main_content);

	plug_edit_settings = new Plugin_Edit_Settings;
	plug_edit_settings->set_content (main_content);

	plug_upload = new Plugin_Upload;
	plug_upload->set_content (main_content);

	plug_status = new Plugin_Status;
	plug_status->set_content (status_content);
}

void
Apfli::deinit_plugins ()
{
	cerr << "Apfli->deinit_plugins" << endl;
	//pthread_cancel (*fkt_thread);

	delete plug_down;
	delete plug_about;
	delete plug_lizens;
	delete plug_help;
	delete plug_main;
	delete plug_edit_settings;
	delete plug_upload;
}

void
Apfli::init_menus ()
{
	cerr << "Apfli->init_menus" << endl;

	Menu::set_thread (fkt_thread);

//    if (is_core_running() == true) {
	main_menu.add_entry (plug_main);
	main_menu.add_entry (plug_down);
	main_menu.add_entry (plug_upload);
//    } else {

//    }

	main_menu.init (2, 0, /*10, 11, */ cp_main_win, L_MAIN);

	settings_menu.add_entry (plug_edit_settings);
	settings_menu.init (21, 0, /*11, 10, */ cp_main_win, L_SETTINGS);

	about_menu.add_entry (plug_about);
	about_menu.add_entry (plug_lizens);
	about_menu.add_entry (plug_help);
	about_menu.init (44, 0, /*10, 11, */ cp_main_win, L_ABOUT);

}

void
Apfli::init_contents ()
{
	cerr << "Apfli->init_contents" << endl;

	//Content
	main_content = new Content;
	main_content->set_win (&main_win, cp_select_item);

	status_content = new Content;
	status_content->set_win (&msgbar_win, cp_select_item);
}

void
Apfli::deinit_contents ()
{
	cerr << "Apfli->deinit_contents" << endl;

	delete main_content;
	main_content = NULL;
	delete status_content;
	status_content = NULL;
}

void
Apfli::init ()
{
	cerr << "Apfli->init" << endl;

	init_threads ();
	init_windows ();
	init_contents ();
	init_plugins ();
	init_menus ();

	pthread_create (msgbar_thread, NULL, msgbar_func, this);
}

void
Apfli::main_loop ()
{
	cerr << "Apfli->main_loop" << endl;

	// damit werden alle Menues gehandled
	Menu *m_act;
	m_act = Menu::get_first ();
	m_act->draw_caption_highlight ();
	m_act->open ();
	m_act->exec_entry ();

	Keyboard keyboard;

	running = true;
	cerr << "Apfli->main_loop->before while" << endl;
	while (running == true)
	{
		if (waiting == true)
		{
			resize ();
			waiting = false;
		}

		if (Plugin::get_handle_keyboard () == true)
		{
			continue;
		}

		keyboard.update ();

		switch (keyboard.get_state (m_act->get_is_open ()))
		{
		case K_EXIT:
			running = false;
			break;

		case K_MENU_EXEC_ENTRY:
			m_act->exec_entry ();
			break;

		case K_MENU_NEXT_ENTRY:
			m_act->next_entry ();
			break;

		case K_MENU_PREV_ENTRY:
			m_act->prev_entry ();
			break;

		case K_MENU_NEXT:
			m_act = m_act->open_next ();
			break;

		case K_MENU_PREV:
			m_act = m_act->open_prev ();
			break;

		case K_MENU_SWAP:
			m_act->swap ();
			break;

		case K_MAIN_NEXT_ITEM:
			Plugin::set_draw (false);	// sollte einen Geschwindigkeitsvorteil geben, ka obs wirklich so ist <dscharfe>
			main_content->act_down ();
			Plugin::set_draw (true);
			break;

		case K_MAIN_PREV_ITEM:
			Plugin::set_draw (false);
			main_content->act_up ();
			Plugin::set_draw (true);
			break;

		case K_MAIN_SCROLL_UP:
			main_content->scroll_up ();
			break;

		case K_MAIN_SCROLL_DOWN:
			main_content->scroll_down ();
			break;

		case K_MAIN_ITEM_EXEC:
			main_content->run ();
			break;
		default:
			break;
		}

		Window::__stdscr_doupdate ();
	}
	cerr << "Apfli->main_loop->ende" << endl;
}

void
Apfli::deinit ()
{
	cerr << "Apfli->deinit" << endl;
	deinit_threads ();
	deinit_contents ();
	deinit_plugins ();
	deinit_windows ();
}

bool
Apfli::term_error ()
{
	struct winsize win;
	ioctl (STDIN_FILENO, TIOCGWINSZ, &win);
	// MIN_COLS und MIN_ROWS siehe Apfli.cpp
	cerr << "cols: " << win.ws_col << endl;
	cerr << "rows: " << win.ws_row << endl;
	if (win.ws_col < MIN_COLS || win.ws_row < MIN_ROWS)
	{
		return true;
	}
	return false;
}

bool
Apfli::resize ()
{
	cerr << "Apfli->resize" << endl;
	clearok (stdscr, true);

	struct winsize win;
	ioctl (STDIN_FILENO, TIOCGWINSZ, &win);
	resizeterm (win.ws_row, win.ws_col);
	wresize (stdscr, win.ws_row, win.ws_col);

	werase (stdscr);

	// MIN_COLS und MIN_ROWS siehe Apfli.cpp
	if (term_error () == true)
		return false;

	Window::__stdscr_border ();

	Menu::resize_menubar ();

	main_win.__resize (Window::__stdscr_getmaxy () - 2,
			   Window::__stdscr_getmaxx () - 1);
	main_win.__erase ();
	msgbar_win.__move (1, Window::__stdscr_getmaxy () - 1);
	msgbar_win.__resize (1, Window::__stdscr_getmaxx () - 1);
	msgbar_win.__erase ();

	main_content->reset ();
	main_content->print ();

	plug_down->resize ();

	//redrawwin(stdscr);
	return true;
}

void
Apfli::stop_main_loop ()
{
	running = false;
}
