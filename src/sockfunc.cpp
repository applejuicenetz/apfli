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


#include "../include/sockfunc.h"
//#include "../include/GUI_Settings.h"
#include <iostream>

using namespace std;

int create_socket()
{
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1) {
#ifdef DEBUG_MODE
	cerr << "Socket erstellen fehlgeschlagen" << endl;
#endif
	return 1;
    }
    return s;
}

int connect_core(int &s)
{
    string buff;
    //Verbindungsdaten festlegen
    hostent *he;

    he = gethostbyname((settings_get("main", "socket", "ip")).c_str());
    struct sockaddr_in addr;
    addr.sin_addr = *((in_addr *) he->h_addr);
    addr.sin_port = htons(atoi((settings_get("main", "socket", "port")).c_str()));	//Port
    addr.sin_family = AF_INET;
    //Verbinden zum aJ core
    if (connect(s, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
#ifdef DEBUG_MODE
	cerr << "Verbindung zum Core fehlgeschlagen" << endl;
#endif

	//eventuelle außerhalb der Funktion abfangen um core zu starten
	return 1;
    }
    return 0;
}


string aj_do_xml(string act, string path)
{
    path += "&password=" + settings_get("main", "socket", "passwort");
    int sock = create_socket();
    if (connect_core(sock) == 1) {
	    return NO_CORE_RUNNING;
    }
    string get;
    int rv = 1;
    char buf[1024];

    //HTTP get Anfrage erzeugen
    path = act + " " + path + " HTTP/1.1 \n\n";

    //Anfrage senden an sock
    send(sock, path.c_str(), path.length(), 0);


    //Antwort abfragen
    while (rv != 0) {
	rv = recv(sock, buf, 1024, 0);
	string t;
	t.assign(buf, rv);
	get += t;
    }

    //Antwort zurueckgeben
    close(sock);
    return get;
}
