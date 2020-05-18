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
#include "Plugin_Download.h"
#include "../../include/Menu.h"
#include "../../include/Window.h"
#include "../../include/Colors.h"
#include "../../include/Keyboard.h"
using namespace std;


/*
	Dieses Plugin demonstriert verwirrende Pointeraritmetik in formschöner Vollendung
	
	so werden die void pointer gecastet (x ist immer ein void *)
	
	CAST_ACT_ITEM(x)...stellt actual_item zur verfuegung
	CAST_PLUG_DOWN(x)..stellt plug_down, einen Pointer auf das aktuelle Plugin_Download 		   Plugin
	
	so erhaelt man den item vector: (diesmal ist x jedoch schon ein Pointer auf
	Plugin_Download)
	
	CAST_ITEM(x)
	
	Die Makros stehen alle in der header Datei.
	Bitte ausreichend testen und vorsichtig sein, da durch die ständigen Typumwandlungen
	extrem leicht Fehler entstehen.

	Fuer bessere Ideen bin ich jederzeit offen.
	
	<dscharfe>
*/


// Fuer ein item Powerdownload einstellen
void
set_power_download (int argc, void **argv)
{
	CAST_ACT_ITEM (argv[0]);
	CAST_PLUG_DOWN (argv[1]);
	CAST_ITEM (plug_down);
	char temp[5];
	snprintf (temp, 5, "%.1f", item[actual_item].pwdl);
	Form edit_box ("Powerdownload");
	edit_box.add ("Wert:", temp);
	edit_box.set_field_pwdl (0);
	edit_box.init ();
	Plugin::set_handle_keyboard (true);
	string *new_settings = NULL;
	new_settings = edit_box.run ();
	if (new_settings != NULL)
	{			// wenn der OK knopf gedruekt wurde     
		if (new_settings[0] != "")
		{
			plug_down->change_pwdl (actual_item,
						strtod (new_settings[0].
							c_str (), NULL));
		}
	}
	delete[]new_settings;
	Plugin::set_handle_keyboard (false);
	return;
}

// Ein Item pausieren
void
set_pause (int argc, void **argv)
{
	CAST_ACT_ITEM (argv[0]);
	CAST_PLUG_DOWN (argv[1]);
	plug_down->pause_dl (actual_item);
	return;
}

// set_pause fuer jedes item aufrufen
void
set_pause_all (int argc, void **argv)
{
	CAST_PLUG_DOWN (argv[1]);
	plug_down->pause_dl_all ();
	return;
}


void
set_pause_all_except (int argc, void **argv)
{
	CAST_ACT_ITEM (argv[0]);
	CAST_PLUG_DOWN (argv[1]);
	plug_down->pause_dl_all_except (actual_item);
	return;
}


void
set_resume_all (int argc, void **argv)
{
	CAST_PLUG_DOWN (argv[1]);
	plug_down->resume_dl_all ();
	return;
}

void
abort_dl (int argc, void **argv)
{
	CAST_PLUG_DOWN (argv[1]);
	CAST_ACT_ITEM (argv[0]);
	
	Form edit_box (L_DL_ABORT, false);
	edit_box.add (L_DL_ABORT_CONFIRM, "yoa");
	edit_box.set_field_opt (0, O_VISIBLE,false);
	Window::__curs_set(0);
	edit_box.init ();
	Plugin::set_handle_keyboard (true);
	string *new_settings = NULL;
	new_settings = edit_box.run ();
	//Window::__curs_set(1);
	if (new_settings != NULL)
	{			// wenn der OK knopf gedruekt wurde     
		plug_down->abort_dl(actual_item);
	}
	delete[]new_settings;
	Plugin::set_handle_keyboard (false);
	return;
}

void
download_options_menu (int actual_item, void *plugin)
{
	//    LINK (plugin);                // danach ist Plugin * pthis und Content * content verfuegbar 
	//(siehe Plugin.h)
	Keyboard keyboard;

	bool run = true;

#define MENU_WIDTH	30
#define MENU_HEIGHT	10

#define MENU_X		(Window::__stdscr_getmaxx () - MENU_WIDTH)/2
#define MENU_Y		(Window::__stdscr_getmaxy () - MENU_HEIGHT)/2

	//Window win;
	// man koennte auch machen das jenachdem ob das aktuelle item bereits pausiert is
	// es pausieren oder fortsetzen anzeigt

	Menu menu;
	menu.add_entry (L_DL_PAUSE, set_pause);
	menu.add_entry (L_DL_PWDL, set_power_download);
	menu.add_entry (L_DL_PAUSE_ALL, set_pause_all);
	menu.add_entry (L_DL_RESUME_ALL, set_resume_all);
	menu.add_entry (L_DL_PAUSE_ALL_EXCEPT, set_pause_all_except);
	menu.add_entry (L_DL_ABORT, abort_dl);
	menu.add_entry (L_DL_MENU_ABORT, NULL);
	//menu.add_entry (L_DL_DETAILS, NULL);

	menu.init (MENU_X, MENU_Y, /*MENU_WIDTH, MENU_HEIGHT, */ cp_msg_win,
		   "");
	menu.open ();
	cerr << "dl menu open" << endl;
	//win.____noutrefresh();
	//m.show();
	update_panels ();
	doupdate ();

	void *params[2];

	while (run == true)
	{

		keyboard.update ();


		switch (keyboard.get_state (true))
		{
		case K_EXIT:
			run = false;
			break;

		case K_MENU_EXEC_ENTRY:
			params[0] = (void *) actual_item;
			params[1] = plugin;
			menu.exec_no_thread (2, params);
			cerr << "after no thread run" << endl;
			run = false;
			break;

		case K_MENU_NEXT_ENTRY:
			menu.next_entry ();
			break;

		case K_MENU_PREV_ENTRY:
			menu.prev_entry ();
			break;
		default:
			break;
		}

		doupdate ();
	}
	cerr << "bfore menu close" << endl;
	menu.close ();
	return;
	//doupdate();
}

Plugin_Download::Plugin_Download ()
{
	set_name ("Download");
	core_dl.set_get_path ("/xml/modified.xml?filter=down", true);
	core_user.set_get_path ("/xml/modified.xml?filter=user", true);
}

void
Plugin_Download::resize ()
{
	size_t sources = 15;
	size_t state = 20;
	size_t speed = 13;
	size_t timeleft = 10;
	size_t pwdl = 6;

	Window *w = content->get_win ();

	int name =
		w->__getmaxx () - sources - state - speed - timeleft - pwdl;

	if (name < 6)
		name = 6;

	Core_Download_Item::table.set (name, sources, state, speed, timeleft,
				       pwdl);

}

Plugin_Download::~Plugin_Download ()
{
	item.clear ();
}

void
Plugin_Download::function ()
{
	resize ();
	unsigned int wait_time;
	string buff = get_setting ("waittime");
	if (buff == "")
	{
		set_setting ("waittime", DEFAULT_WAIT_TIME);
		wait_time = atoi (DEFAULT_WAIT_TIME);
	}
	else
	{
		wait_time = atoi (buff.c_str ());
	}

	//cerr << "Plugin_download::function:" << wait_time << endl;
	set_content ();

	//Downloads laden
	init ();
//	table_t table = Core_Download_Item::table;

	while (running == true)
	{
		if (Plugin::draw == true)
		{
			get_content (content);
			content->set_enter_function (download_options_menu);
			content->print ();
		}
		napms (wait_time);
	}
	free_data ();
	return;
}

void
Plugin_Download::init ()
{
	core_dl.init ();
	core_user.init ();
	string filename, pos, pdl, status, test;
	item.clear ();
	long int size;
	core_dl.actual ();
	vector < string > dllist;
	core_dl.get_id_list (dllist, "download", "id", NULL, "");
	for (unsigned int i = 0; i < dllist.size (); i++)
	{
		filename =
			core_dl.get_data ("download", "filename", getProp,
					  "id", dllist[i]);
		size = atoi ((core_dl.
			      get_data ("download", "size", getProp, "id",
					dllist[i])).c_str ());
		Core_Download_Item buff (&core_dl, &core_user, dllist[i],
					 filename, size);
		item.push_back (buff);
	}
	return;
}

void
Plugin_Download::get_content (Content * ret)
{
	if (item.size () > 0)
	{
		this->core_dl.actual ();
		this->core_user.actual ();
		ret->clear ();
		vector < Core_Download_Item >::iterator buff;

		for (buff = item.begin (); buff != item.end (); buff++)
		{
			//Abfrage
			if (buff->actual ())
			{
				ret->add_item (buff->get_filename () +
					       buff->get_stat ());
			}
			else
			{
				item.erase (buff);
			}
		}
	}
	return;
}

void
Plugin_Download::change_pwdl (unsigned int pos, double pwdl)
{
	pwdl = (pwdl - 1.00) * 10.00;
	if (pwdl > 490)
		pwdl = 490;
	if (pwdl < 12)
		pwdl = 0;
	string id = item[pos].get_id ();
	char pdl[3];
	sprintf (pdl, "%.0f", pwdl);
	string todo =
		"/function/setpowerdownload?id=" + id + "&Powerdownload=" +
		pdl;
	aj_do_xml ("GET", todo);
	return;
}

void
Plugin_Download::pause_dl (unsigned int pos)
{
	string id = item[pos].get_id ();
	string todo;
	if (item[pos].get_status () == L_PAUSE)
		todo = "/function/resumedownload?id=" + id;
	else
		todo = "/function/pausedownload?id=" + id;
	aj_do_xml ("GET", todo);
	return;
}

void
Plugin_Download::pause_dl_all ()
{
	string id;
	string todo;
	for (unsigned int i = 0; i < item.size (); i++)
	{
		id = item[i].get_id ();
		todo = "/function/pausedownload?id=" + id;
		aj_do_xml ("GET", todo);
	}
	return;
}

void
Plugin_Download::pause_dl_all_except (unsigned int pos)
{
	string id;
	string todo;
	for (unsigned int i = 0; i < item.size (); i++)
	{
		if (i != pos)
		{
			id = item[i].get_id ();
			todo = "/function/pausedownload?id=" + id;
			aj_do_xml ("GET", todo);
		}
	}
	return;
}

void
Plugin_Download::resume_dl_all ()
{
	string id;
	string todo;
	for (unsigned int i = 0; i < item.size (); i++)
	{
		id = item[i].get_id ();
		todo = "/function/resumedownload?id=" + id;
		aj_do_xml ("GET", todo);
	}
	return;
}

void
Plugin_Download::abort_dl (unsigned int pos)
{
	string id = item[pos].get_id ();
	string todo;
	todo = "/function/canceldownload?id=" + id;
	aj_do_xml ("GET", todo);
	return;
}


void
Plugin_Download::free_data ()
{
	core_dl.free_data ();
	core_user.free_data ();
	return;
}
