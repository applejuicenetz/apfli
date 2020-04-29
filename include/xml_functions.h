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

#ifndef _XML_FUNCTIONS_H
#define _XML_FUNCTIONS_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>

using namespace std;

enum Parse_Type { getVal, getProp };


	/* Gibt xml zurück
	 * sub_element: cur->name | <appleJuice><subElement>...
	 * value:       unter Wert |((<appleJuice><subElement><value>...)||(<appleJuice><subElement value="x">...))
	 * parse_typ:   wie ist information gespeichert (als Property:getProp;als Value:getVal)
	 * to_test:     welches Property soll auf `id` überprüft werden
	 * id:          Wert auf den getestet werden soll
	 */
string xml_get_data(string & data, string & xml_root, char *sub_element,
		    char *value, Parse_Type parse_type, char *to_test,
		    const string & id);

	/* Erstellt Liste mit allen `values` die in core_data vorkommen
	 * ret:         Liste die zurückgegeben wird
	 * sub_element: cur->name | <appleJuice><subElement>...
	 * value:       Gibt an welcher Wert in die Liste geschrieben wird
	 * to_test:     welches Property soll auf `id` überprüft werden
	 * id:          Wert auf den getestet werden soll
	 */
void xml_get_id_list(string & data, string & xml_root,
		     vector < string > &ret, char *sub_element,
		     char *value, char *to_test, const string & id);
	/* get_node sucht solange in der aktuellen subebene bis es sub_element
	 * gefunden hat. Dort springt es dann hin
	 */
void xml_get_node(xmlNodePtr & cur, char *sub_element, char *to_test,
		  const string & id);
string xml_get_property(xmlNodePtr cur, char *sub_element, char *value,
			char *to_test, const string & id);
string xml_get_value(xmlDocPtr & doc, xmlNodePtr cur, char *sub_element,
		     char *value);

	//Läd Daten in doc und setzt cur auf child von root     
bool xml_init(xmlDocPtr & doc, xmlNodePtr & cur, string & data,
	      string xml_root);
#endif				/* _XML_FUNCTIONS_H */
