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


#ifndef _CCOREDATA_H
#define _CCOREDATA_H

#include "../include/settings.h"
//#include "../include/Debug.h"
#include <string>
#include <libxml/parser.h>
#include <vector>

#ifdef XML_ROOT
#undef XML_ROOT
#endif
#define XML_ROOT			"applejuice"

enum Parse_Type { getVal, getProp };

using namespace std;

bool is_core_running();

//verarbeitet Daten vom Core
class Core_Data {
  public:
    Core_Data();
    /* Legen den Pfad fest
     * use_session darf nur True sein wenn der getPath /xml/modified?... ist
     * evtl noch automatisieren
     */
    Core_Data(char *get_path, bool use_session);
    void set_get_path(char *get_path, bool use_session);

    //aktualisiert Daten vom Core
    void actual();

    /* Gibt Coredaten zurück
     * sub_element: cur->name | <appleJuice><subElement>...
     * value:       unter Wert |((<appleJuice><subElement><value>...)||(<appleJuice><subElement value="x">...))
     * parse_typ:   wie ist information gespeichert (als Property:getProp;als Value:getVal)
     * to_test:     welches Property soll auf `id` überprüft werden
     * id:          Wert auf den getestet werden soll
     */
    string get_data(char *sub_element, char *value,
		    Parse_Type parse_type, char *to_test,
		    const string & id);
    /* Erstellt Liste mit allen `values` die in core_data vorkommen
     * ret:         Liste die zurückgegeben wird
     * sub_element: cur->name | <appleJuice><subElement>...
     * value:       Gibt an welcher Wert in die Liste geschrieben wird
     * to_test:     welches Property soll auf `id` überprüft werden
     * id:          Wert auf den getestet werden soll
     */
    void get_id_list(vector < string > &ret, char *sub_element,
		     char *value, char *to_test, const string & id);

    //Initiert alle Daten
    void init();
    //Löscht alle Daten
    void free_data();

  private:
    /* get_node sucht solange in der aktuellen subebene bis es sub_element
     * gefunden hat.
     */
    void get_node(xmlNodePtr & cur, char *sub_element, char *to_test,
		  const string & id);
    string get_property(xmlNodePtr cur, char *sub_element, char *value,
			char *to_test, const string & id);
    string get_value(xmlDocPtr & doc, xmlNodePtr cur,
		     char *sub_element, char *value);

    bool init_xml(xmlDocPtr & doc, xmlNodePtr & cur, string & data);

    void actual_session();
    void actual_no_session();

    string get_path;
    string core_data;

    string timestamp;
    string session;
    bool use_session;
};


#endif
