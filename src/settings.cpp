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
#include "../include/settings.h"
#include "../include/Plugin.h"
#include "plugins/Plugin_Edit_Settings.h"
#include "../include/xml_functions.h"
#include "../include/Form.h"
#include "../include/sockfunc.h"

#define DEBUG_MODE

#define BUF_LEN_ 20
#define UMRECHNEN1()\
		first = atoi(buffer.c_str());\
		first = first / 1024.0;\
		buff;\
		snprintf (buff, BUF_LEN_, "%.1f", first);

#define UMRECHNEN2(buffer)\
		first = atoi(buffer.c_str());\
		first = first * 1024.0;\
		buff;\
		snprintf (buff, BUF_LEN_, "%.0f", first);

static int last_item = 0;

string
getfile ()
{
	string file;

	file = getenv ("HOME");
	file += '/';
	file += ".apfli/settings";

	return (file);
}

bool
settings_init ()
{
	ifstream setfile;
	setfile.open ((char *) (getfile ()).c_str ());
	//free (file);
	if (setfile == NULL)
	{

		cerr << "setfile == NULL" << endl;

		settings_buffer =
			"<?xml version=\"1.0\"?>\n<" + (string) XML_ROOT +
			">\n</" + (string) XML_ROOT + ">";
		return false;
	}


	string buf;

	while (setfile.good ())
	{
		buf = "";
		setfile >> buf;
		settings_buffer += buf + "\n";
	}

	setfile.close ();
	return true;
}


bool
settings_init_xml (xmlDocPtr & doc, xmlNodePtr & cur)
{
	doc = NULL;
	cur = NULL;
	doc = xmlParseMemory (settings_buffer.c_str (),
			      settings_buffer.length ());

	if (doc == NULL)
	{
		cerr << "settings_init_xml: Document not parsed successfully."
			<< endl;
		doc = xmlNewDoc ((xmlChar *) "1.0");
		cur = xmlNewDocNode (doc, NULL, (xmlChar *) XML_ROOT, NULL);
		xmlDocSetRootElement (doc, cur);
		//return false;
	}

	cur = xmlDocGetRootElement (doc);
	if (cur == NULL)
	{
		cerr << "settings_init_xml: Empty Document." << endl;
		xmlFreeDoc (doc);
		return false;
	}

	if (xmlStrcmp (cur->name, (const xmlChar *) XML_ROOT))
	{
		cerr << "settings_init_xml: wrong Type." << endl;
		xmlFreeDoc (doc);
		return false;
	}
	return true;
}

void
settings_save ()
{

	xmlDocPtr doc1;
	xmlNodePtr cur1;

	settings_init_xml (doc1, cur1);
	xmlSaveFile ((char *) (getfile ()).c_str (), doc1);
	xmlFreeDoc (doc1);
	xmlCleanupParser ();
}

void
settings_get_node (xmlNodePtr & cur, char *sub_element)
{
	//xmlChar *sonst;
	//cur = cur->xmlChildrenNode;
	//Wenn keine ID gesetzt wurde

	while (cur != NULL)
	{
		if ((!xmlStrcmp (cur->name, (const xmlChar *) sub_element)))
		{
			return;
		}
		cur = cur->next;
	}
	return;
}

void
settings_set (string topic, string name, string ident, string value)
{
	cerr << "settings_set" << endl;

	xmlDocPtr doc1;
	xmlNodePtr cur1;
	xmlNodePtr last_node;
	settings_init_xml (doc1, cur1);
	last_node = cur1;
	cur1 = cur1->xmlChildrenNode;


	settings_get_node (cur1, (char *) topic.c_str ());
	//Geh zu topoc(<main>
	if (cur1 == NULL)
	{

		cur1 = xmlNewChild (last_node, NULL,
				    BAD_CAST (char *)topic.c_str (), NULL);

		cur1 = xmlNewChild (cur1, NULL,
				    BAD_CAST (char *)name.c_str (), NULL);
	}
	else
	{
		last_node = cur1;
		cur1 = cur1->xmlChildrenNode;

		if (cur1 == NULL)
		{
			cur1 = xmlNewChild (last_node, NULL,
					    BAD_CAST (char *)name.c_str (),
					    NULL);
		}
		else
		{
			//last_node = cur1;
			settings_get_node (cur1, (char *) name.c_str ());
			if (cur1 == NULL)
			{
				cur1 = xmlNewChild (last_node, NULL,
						    BAD_CAST (char *)name.
						    c_str (), NULL);
			}
		}
	}

	xmlSetProp (cur1, BAD_CAST ident.c_str (), BAD_CAST value.c_str ());

	xmlChar *xml_buff;
	int buffersize;
	xmlDocDumpMemory (doc1, &xml_buff, &buffersize);
	settings_buffer = (char *) xml_buff;

	xmlFree (xml_buff);
	/*free the document */


	xmlFreeDoc (doc1);

}

string
settings_get (string topic, string name, string ident)
{
	xmlDocPtr doc1;
	xmlNodePtr cur1;
	xmlChar *buf;
	string dl;

	settings_init_xml (doc1, cur1);
	cur1 = cur1->xmlChildrenNode;
	if (cur1 == NULL)
	{
		xmlFreeDoc (doc1);
		return ("");
	}

	settings_get_node (cur1, (char *) topic.c_str ());
	if (cur1 == NULL)
	{
		xmlFreeDoc (doc1);
		return ("");
	}

	cur1 = cur1->xmlChildrenNode;

	if (cur1 == NULL)
	{
		xmlFreeDoc (doc1);
		return ("");
	}

	settings_get_node (cur1, (char *) name.c_str ());

	if (cur1 == NULL)
	{
		xmlFreeDoc (doc1);
		return ("");
	}

	if (cur1 != NULL)
	{
		buf = xmlGetProp (cur1, (const xmlChar *) ident.c_str ());
		if (buf != NULL)
		{
			dl = (char *) buf;
			xmlFree (buf);
			xmlFreeDoc (doc1);
			return (dl);
		}
	}
	xmlFreeDoc (doc1);
	//mlCleanupParser();
	return ("");

}


void
cast (string str, int &ret)
{
	ret = atoi (str.c_str ());
}

void
settings_set_pt_pw (string password)
{
	unsigned char sig[MD5_SIZE];
	char str[33];
	md5_buffer ((char *) password.c_str (), password.length (), sig);
	md5_sig_to_string (sig, str, sizeof (str));
	settings_set ("main", "socket", "passwort", (string) str);
}


void
settings_ask ()
{
/*	settings_set ("main", "socket", "ip", DEFAULT_IP);
	settings_set_pt_pw (DEFAULT_PW);
	settings_set ("main", "socket", "port", DEFAULT_PORT);
	settings_set ("main", "socket", "ajcore", DEFAULT_AJCORE);

	return;
*/
	string answer;
	cout << L_NO_CONFIG << endl;
	cout << L_ASK_CONFIG << " :";
	cin >> answer;
	if (answer == L_YES_CHAR)
	{
		//Wenn IP nicht gesetzt wurde
		if (settings_get ("main", "socket", "ip") == "")
		{
			cout << L_NO_IP << DEFAULT_IP << ")\n";
			cin >> answer;
			if (answer != "")
				settings_set ("main", "socket", "ip", answer);
		}
		//Wenn Passwort nicht gesetzt wurde
		if (settings_get ("main", "socket", "passwort") == "")
		{
			cout << L_NO_PW << DEFAULT_PW << ")\n";
			cin >> answer;
			if (answer != "")
				settings_set_pt_pw (answer);
		}
		//Wenn Port nicht gesetzt wurde
		if (settings_get ("main", "socket", "port") == "")
		{
			cout << L_NO_PORT << DEFAULT_PORT << ")\n";
			cin >> answer;
			if (answer != "")
				settings_set ("main", "socket", "port",
					      answer);
		}

/*		// Ajcore Pfad
		if (settings_get ("main", "socket", "ajcore") == "")
		{
			cout << "AJ startkomando (" << DEFAULT_AJCORE
				<< ")\n";
			cin >> answer;
			if (answer != "")
				settings_set ("main", "socket", "ajcore",
					      answer);
		}
*/
		settings_set ("main", "socket", "ajcore", DEFAULT_AJCORE);

	}
}

int
parse_cmdline (int argc, char **argv, vector < settype_t > &settings)
{
	settype_t set;
	const char *cmd_types[] =
		{ CMD_TYPE_PW, CMD_TYPE_LINK, CMD_TYPE_VERSION };

	cerr << "Parse Command Line argc:" << argc << endl;
	int ind = -1;

	for (int i = 1; i < argc; i++)
	{

		if (argv[i][0] == '-')
		{

			settings.push_back (set);
			ind = settings.size () - 1;

			for (int j = 0; j < TYPES; j++)
			{
//                          cerr << argv[i] <<"|"<<cmd_types[i]<<endl;
				if (strcmp (argv[i], cmd_types[j]) == 0)
				{
					settings[ind].type = j;
				}
			}

		}
		else
		{
			// alle argumente die vor dem ersten parameter kommen werden ignoriert, also bei
			// ./apfli bla1 bla2 bla3 -pl link1 link2
			// wird bla1 bla2 bla3 ignoriert
			if (ind > -1)
			{
				settings[ind].values.push_back (argv[i]);
			}
		}
	}
	return 0;
}


void
settype_t::get_values ()
{
	for (unsigned int i = 0; i < values.size (); i++)
	{
		cerr << "v: " << values[i] << endl;
	}
}


void
show_topics (void *plugin)
{
	LINK (plugin);		// danach ist Plugin * pthis und Content * content verfuegbar (siehe Plugin.h)
	Plugin_Edit_Settings *p_plug =
		reinterpret_cast < Plugin_Edit_Settings * >(plugin);

	p_plug->v_act_topic.clear ();

	xmlDocPtr doc1;
	xmlNodePtr cur1;

	content->clear ();
	content->reset ();
	content->set_enter_function (show_sub_topics);

	xml_init (doc1, cur1, settings_buffer, "apfli");
	p_plug->v_act_topic.clear ();

	while (cur1 != NULL)
	{
		if (xmlStrcmp (cur1->name, (const xmlChar *) "text"))
		{
			p_plug->v_act_topic.push_back ((char *) cur1->name);
			content->add_item ((char *) cur1->name);
		}
		cur1 = cur1->next;
	}
	xmlFreeDoc (doc1);

	p_plug->v_act_topic.push_back (L_SETTINGS_CORE);
	content->add_item (L_SETTINGS_CORE);

	content->print ();
}

void
show_sub_topics (int actual_item, void *plugin)
{
	LINK (plugin);		// danach ist Plugin * pthis und Content * content verfuegbar (siehe Plugin.h)
	Plugin_Edit_Settings *p_plug =
		reinterpret_cast < Plugin_Edit_Settings * >(plugin);
	p_plug->s_act_topic = p_plug->v_act_topic[actual_item];
	p_plug->v_act_sub_topic.clear ();

	last_item = actual_item;

	xmlDocPtr doc1;
	xmlNodePtr cur1;

	content->clear ();
	content->reset ();
	content->set_enter_function (show_settings_cont);

	if (p_plug->s_act_topic != L_SETTINGS_CORE)
	{
		xml_init (doc1, cur1, settings_buffer, "apfli");
		xml_get_node (cur1, (char *) p_plug->s_act_topic.c_str (),
			      NULL, "");
		cur1 = cur1->xmlChildrenNode;

		while (cur1 != NULL)
		{
			if (xmlStrcmp (cur1->name, (const xmlChar *) "text"))
			{
				p_plug->v_act_sub_topic.
					push_back ((char *) cur1->name);
				content->add_item ((char *) cur1->name);
			}
			cur1 = cur1->next;
		}

		xmlFreeDoc (doc1);
	}
	else
	{
		edit_core_settings ();
	}
	content->add_item ("Zurück");
	content->add_enter_funtion (show_topics);
	content->print ();
}

void
show_settings_cont (int actual_item, void *plugin)
{
	//    LINK(plugin);           // danach ist Plugin * pthis und Content * content verfuegbar (siehe Plugin.h)
	Plugin_Edit_Settings *p_plug =
		reinterpret_cast < Plugin_Edit_Settings * >(plugin);
	p_plug->s_act_sub_topic = p_plug->v_act_sub_topic[actual_item];
	p_plug->v_act_setting.clear ();

	xmlDocPtr doc1;
	xmlNodePtr cur1;
	xmlAttrPtr attr1;
	xmlChar *buf;
	string buffer, buffer2;

	//      content->clear ();
	//      content->reset ();

	xml_init (doc1, cur1, settings_buffer, "apfli");
	xml_get_node (cur1, (char *) p_plug->s_act_topic.c_str (), NULL, "");
	cur1 = cur1->xmlChildrenNode;
	xml_get_node (cur1, (char *) p_plug->s_act_sub_topic.c_str (), NULL,
		      "");

	Plugin::set_handle_keyboard (true);


	Form edit_box (p_plug->s_act_sub_topic /*, anzahl_der_felder */ );

	int count = 0;
	if (cur1 != NULL)
	{
		attr1 = cur1->properties;
		while (attr1 != NULL)
		{
			p_plug->v_act_setting.push_back ((char *) attr1->
							 name);

			buf = xmlGetProp (cur1, attr1->name);
			if (buf != NULL)
			{
				buffer = (char *) attr1->name;

				//buffer += ":";
				buffer2 = (char *) buf;
				xmlFree (buf);

				// damit 2 paswort felder angezeigt werden
				// indenen man aber nicht sieht wieviel zeichen
				// drinstehen
				if (buffer == "passwort")
				{
					// is och eigentlich doof weil man sozusagen
					// vorher wissen muss das hier 2felder sind weil
					// man ja anzahl_der_felder definieren muss
					buffer2 = "";
					edit_box.add (buffer, "");
					edit_box.add (buffer, "");
					edit_box.set_field_opt (count,
								O_PUBLIC,
								false);
					count++;
					edit_box.set_field_opt (count,
								O_PUBLIC,
								false);
				}
				else
				{
					edit_box.add (buffer, buffer2);
					if (buffer == "ip")
					{
						edit_box.
							set_field_ipv4
							(count);
					}
				}
				count++;
			}
			attr1 = attr1->next;
		}
	}
	else
	{

	}

	xmlFreeDoc (doc1);

	edit_box.init ();


	string *new_settings = NULL;
	vector < string > idents;
	idents = edit_box.get_idents ();

	new_settings = edit_box.run ();

	if (new_settings != NULL)
	{			// wenn der OK knopf gedruekt wurde
		for (unsigned int i = 0; i < idents.size (); i++)
		{
			if (idents[i] != "" && new_settings[i] != "")
			{
				cerr << "<" << p_plug->
					s_act_topic << "><" << p_plug->
					s_act_sub_topic << "><" << idents[i]
					<< " '" << new_settings[i] << "'>" <<
					endl;
				if (idents[i] == "passwort")
				{
					if (new_settings[i] ==
					    new_settings[i++])
						settings_set_pt_pw
							(new_settings[i]);
				}
				else
					settings_set (p_plug->s_act_topic,
						      p_plug->
						      s_act_sub_topic,
						      idents[i],
						      new_settings[i]);
			}
			//cerr << "new_settings["<<i<<"]: " << new_settings[i]<<endl;
		}
		delete[]new_settings;
	}			// beim cancel knopf:
	else
	{

	}

	Plugin::set_handle_keyboard (false);

	show_sub_topics (last_item, plugin);
}

void
edit_core_settings ()
{
	xmlDocPtr doc1;
	xmlNodePtr cur1;
	float first;
	char buff[BUF_LEN_];
	string buffer;

	string core_settings = aj_do_xml ("GET", "/xml/settings.xml?");
	core_settings = core_settings.erase (0, core_settings.find ("<", 0));

	xml_init (doc1, cur1, core_settings, "settings");

	Plugin::set_handle_keyboard (true);

	Form edit_box (L_SETTINGS_CORE);

	buffer = xml_get_value (doc1, cur1, "", "nick");
	edit_box.add (L_CS_NICK, buffer);

	buffer = xml_get_value (doc1, cur1, "", "port");
	edit_box.add (L_CS_PORT, buffer);

	buffer = xml_get_value (doc1, cur1, "", "xmlport");
	edit_box.add (L_CS_XML_PORT, buffer);
	edit_box.set_field_int (2, 0, 0);

	buffer = xml_get_value (doc1, cur1, "", "maxupload");
	UMRECHNEN1 ();
	edit_box.add (L_CS_MAX_UP, buff);
	edit_box.set_field_num (3, 1, 3, 99999);

	buffer = xml_get_value (doc1, cur1, "", "maxdownload");
	UMRECHNEN1 ();
	edit_box.add (L_CS_MAX_DOWN, buff);
	edit_box.set_field_num (4, 1, 0, 99999);

	buffer = xml_get_value (doc1, cur1, "", "maxsourcesperfile");
	edit_box.add (L_CS_MAX_SRC_FILE, buffer);
	edit_box.set_field_int (5, 0, 99999);

	buffer = xml_get_value (doc1, cur1, "", "maxnewconnectionsperturn");
	edit_box.add (L_CS_MAX_NEW_CON, buffer);
	edit_box.set_field_int (6, 1, 200);
/*	
	buffer = xml_get_value (doc1, cur1, "settings", "speedperslot");
	edit_box.add ("Geschwindigkeit pro Slot", buffer);
	edit_box.set_field_int(7,0,99999);
*/

	xmlFreeDoc (doc1);

	edit_box.init ();


	string *new_settings = NULL;
	vector < string > idents;
	idents = edit_box.get_idents ();

	new_settings = edit_box.run ();

	if (new_settings != NULL)
	{			// wenn der OK knopf gedruekt wurde
		buffer = "/function/setsettings?";

		buffer += "&Nickname=" + new_settings[0];
		buffer += "&Port=" + new_settings[1];
		buffer += "&XMLPort=" + new_settings[2];
		UMRECHNEN2 (new_settings[3]);
		buffer += "&MaxUpload=";
		buffer += buff;
		UMRECHNEN2 (new_settings[4]);
		buffer += "&MaxDownload=";
		buffer += buff;

		buffer += "&MaxSourcesPerFile=" + new_settings[5];
		buffer += "&MaxNewConnectionsPerTurn=" + new_settings[6];

		aj_do_xml ("GET", buffer);
		delete[]new_settings;
	}			// beim cancel knopf:

	Plugin::set_handle_keyboard (false);

	//show_sub_topics (last_item, plugin);

}
