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
#ifndef PLUGIN_DOWNLOAD_H
#define PLUGIN_DOWNLOAD_H
#include "../../include/Plugin.h"
#include <string.h>
#include "../../include/sockfunc.h"
#include "../../include/settings.h"
#include "../../include/Form.h"
#include "../../include/Core_Download_Item.h"
#include <iostream>
#include <vector>
#include "../../include/Core_Data.h"
#include "../../include/language.h"

using namespace std;

class Plugin_Download:public Plugin {
  public:
    Plugin_Download();
    ~Plugin_Download();

    void function();

    void get_content(Content * ret);
    void init();
    void change_pwdl(unsigned int pos, double pwdl);
    void pause_dl(unsigned int pos);
    void pause_dl_all_except(unsigned int pos);
    void pause_dl_all();
    void resume_dl_all();
    void abort_dl(unsigned int pos);
    void resize();
     vector < Core_Download_Item > item;
    //Core_Download_Item *get_item(int nr);
    //      static table_t table;

  private:

     Core_Data core_dl;
    Core_Data core_user;
    void free_data();
    //vector < Core_Download_Item > item;

};

#define CAST_ACT_ITEM(x) \
	int actual_item = reinterpret_cast<int>(x);

#define CAST_PLUG_DOWN(x) \
	Plugin_Download *plug_down = reinterpret_cast<Plugin_Download*>(x);

#define CAST_ITEM(x) \
	vector < Core_Download_Item > &item = x->item;


#endif
