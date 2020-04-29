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
#include "../include/aux_functions.h"

void gui_print_dat(string & ret, long int first, long int last)
{
    float *most;
    float b_first = first;
    float b_last = last;
    if (b_first < b_last)
	most = &b_last;
    else
	most = &b_last;
    ret = "Byte";
    if (*most >= 1024) {
	ret = "KB";
	b_first = b_first / 1024.00;
	b_last = b_last / 1024.00;
	if (*most >= 1024) {
	    ret = "MB";
	    b_first = b_first / 1024.00;
	    b_last = b_last / 1024.00;
	    if (*most >= 1024) {
		ret = "GB";
		b_first = b_first / 1024.00;
		b_last = b_last / 1024.00;
	    }
	}
    }
#define BUF_LEN	20
    char buff[BUF_LEN];
    sprintf(buff, "%.2f/%.2f %s", 
	    b_first, b_last, 
	    (char*)ret.c_str());
/*
	while (strlen(buff)<BUF_LEN) {
		strcat(buff, " ");
	}
*/
    ret = buff;
}

void gui_print_dat(string & ret, float first, bool is_speed)
{
    ret = "Byte";
    if (first >= 1024 || first <= -1024) {
	ret = "KB";
	first = first / 1024.00;
	if (first >= 1024 || first <= -1024) {
	    ret = "MB";
	    first = first / 1024.00;
	    if (first >= 1024 || first <= -1024) {
		ret = "GB";
		first = first / 1024.00;
	    }
	}
    }
#define BUF_LEN_ 20
    char buff[BUF_LEN_];
    if (is_speed)
	sprintf(buff, "%.2f %s/s", first, ret.c_str());
    else
	sprintf(buff, "%.2f %s", first, ret.c_str());



    ret = buff;
}


void gui_print_dat(string & ret, string & dat, bool is_speed)
{
    float first = atoi(dat.c_str());
    gui_print_dat(ret, first, is_speed);
}
