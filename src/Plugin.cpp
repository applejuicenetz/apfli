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
#include "../include/Plugin.h"
//Debug * Plugin::debug = NULL; // fuer Debug Modus
Plugin *Plugin::act = NULL;
bool Plugin::draw = true;
bool Plugin::handle_keyboard = false;


Plugin::Plugin()
{
    set_name("noname");
    running = true;
    handle_keyboard = false;
}

Plugin::~Plugin()
{

}

void Plugin::set_name(string name)
{
    this->name = name;
}

void Plugin::set_draw(bool draw)
{
    Plugin::draw = draw;
}

void Plugin::set_content(Content * content)
{
    this->content = content;
}

void Plugin::function()
{

}

void Plugin::call_func()
{
    if (act != NULL)
	Plugin::act->function();
}

void Plugin::set_content()
{
    content->set_act_plugin((void *) this);
}

void Plugin::kill_gentle()
{
    running = false;
}

void Plugin::set_running(bool running)
{
    this->running = running;
}

void Plugin::set_setting(string ident, string value)
{
    settings_set("plugin", name, ident, value);
}

string Plugin::get_setting(string ident)
{
    return (settings_get("plugin", name, ident));
}
