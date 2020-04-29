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

#include "../include/xml_functions.h"
using namespace std;

bool
xml_init (xmlDocPtr & doc, xmlNodePtr & cur, string & data, string xml_root)
{
	doc = NULL;
	cur = NULL;
	doc = xmlParseMemory (data.c_str (), data.length ());
	if (doc == NULL)
	{
#ifdef DEBUG_MODE
		cerr << "Dokument nicht richtig geparst" << endl;
#endif
		return false;
	}

	cur = xmlDocGetRootElement (doc);
	if (cur == NULL)
	{
#ifdef DEBUG_MODE
		cerr << "Leeres Dokument" << endl;
#endif
		xmlFreeDoc (doc);
		return false;
	}

	if (xmlStrcmp (cur->name, (const xmlChar *) xml_root.c_str ()))
	{
#ifdef DEBUG_MODE
		cerr << "Dokument ist vom falschen typ" << endl;
#endif
		xmlFreeDoc (doc);
		return false;
	}
	cur = cur->xmlChildrenNode;
	return true;
}


void
xml_get_node (xmlNodePtr & cur,
	      char *sub_element, char *to_test, const string & id)
{
	xmlChar *sonst;
	//cur = cur->xmlChildrenNode;
	//Wenn keine ID gesetzt wurde
	if (to_test == NULL)
	{
		while (cur != NULL)
		{
			if ((!xmlStrcmp
			     (cur->name, (const xmlChar *) sub_element)))
			{
				return;
			}
			cur = cur->next;
		}
		return;
	}
	//Wenn ID gesetzt wurde
	else
	{
		while (cur != NULL)
		{
			if (!xmlStrcmp
			    (cur->name, (const xmlChar *) sub_element))
			{
				sonst = xmlGetProp (cur, (const xmlChar *)
						    to_test);
				if (!xmlStrcmp
				    (sonst, (const xmlChar *) id.c_str ()))
				{
					xmlFree (sonst);
					return;
				}
				xmlFree (sonst);
			}
			cur = cur->next;
		}
	}
	return;
}

string
xml_get_property (xmlNodePtr cur,
		  char *sub_element, char *value, char *to_test,
		  const string & id)
{
	xmlChar *buf;
	string dl;
	if (strcmp (sub_element, ""))
		xml_get_node (cur, sub_element, to_test, id);
	if (cur != NULL)
	{
		buf = xmlGetProp (cur, (const xmlChar *) value);
		if (buf != NULL)
		{
			dl = (char *) buf;
			xmlFree (buf);
			return (dl);
		}
	}
	return ("");
}

string
xml_get_value (xmlDocPtr & doc, xmlNodePtr cur,
	       char *sub_element, char *value)
{
	//cur = cur->xmlChildrenNode->xmlChildrenNode;
	if (strcmp (sub_element, ""))
	{
		xml_get_node (cur, sub_element, NULL, "");
		if (cur != NULL)
		{
			cur = cur->xmlChildrenNode;
		}
		else
			return ("");
	}
	if (strcmp (value, ""))
	{
		xml_get_node (cur, value, NULL, "");
		if (cur == NULL)
		{
			return ("");
		}
	}

	xmlChar *key;
	string dl;
	key = xmlNodeListGetString (doc, cur->xmlChildrenNode, 1);
	dl = (char *) key;
	xmlFree (key);
	return (dl);
}


string
xml_get_data (string & data, string & xml_root, char *sub_element,
	      char *value, Parse_Type parse_type, char *to_test,
	      const string & id)
{
	xmlDocPtr doc = NULL;
	xmlNodePtr cur = NULL;
	string ret;
//-------------------Überprüfung ob Datei korrekt aufgebaut ist---------------------
	if (!xml_init (doc, cur, data, xml_root))
		return ("");
//---------------------------------------------------------------------------------
	//Wenn Wert benötigt wird
	if (parse_type == getVal)
	{
		ret = xml_get_value (doc, cur, sub_element, value);
	}
	else
	{
		ret = xml_get_property (cur, sub_element, value, to_test, id);
	}
	xmlFreeDoc (doc);
	return (ret);
}



void
xml_get_id_list (string & data, string & xml_root, vector < string > &ret,
		 char *sub_element, char *value, char *to_test,
		 const string & id)
{
	ret.clear ();
	xmlChar *buf;
	xmlChar *sonst;
	xmlDocPtr doc = NULL;
	xmlNodePtr cur = NULL;

	if (!xml_init (doc, cur, data, xml_root))
		return;

	if ((to_test == NULL))
	{
		while (cur != NULL)
		{
			if ((!xmlStrcmp
			     (cur->name, (const xmlChar *) sub_element)))
			{
				buf = xmlGetProp (cur,
						  (const xmlChar *) value);
				ret.push_back ((string) ((char *) buf));
				xmlFree (buf);
			}
			cur = cur->next;
		}
	}
	else
	{
		while (cur != NULL)
		{
			if (!xmlStrcmp
			    (cur->name, (const xmlChar *) sub_element))
			{
				sonst = xmlGetProp (cur, (const xmlChar *)
						    to_test);
				if (!xmlStrcmp
				    (sonst, (const xmlChar *) id.c_str ()))
				{
					buf = xmlGetProp (cur,
							  (const xmlChar *)
							  value);
					ret.push_back ((string)
						       ((char *) buf));
					xmlFree (buf);
				}
				xmlFree (sonst);
			}
			cur = cur->next;
		}
	}
	xmlFreeDoc (doc);
	return;
}
