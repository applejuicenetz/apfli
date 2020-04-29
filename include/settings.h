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
#ifndef SETTINGS_H
#define SETTINGS_H
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "../include/md5.h"
#include "../include/language.h"
#include "../include/Colors.h"

#define XML_ROOT "apfli"

#define DEFAULT_PW ""
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT "9851"
#define DEFAULT_AJCORE "java -jar ajcore.jar"
#define DEFAULT_WAIT_TIME "1000"

using namespace std;

#define TYPES 3

#define CMD_TYPE_PW	"-pw"
#define CMD_TYPE_LINK	"-pl"
#define CMD_TYPE_VERSION "-v"

static string settings_buffer;
//static int last_item;

enum {
    set_password,
    set_link,
    set_version
};

//static const char *cmd_types[] = { "-pw", "-pl" };

class settype_t {
  public:
    vector < string > values;
    int type;
    void get_values();
};


bool settings_init();

bool settings_init_xml(xmlDocPtr & doc, xmlNodePtr & cur);
void settings_save();
void settings_get_node(xmlNodePtr & cur, char *sub_element);
void settings_set_pt_pw(string password);
void settings_set(string topic, string name, string ident, string value);
string settings_get(string topic, string name, string ident);
void cast(string str, int &ret);
void settings_ask();

//int parse_cmdline(int argc, char **argv, vector <string> &links, vector <string> &settings);
int parse_cmdline(int argc, char **argv, vector < settype_t > &settings);

void show_topics(void *plugin);
void show_sub_topics(int actual_item, void *plugin);
void show_settings_cont(int actual_item, void *plugin);
void edit_core_settings();

#endif
