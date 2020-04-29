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

#ifndef CORE_DOWNLOAD_ITEM_H
#define CORE_DOWNLOAD_ITEM_H

#include <string>
#include "../include/Core_Data.h"
#include "../include/aux_functions.h"
#include "../include/language.h"
#include "../include/types.h"

#define SIZE_FILENAME	30
using namespace std;

string format(char *str, size_t len);
string format(string & str, size_t len);


class Core_Download_Item {
  public:
    Core_Download_Item(Core_Data * core_dl, Core_Data * core_user,
		       string Id, string filename, long int size);
    //Wenn actual false zurückgibt, ist Download nichtmehr vorhanden
    //Core_Download_Item();
    bool actual();
    string get_filename();
    string get_stat();
    string get_id();
    string get_status();
    string get_remain();
    double pwdl;
    static table_t table;

  private:
     string filename;
    string id;
    long int size;
    long int pos;
    unsigned int speed;
    string status;
    int quellenzahl;
    int aktivzahl;
    int downloadzahl;
    Core_Data *core_dl;
    Core_Data *core_user;
    //      static table_t table;
};

#endif
