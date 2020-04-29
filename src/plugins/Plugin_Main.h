/***************************************************************************
 *   Copyright (C) 2004 by Dominic Scharfe,Felix Müller                    *
 *   www.fd-soft.de.tt                                                     *
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

#ifndef PLUGIN_MAIN_H
#define PLUGIN_MAIN_H
#include <fstream>
#include "../../include/Plugin.h"
//#include "../include/sockfunc.h"
#include "../../include/Core_Data.h"
//#define _LANG_DEUTSCH
#include "../../include/language.h"


#define TEST_GET(x,y)\
	if (get != "")\
	sprintf(zeile, x,get.c_str());\
	else sprintf(zeile,y);

using namespace std;

class Plugin_Main:public Plugin {
  public:
    Plugin_Main();
    void function();

  private:
     Core_Data core_main;
//Core Daten fuer Netwerkinformationen
    Core_Data core_mod;
//Core Daten fuer Server
    Core_Data core_serv;
};

#endif
