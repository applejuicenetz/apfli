/***************************************************************************
 *   Copyright (C) 2004 by Dominic Scharfe,Felix M�ller                    *
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


#ifndef _SOCKFUNC_H
#define _SOCKFUNC_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "../include/settings.h"

#define closesocket(s) close(s)
#define NO_CORE_RUNNING	"Der Core ist nicht erreichbar"
using namespace std;

/*Socket erstellen
gibt socket identifier zurück
*/
int create_socket();

/*Verbindung zum core aufbauen
ip:ip des Core (nur ip noch keine Namensauflösung
port:XML Port des cores
gibt im erfolgsfall 0 zurück
*/
int connect_core(int &s);
/*Daten abfragen
sock: in connectCore erzeugter Socket
ip:ip des Core (nur ip noch keine Namensauflösung
port:XML Port des cores
path: adfragepfad einschließlich Optionen(Passwort,zip...)
*/
string aj_do_xml(string act, string path);


#endif
