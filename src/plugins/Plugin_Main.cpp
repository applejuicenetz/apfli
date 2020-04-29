/***************************************************************************
 *   Copyright (C) 2004 by Dominic Scharfe,Felix M|ller                    *
 *   www.fd-soft.de.tt                                                     *
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

#include "Plugin_Main.h"

Plugin_Main::Plugin_Main ()
{
	set_name ("Main");
	core_main.set_get_path ("/xml/information.xml?", false);
	core_mod.set_get_path ("/xml/modified.xml?filter=informations",
			       false);
	core_serv.set_get_path ("/xml/modified.xml?filter=server", true);
}

void
Plugin_Main::function ()
{
	set_content ();

	core_main.init ();
	core_mod.init ();
	core_serv.init ();

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


	while (running == true)
	{
		string get;


		content->clear ();
		content->set_enter_function (NULL);

		core_main.actual ();
		core_mod.actual ();
		core_serv.actual ();


		char zeile[2048];

		get = core_main.get_data ("generalinformation", "system",
					  getVal, NULL, "");
		//sprintf(zeile, "Betriebsystem: %s", get.c_str());
		TEST_GET (L_OS, L_NO_OS);
		content->add_item (zeile);

		get = core_main.get_data ("generalinformation", "version",
					  getVal, NULL, "");
		TEST_GET (L_CORE_VERSION, L_NO_CORE);
		content->add_item (zeile);

		get = core_mod.get_data ("networkinfo", "users", getProp,
					 NULL, "");
		TEST_GET (L_USER, L_NO_USER);
		content->add_item (zeile);

		get = core_mod.get_data ("networkinfo", "files", getProp,
					 NULL, "");
		TEST_GET (L_FILES, L_NO_FILES);
		content->add_item (zeile);

		get = core_mod.get_data ("networkinfo", "filesize", getProp,
					 NULL, "");
		TEST_GET (L_SIZE, " ");
		content->add_item (zeile);

		get = core_mod.get_data ("networkinfo",
					 "connectedwithserverid", getProp,
					 NULL, "");

		if (get != "-1")
		{
			get = core_serv.get_data ("server", "name", getProp,
						  "id", get);
		}

		if (get != "-1" && get != "")
		{
			sprintf (zeile, L_SERVER, get.c_str ());

		}
		else
		{
			sprintf (zeile, L_NO_SERVER);
		}
		content->add_item (zeile);

		while (Plugin::draw == false)
		{
			napms (100);
		}

		content->print ();
		napms (wait_time);
	}

}
