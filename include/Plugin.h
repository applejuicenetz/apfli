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
#ifndef PLUGIN_H
#define PLUGIN_H
#include <string.h>
#include <iostream>
#include "../include/Content.h"
#include "../include/settings.h"
using namespace std;


class Plugin
{
      public:
	Plugin ();
	virtual ~ Plugin ();
	void set_name (string name);
	void set_content (Content * content);
	string get_name ()
	{
		return name;
	};

	void set_act ()
	{
		Plugin::act = this;
	};

	static Plugin *get_act ()
	{
		return Plugin::act;
	};
	virtual void function ();

	// fuer Debug Modus
	static void call_func ();
	void set_content ();
	Content *get_content ()
	{
		return content;
	};
	void kill_gentle ();
	static void set_draw (bool draw);
	void set_running (bool running);

	//void set_name(char *name) {strcpy(this->name, name);};
	void set_fptr (void (*fptr) (int argc, void **argv))
	{
		this->fptr = fptr;
	};
	void *get_fptr ()
	{
		return (void *) fptr;
	};

	static bool get_handle_keyboard ()
	{
		return handle_keyboard;
	};

	static void set_handle_keyboard (bool hk)
	{
		handle_keyboard = hk;
	};
	
	void exec (int a, void **b)
	{
		fptr (a, b);
	}

      protected:
	Content * content;
	static bool draw;
	bool running;
	void set_setting (string ident, string value);
	string get_setting (string ident);
	static bool handle_keyboard;

      private:
	string name;
	void (*fptr) (int argc, void **argv);
	static Plugin *act;
};

#define LINK(x) \
	Plugin *pthis = reinterpret_cast<Plugin*>(x);\
	Content *content = pthis->get_content();

#endif
