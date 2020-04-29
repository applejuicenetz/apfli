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

#define DEBUG_MODE
#include "../include/Core_Data.h"
#include "../include/sockfunc.h"
//#include "../include/Debug.h"
#include <string>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>
#include <fstream>
#include <vector>

extern pthread_mutex_t mutex2;

//extern Debug debug;

using namespace std;

#define RESET_CUR1()\
		cur1 = xmlDocGetRootElement (doc1);\
		cur1 = cur1->xmlChildrenNode;\

#define RESET_CUR2()\
		cur2 = xmlDocGetRootElement (doc2);\
		cur2 = cur2->xmlChildrenNode;\

bool
is_core_running ()
{
	if (aj_do_xml ("GET", "/xml/modified.xml") == NO_CORE_RUNNING)
		return false;
	return true;
}


Core_Data::Core_Data (char *get_path, bool use_session)
{
	set_get_path (get_path, use_session);
}

Core_Data::Core_Data ()
{

}

void
Core_Data::set_get_path (char *get_path, bool use_session)
{
	this->get_path = get_path;
	this->use_session = use_session;
}

void
Core_Data::init ()
{
	//session = "111492334";
	if (use_session)
	{
		core_data = aj_do_xml ("GET", "/xml/getsession.xml?");
		core_data = core_data.erase (0, core_data.find ("<", 0));
		session = get_data ("session", "id", getProp, NULL, "");
	}
	core_data = aj_do_xml ("GET", get_path);
	core_data = core_data.erase (0, core_data.find ("<", 0));


	timestamp = get_data ("time", "", getVal, NULL, "");
}

bool
Core_Data::init_xml (xmlDocPtr & doc, xmlNodePtr & cur, string & data)
{
	doc = NULL;
	cur = NULL;
	doc = xmlParseMemory (data.c_str (), data.length ());
	if (doc == NULL)
	{

		cerr << "C_D:" << L_DOC_PARSE_ERROR << endl;

		return false;
	}

	cur = xmlDocGetRootElement (doc);
	if (cur == NULL)
	{

		cerr << "C_D:" << L_EMPTY_DOC << endl;

		xmlFreeDoc (doc);
		return false;
	}

	if (xmlStrcmp (cur->name, (const xmlChar *) XML_ROOT))
	{

		cerr << "C_D:" << L_WRONG_DOC_TYPE << endl;

		xmlFreeDoc (doc);
		return false;
	}
	cur = cur->xmlChildrenNode;
	return true;
}

/*void Core_Data::actual_session()
{

    //            cerr << "C_D:actual_session." << endl;

    string buffer;

    string sub_element;
    string id;

    xmlChar *sonst;
    xmlNodePtr cur_buff;

    xmlDocPtr doc1;
    xmlNodePtr cur1;

    xmlDocPtr doc2;
    xmlNodePtr cur2;
    timestamp = get_data("time", "", getVal, NULL, "");

    //-------------loesche nicht mehr vorhandene Daten--------------------

    //Rufe alle gelöschten ids ab
    buffer = "/xml/modified.xml?filter=ids&timestamp=" + timestamp +
	"&session=" + session;
    buffer = aj_do_xml("GET", buffer);
    buffer = buffer.erase(0, buffer.find("<", 0));

    //cerr<<"delete buffer:"<<buffer<<endl;

    //doc2 und cur2 durchsuchen die 'removed' Liste
    if (!init_xml(doc1, cur1, core_data)
	|| !init_xml(doc2, cur2, buffer)) {
	xmlFreeDoc(doc1);
	xmlFreeDoc(doc2);
	return;
    }
    while (cur2 != NULL) {
	get_node(cur2, "removed", NULL, "");
	if (cur2 == NULL)
	    break;
	id = get_property(cur2, "object", "id", NULL, "");
	while (cur1 != NULL) {
	    sonst = xmlGetProp(cur1, (const xmlChar *) "id");
	    if (!xmlStrcmp(sonst, (const xmlChar *) id.c_str())) {
		xmlUnlinkNode(cur1);
		xmlFreeNode(cur1);
		xmlFree(sonst);
		break;
	    }
	    xmlFree(sonst);
	    cur1 = cur1->next;
	}
	RESET_CUR1();
	cur2 = cur2->next;
    }

    //evtl docs freeen
    xmlFreeDoc(doc2);
    RESET_CUR1()
	//xmlFreeDoc (doc2);
	//----------------------------Aendere Daten----------------------------
	buffer = get_path + "&timestamp=" + timestamp;
    buffer = aj_do_xml("GET", buffer);
    buffer = buffer.erase(0, buffer.find("<", 0));

    //cerr<<"change buffer:"<<buffer<<endl;

    if (!init_xml(doc2, cur2, buffer)) {
	xmlFreeDoc(doc2);
	xmlFreeDoc(doc1);
	return;
    }
    while (cur2 != NULL) {
	sonst = xmlGetProp(cur2, (const xmlChar *) "id");
	if (sonst != NULL) {
	    sub_element = (char *) cur2->name;
	    id = (char *) sonst;
	    xmlFree(sonst);
	    get_node(cur1, (char *) sub_element.c_str(), "id", id);
	    //Wenn id in doc1 vorhanden, dann überschreiben
	    if (cur1 != NULL) {
		cur_buff = cur2;
		cur2 = cur2->next;
		cur1 = xmlReplaceNode(cur1, cur_buff);
		xmlFreeNode(cur1);
	    }
	    //Sonst hinzufügen
	    else {
		cur_buff = cur2;
		cur2 = cur2->next;
		xmlDocCopyNode(cur_buff, doc1, 2);
	    }
	    RESET_CUR1();
	} else
	    cur2 = cur2->next;
    }
    //-----------------------Aktualisiert-timestamp------------------------
    RESET_CUR2();
    get_node(cur2, "time", NULL, "");
    xmlChar *key;
    key = xmlNodeListGetString(doc2, cur2->xmlChildrenNode, 1);
    timestamp = (char *) key;
    xmlFree(key);
    //cerr << "timestamp: "<<timestamp<<endl;
    //---------------------------------------------------------------------
    xmlChar *xml_buff;
    int buffersize;
    xmlDocDumpFormatMemory(doc1, &xml_buff, &buffersize, 1);

    core_data = (char *) xml_buff;
    //cerr<<"buffer:"<<core_data<<endl;
    buffer.clear();


    xmlFree(xml_buff);

    xmlFreeDoc(doc1);
    xmlFreeDoc(doc2);

}*/



void
Core_Data::actual_session ()
{
#ifdef DEBUG_MODE
	cerr << "C_D:actual_session." << endl;
#endif
	string buffer;

	string sub_element;
	string id;

	xmlChar *sonst;
	xmlNodePtr cur_buff;

	xmlDocPtr doc1;
	xmlNodePtr cur1;

	xmlDocPtr doc2;
	xmlNodePtr cur2;
	timestamp = get_data ("time", "", getVal, NULL, "");

	//-------------loesche nicht mehr vorhandene Daten--------------------

	//Rufe alle gelschten ids ab
	buffer = "/xml/modified.xml?filter=ids&timestamp=" + timestamp +
		"&session=" + session;
	buffer = aj_do_xml ("GET", buffer);
	buffer = buffer.erase (0, buffer.find ("<", 0));

	//cerr<<"delete buffer:"<<buffer<<endl;

	//doc2 und cur2 durchsuchen die 'removed' Liste
	if (!init_xml (doc1, cur1, core_data)
	    || !init_xml (doc2, cur2, buffer))
	{
		xmlFreeDoc (doc1);
		xmlFreeDoc (doc2);
		return;
	}
	while (cur2 != NULL)
	{
		get_node (cur2, "removed", NULL, "");
		if (cur2 == NULL)
			break;
		cur2 = cur2->xmlChildrenNode;
		id = get_property (cur2, "object", "id", NULL, "");
		while (cur1 != NULL)
		{
			sonst = xmlGetProp (cur1, (const xmlChar *) "id");
			if (!xmlStrcmp (sonst, (const xmlChar *) id.c_str ()))
			{
				xmlUnlinkNode (cur1);
				xmlFreeNode (cur1);
				xmlFree (sonst);
				break;
			}
			xmlFree (sonst);
			cur1 = cur1->next;
		}
		RESET_CUR1 ();
		cur2 = cur2->next;
	}

	//evtl docs freeen
	xmlFreeDoc (doc2);
	RESET_CUR1 ()
		//xmlFreeDoc (doc2);
		//----------------------------Aendere Daten----------------------------
		buffer = get_path + "&timestamp=" + timestamp;
	buffer = aj_do_xml ("GET", buffer);
	buffer = buffer.erase (0, buffer.find ("<", 0));

	//cerr<<"change buffer:"<<buffer<<endl;

	if (!init_xml (doc2, cur2, buffer))
	{
		xmlFreeDoc (doc2);
		xmlFreeDoc (doc1);
		return;
	}
	while (cur2 != NULL)
	{
		sonst = xmlGetProp (cur2, (const xmlChar *) "id");
		if (sonst != NULL)
		{
			sub_element = (char *) cur2->name;
			id = (char *) sonst;
			xmlFree (sonst);
			get_node (cur1, (char *) sub_element.c_str (), "id",
				  id);
			//Wenn id in doc1 vorhanden, dann |berschreiben
			if (cur1 != NULL)
			{
				cur_buff = cur2;
				cur2 = cur2->next;
				cur1 = xmlReplaceNode (cur1, cur_buff);
				xmlFreeNode (cur1);
			}
			//Sonst hinzuf|gen
			else
			{
				cur_buff = xmlDocCopyNode (cur2, doc1, 1);
				cur2 = cur2->next;
				cur1 = xmlDocGetRootElement (doc1);
				xmlAddChild (cur1, cur_buff);
			}
			RESET_CUR1 ();
		}
		else
			cur2 = cur2->next;
	}
	//-----------------------Aktualisiert-timestamp------------------------
	RESET_CUR2 ();
	get_node (cur2, "time", NULL, "");
	xmlChar *key;
	key = xmlNodeListGetString (doc2, cur2->xmlChildrenNode, 1);
	timestamp = (char *) key;
	xmlFree (key);
	//cerr << "timestamp: "<<timestamp<<endl;
	//---------------------------------------------------------------------
	xmlChar *xml_buff;
	int buffersize;
	xmlDocDumpFormatMemory (doc1, &xml_buff, &buffersize, 1);

	core_data = (char *) xml_buff;
	//cerr<<"buffer:"<<core_data<<endl;
	buffer.erase ();


	xmlFree (xml_buff);

	xmlFreeDoc (doc1);
	xmlFreeDoc (doc2);

}






void
Core_Data::actual_no_session ()
{
	core_data.erase ();
	core_data = aj_do_xml ("GET", get_path);
	core_data = core_data.erase (0, core_data.find ("<", 0));
}

void
Core_Data::actual ()
{
	if (use_session)
		actual_session ();
	else
		actual_no_session ();

}

void
Core_Data::get_node (xmlNodePtr & cur,
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
Core_Data::get_property (xmlNodePtr cur,
			 char *sub_element, char *value,
			 char *to_test, const string & id)
{
	xmlChar *buf;
	string dl;
	get_node (cur, sub_element, to_test, id);
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

string Core_Data::get_value (xmlDocPtr & doc, xmlNodePtr cur,
			     char *sub_element, char *value)
{
	//cur = cur->xmlChildrenNode->xmlChildrenNode;
	get_node (cur, sub_element, NULL, "");
	if (cur != NULL)
	{
		if (strcmp (value, ""))
		{
			cur = cur->xmlChildrenNode;
			get_node (cur, value, NULL, "");
			if (cur == NULL)
			{
				return ("");
			}
		}
	}
	else
	{
		return ("");
	}
	xmlChar *
		key;
	string
		dl;
	key = xmlNodeListGetString (doc, cur->xmlChildrenNode, 1);
	dl = (char *) key;
	xmlFree (key);
	return (dl);
}


string Core_Data::get_data (char *sub_element, char *value,
			    Parse_Type parse_type, char *to_test,
			    const string & id)
{
	xmlDocPtr
		doc = NULL;
	xmlNodePtr
		cur = NULL;
	string
		ret;


//-------------------Überprüfung ob Datei korrekt aufgebaut ist---------------------
	if (!init_xml (doc, cur, core_data))
		return ("");
//---------------------------------------------------------------------------------
	//Wenn Wert benötigt wird
	if (parse_type == getVal)
	{
		ret = get_value (doc, cur, sub_element, value);
	}
	else
	{
		ret = get_property (cur, sub_element, value, to_test, id);
	}
	xmlFreeDoc (doc);
	return (ret);
}

void
Core_Data::get_id_list (vector < string > &ret, char *sub_element,
			char *value, char *to_test, const string & id)
{
	ret.clear ();
	xmlChar *buf;
	xmlChar *sonst;
	xmlDocPtr doc = NULL;
	xmlNodePtr cur = NULL;

	if (!init_xml (doc, cur, core_data))
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

void
Core_Data::free_data ()
{
	core_data.erase ();
	timestamp.erase ();
	session.erase ();
}
