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
#ifndef _FORM_H
#define _FORM_H
#include "Window.h"
#include "Keyboard.h"
#include <form.h>
#include <string>
#include <vector>
//#define MAX_FIELDS 100
using namespace std;

class Form {
  public:
    Form(string caption /*, int fields */ );
    ~Form();
    void init();
    void deinit();
    void hide();
    void show();
    void add(string bez, string bez);
    //      void run(string *settings, vector <string> &idents);
    //      void run(string *settings);
    string *run();
    void set_field_opt(int count, int attr, bool on);
    void set_field_pwdl(int count);
    void set_field_ipv4(int count);
  	void set_field_int(int count,int min ,int max);
     vector < string > &get_idents();
  private:
     Window window;
    FIELD **field;

     vector < FIELD * >field_vect;
     vector < string > field_capt;

     int ident_max_size;
    int act_field;
    FORM *form;
    string caption;
    int fields;
    int rows;
    int cols;
};

#endif
