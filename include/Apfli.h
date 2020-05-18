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
#ifndef APFLI_H_
#define APFLI_H_


#include "../include/Window.h"
#include "../include/Menu.h"
#include "../include/Colors.h"
#include "../include/Keyboard.h"
#include "../src/plugins/Plugin_Download.h"
#include "../src/plugins/Plugin_About.h"
#include "../src/plugins/Plugin_Help.h"
#include "../src/plugins/Plugin_Lizens.h"
#include "../src/plugins/Plugin_Main.h"
#include "../src/plugins/Plugin_Edit_Settings.h"
#include "../src/plugins/Plugin_Upload.h"
#include "../src/plugins/Plugin_Status.h"
#include "../include/settings.h"
#include "../include/sockfunc.h"
#include <pthread.h>
#include <fstream>
#include <iostream>
#include <sys/ioctl.h>
#include <sys/termios.h>

#define MIN_ROWS 5
#define MIN_COLS 40
#define APFLI_VERSION 	"0.2 | build 17/08/2004 | release 3"
#define APFLI_HELP 		"Parameter: -v : Versionsinfo"
using namespace std;

/**
Apfli Implementation

@author Dominic Scharfe, Felix Mueller
*/

class Apfli {
  public:
    Apfli();
    ~Apfli();

    static bool term_error();

    void init();
    void deinit();
    void main_loop();

    void init_threads();
    void deinit_threads();

    void init_windows();
    void deinit_windows();

    void init_plugins();
    void deinit_plugins();

    void init_menus();

    void init_contents();
    void deinit_contents();

    // wenn Fenstergroesse geandert wird
    bool resize();

    static bool process_links(int argc, char **argv);

    void stop_main_loop();

    Window *get_msgbar_win() {
	return &msgbar_win;
    };

    Plugin_Status *plug_status;
    static bool waiting;
  private:
    //      static bool waiting;

    Plugin_Download * plug_down;
    Plugin_About *plug_about;
    Plugin_Lizens *plug_lizens;
    Plugin_Help *plug_help;
    Plugin_Main *plug_main;
    Plugin_Edit_Settings *plug_edit_settings;
    Plugin_Upload *plug_upload;


    pthread_t *fkt_thread;
    pthread_t *msgbar_thread;
    Content *main_content;
    Content *status_content;

    Menu main_menu;
    Menu settings_menu;
    Menu about_menu;

    Window main_win;
    Window msgbar_win;
    bool running;

    // benoetigt fuer debugging
    streambuf *sbuf;
    ofstream out;


};

#endif
