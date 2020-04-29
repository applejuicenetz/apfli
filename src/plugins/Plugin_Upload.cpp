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

#include "Plugin_Upload.h"

Plugin_Upload::Plugin_Upload()
{
    set_name("Upload");
    core_up.set_get_path("/xml/modified.xml?filter=uploads", true);
}

void
 Plugin_Upload::function()
{

    unsigned int wait_time;
    string buff = get_setting("waittime");
    if (buff == "") {
	set_setting("waittime", DEFAULT_WAIT_TIME);
	wait_time = atoi(DEFAULT_WAIT_TIME);
    } else {
	wait_time = atoi(buff.c_str());
    }

    //cerr << "Plugin_download::function:" << wait_time << endl;
    set_content();
    core_up.init();
    //Sonstige Variablen
    string get, shareid, speed, prio, test;
    char zeile[1000];
    float pwdl;
    long int von, bis, pos;
    int count_active = 0;

    while (running == true) {
	if (Plugin::draw == true) {

	    content->clear();
	    core_up.actual();
	    count_active = 0;
	    //Lade isliste der Uploads
	    vector < string > ullist;
	    core_up.get_id_list(ullist, "upload", "id", NULL, "");
	    unsigned int ulsize = ullist.size();
	    content->add_item(L_UL_ACTIVE);
	    for (unsigned int i = 0; i < ulsize; i++) {
		//Überprüfen ob aktiv ist
		shareid =
		    core_up.get_data("upload", "status",
				     getProp, "id", ullist[i]);
		//Aktiver Upload
		if (shareid == "1") {
		    count_active++;
		    shareid =
			core_up.get_data("upload",
					 "shareid",
					 getProp, "id", ullist[i]);
		    speed = core_up.get_data("upload",
					     "speed",
					     getProp, "id", ullist[i]);
		    prio = core_up.get_data("upload",
					    "priority",
					    getProp, "id", ullist[i]);
		    von = atoi((core_up.
				get_data("upload",
					 "uploadfrom",
					 getProp, "id",
					 ullist[i])).c_str());

		    bis = atoi((core_up.
				get_data("upload",
					 "uploadto",
					 getProp, "id",
					 ullist[i])).c_str());

		    pos = atoi((core_up.
				get_data("upload",
					 "actualuploadposition",
					 getProp, "id",
					 ullist[i])).c_str());

		    if (shareid != "") {
			test = "/xml/getobject.xml?id=" + shareid;
			core_object.set_get_path((char *)
						 test.c_str(), false);
			core_object.init();
			get = core_object.
			    get_data("share",
				     "shortfilename",
				     getProp, "id", (char *)
				     shareid.c_str());
			if (get != "") {
			    //Größe berechnen
			    bis -= von;
			    //schon übertragene Datenmenge berechnen
			    pos -= von;
			    gui_print_dat(buff, pos, bis);
			    gui_print_dat(test, speed, true);
			    pwdl = (atol(prio.c_str()) / 10.00) + 1.00;
			    if (pwdl < 2.2)
				pwdl = 1.0;
			    sprintf(zeile,
				    "%s %s %.1f",
				    buff.c_str(), test.c_str(), pwdl);
			    test = "  ";
			    test += zeile;
			    content->add_item(get);
			    content->add_string(test);
			}
		    }
		}
	    }
	    sprintf(zeile, L_UL_STAT, count_active, ulsize);
	    content->add_string(zeile);
	    ullist.clear();
	    content->print();
	}
	napms(wait_time);
    }
    free_data();
}

void Plugin_Upload::free_data()
{
    core_up.free_data();
    core_object.free_data();
}
