/***************************************************************************
 *   Copyright (C) 2004 by Dominic Scharfe,Felix M�ller                    *
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

#ifndef PLUGIN_HELP_H
#define PLUGIN_HELP_H
#include "../../include/Plugin.h"
#include <fstream>
using namespace std;

class Plugin_Help:public Plugin {
  public:
    Plugin_Help();
    void function();

  private:

};

#endif
