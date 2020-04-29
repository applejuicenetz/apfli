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

#include "Plugin_Status.h"

Plugin_Status::Plugin_Status()
{
    set_name("Status");
    core_mod.set_get_path("/xml/modified.xml?filter=informations", false);
}

void
 Plugin_Status::function()
{
    cerr << "Plugin_Status::function"<<endl;
    unsigned int wait_time;
    string buff = get_setting("waittime");
    if (buff == "") {
	set_setting("waittime", DEFAULT_WAIT_TIME);
	wait_time = atoi(DEFAULT_WAIT_TIME);
    } else {
	wait_time = atoi(buff.c_str());
    }

    set_content();
    content->clear();

    core_mod.init();

    
    string get;
    string buffer;

    while (running == true) {
	if (Plugin::draw == true) {
	    core_mod.actual();
	    buffer.erase();
	    content->clear();
	    //UploadSpeed anzeigen

	    get = core_mod.get_data("information", "uploadspeed",
				    getProp, NULL, "");

	    if (get != "") {
		gui_print_dat(buff, get, true);
		buffer = "ULspeed: " + buff;
	    } 
	    //DownloadSpeed anzeigen
	    get = core_mod.get_data("information",
				    "downloadspeed", getProp, NULL, "");
	    if (get != "") {
		gui_print_dat(buff, get, true);
		buffer += " DLspeed: " + buff;
	    }
	    //Credits anzeigen
	    get = core_mod.get_data("information", "credits",
				    getProp, NULL, "");
	    if (get != "") {
		gui_print_dat(buff, get, false);
	    }
	    buffer += " Credits: " + buff;

	    buffer += "   [F10] Beenden";
	    content->add_item(buffer);

	    content->print();
	}
	napms(wait_time);
	//napms(wait_time);
    }
    free_data();
}

void Plugin_Status::free_data()
{
    core_mod.free_data();
}
