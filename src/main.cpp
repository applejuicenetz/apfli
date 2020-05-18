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
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "../include/Apfli.h"
#include <signal.h>
#include <stdlib.h>
using namespace std;
#define DEBUG_MODE

static Apfli *apfli;

// Signalhandler
void
sigfunc (int sig)
{
	cerr << "Signalhandler" << endl;
	cerr << "-->" << sig << endl;
	switch (sig)
	{
	case SIGWINCH:
		Apfli::waiting = true;
		break;
	case SIGABRT:
		cerr << "beende wegen SIGABRT" << endl;
		exit (1);
		break;

	case SIGTERM:
	case SIGINT:
		settings_save ();
		cerr << "beende wegen kill/Ctrl+C" << endl;
		exit (1);
		break;
	case SIGSEGV:
		cout << "Segmentation Fault! infos siehe apfli.err (wenn DEBUG_MODE eingestellt ist)" << endl;
		exit (1);
	}
}


int
main (int argc, char *argv[])
{
	streambuf *sbuf;
	ofstream out;

	// Logfile liegt unter ~/.apfli/logfile:
	string file = getenv ("HOME");
	file += "/.apfli/logfile";

	// logfile oeffnen und stderr aufs logfile umlenken
	out.open ((char *) file.c_str ());
	sbuf = cerr.rdbuf ();
	cerr.rdbuf (out.rdbuf ());

	cerr << "Apfli Start" << endl;

	// signalhandler fuettern
	signal (SIGINT, sigfunc);
	signal (SIGWINCH, sigfunc);
	signal (SIGSEGV, sigfunc);
	signal (SIGTERM, sigfunc);
	signal (SIGABRT, sigfunc);


	// bei korrupter/nichtvorhandener Settings Datei:
	if (settings_init () == false)
		settings_ask ();

	if (Apfli::process_links (argc, argv) == false)
	{

		// MIN_COLS und MIN_ROWS siehe Apfli.cpp
		if (Apfli::term_error () == true)
		{
			cout << "Das Terminal ist zu klein" << endl;
			cout << "Es sollte mindestens " << MIN_COLS <<
				" Spalten und " << MIN_ROWS << " Zeilen" <<
				endl;
			cout << "gross sein" << endl;
		}
		else
		{

			// wenn keine links uebergeben wurden
			apfli = new Apfli;
			apfli->main_loop ();

			delete apfli;
			settings_save ();

		}
	}
	cerr << "ApfLi wurde sauber beendet" << endl;

	cerr.rdbuf (sbuf);

	return EXIT_SUCCESS;
}
