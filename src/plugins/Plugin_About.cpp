/***************************************************************************
 *   Copyright (C) 2004 by Dominic Scharfe,Felix M|ller                    *
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

#include "Plugin_About.h"

Plugin_About::Plugin_About()
{
    set_name("About");
}

void Plugin_About::function()
{
    set_content();

    char zeile[2000];
    string env = getenv("HOME");
    env += "/.apfli/ABOUT";
    ifstream readme((char *) env.c_str());

    content->clear();

    if (readme.good() == true) {
	while (!readme.eof()) {
	    readme.getline(zeile, 1000);
	    content->add_item(zeile);
	}
    } else {
	cerr << L_ABOUT_NO_FILE << " | " << env << endl;
	content->add_string(L_ABOUT_NO_FILE);
    }

    content->print();
    readme.close();
}
