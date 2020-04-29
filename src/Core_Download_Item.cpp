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

#include "../include/Core_Download_Item.h"
//#include "../include/Debug.h"
using namespace std;
//extern Debug debug;

// name, quellenstatus, uebertragen/filesize, speed, verbleibende zeit, powerdownload
table_t Core_Download_Item::table(30, 15, 20, 15, 12, 6);

string format(char *str, size_t len);
string format(string & str, size_t len);

inline string format(char *str, size_t len)
{
    string ret = str;
    return format(ret, len);
}

inline string format(string & str, size_t len)
{
    size_t spaces = 3;		//spaltenabstand

    string ret = str;

    int dif = len - str.size();

    if (dif > 0) {
	for (size_t i = 0; i < (size_t) dif; i++) {
	    ret += " ";
	}
    } else {
	ret = "";
	for (size_t i = 0; i < len - spaces; i++) {
	    ret += str[i];
	}
	for (size_t i = 0; i < spaces; i++) {
	    ret += " ";
	}

    }
    return ret;
}



Core_Download_Item::Core_Download_Item(Core_Data * core_dl,
				       Core_Data * core_user, string Id,
				       string filename, long int size)
{
    this->core_dl = core_dl;
    this->core_user = core_user;
    this->id = Id;
    this->filename = filename;
    this->size = size;
}


bool Core_Download_Item::actual()
{
//      DEB_MSG("CORE_DL_IT actual start");
    vector < string > statuslist;
    pos =
	atoi(((*core_dl).
	      get_data("download", "ready", getProp, "id", id)).c_str());
    status = (*core_dl).get_data("download", "status", getProp, "id", id);
    string pdl = (*core_dl).get_data("download", "powerdownload", getProp,
				     "id", id);
//      DEB_MSG("CORE_DL_IT before get_list");
    (*core_user).get_id_list(statuslist, "user", "status",
			     "downloadid", id);
    aktivzahl = 0;
    downloadzahl = 0;
    speed = 0;
    quellenzahl = statuslist.size();
//      DEB_MSG("CORE_DL_IT before loop");
//      DEB_MSG(quellenzahl);
    if (quellenzahl > 0) {
	//Errechnet Quellenanzahl in Warteschlange
	for (int j = 0; j < quellenzahl; j++) {
	    if (statuslist[j] == "5") {
		aktivzahl++;
	    } else if (statuslist[j] == "7") {
		aktivzahl++;
		downloadzahl++;
	    }
	}
	//Errechnet Geschwindigkeit des Downloads
	if (downloadzahl > 0) {
	    (*core_user).get_id_list(statuslist, "user",
				     "speed", "downloadid", id);
	    int speedlistcount = statuslist.size();
	    for (int j = 0; j < speedlistcount; j++) {
		speed += atol(statuslist[j].c_str());
	    }
	}
    }
    //Status umwandeln
    if ((status == "0") && (downloadzahl == 0))
	status = L_SEARCH;
    else if (status == "0")
	status = L_LOAD;
    else if (status == "1")
	status = L_FEWMEM;
    else if (status == "12")
	status = L_GETREADY;
    else if (status == "13")
	status = L_WRONGREADY;
    else if (status == "14")
	status = L_READY;
    else if (status == "15")
	status = L_ABORT;
    else if (status == "16")
	status = L_CREATEDATA;
    else if (status == "17")
	status = L_ABBORTED;
    else if (status == "18")
	status = L_PAUSE;
    //PWDL umwandeln
    pwdl = 1.00 + (atol(pdl.c_str()) / 10.00);

    statuslist.clear();
    return (true);
}

string Core_Download_Item::get_filename()
{

    string buf;
    buf = format(filename, table.name);
    return buf;
}

string Core_Download_Item::get_stat()
{
    string ret, buff, buffer;
    char zeile[1024];
    strcpy(zeile, "");

    // status anzeigen
    sprintf(zeile, "%s %i/%i(%i)", (char *) status.c_str(),
	    quellenzahl, aktivzahl, downloadzahl);
    ret = format(zeile, table.sources);

    //uebertragen
    gui_print_dat(buff, pos, size);
    //      ret += buff + get_spaces(buff, table.state);
    ret += format(buff, table.state);

    // powerdownload
    sprintf(zeile, "%.1f", pwdl);
    ret += format(zeile, table.pwdl);

    // speed
    gui_print_dat(buff, speed, true);
    if (speed != 0.00) {
	sprintf(zeile, "%s", buff.c_str());
    } else {
	strcpy(zeile, "");
    }
    //      ret += zeile + get_spaces(buff, table.speed);
    ret += format(zeile, table.speed);

    // verbleibende zeit
    buff = get_remain();
    //      ret += buff + get_spaces(buff, table.timeleft);
    ret += format(buff, table.timeleft);

    return ret;
}


string Core_Download_Item::get_id()
{
    return (id);
}

string Core_Download_Item::get_status()
{
    return (status);
}

string Core_Download_Item::get_remain()
{
    int remain_h = 0;
    int remain_m = 0;

    char zeile[1024];
    strcpy(zeile, "");
    if (speed != 0) {
	remain_m = (size - pos) / (speed * 60);
	while (remain_m > 60) {
	    remain_m -= 60;
	    remain_h++;
	}


	sprintf(zeile, "%dh %dmin", remain_h, remain_m);
    }
    return zeile;
}
