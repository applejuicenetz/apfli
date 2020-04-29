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
#include "../include/types.h"

table_t::table_t(size_t name, size_t sources, size_t state, size_t speed,
		 size_t timeleft, size_t pwdl)
{
    set(name, sources, state, speed, timeleft, pwdl);
}

void
 table_t::set(size_t name, size_t sources, size_t state, size_t speed,
	      size_t timeleft, size_t pwdl)
{
    this->name = name;
    this->sources = sources;
    this->state = state;
    this->speed = speed;
    this->timeleft = timeleft;
    this->pwdl = pwdl;
}
