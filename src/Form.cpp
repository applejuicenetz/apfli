/***************************************************************************
 *   Copyright (C) 2004 by Dominic Scharfe, Felix Müller                   *
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
#include "../include/Form.h"

Form::Form (string caption)
{
	ident_max_size = 0;
	cerr << "Form::Form" << endl;
	this->caption = caption;
	act_field = 0;
	cerr << "Form::end" << endl;
	this->need_input = true;
}

Form::Form (string caption, bool need_input)
{
	ident_max_size = 0;
	cerr << "Form::Form" << endl;
	this->caption = caption;
	act_field = 0;
	cerr << "Form::end" << endl;
	this->need_input = need_input;
}

Form::~Form ()
{
	cerr << "Form::~Form" << endl;
	deinit ();
}

void
Form::add (string bez, string def)
{
	if (bez.size () > (unsigned int) ident_max_size)
		ident_max_size = bez.size ();
	FIELD *buf;
	cerr << "Form::add: " << bez << endl;
	if (!need_input)
		buf = new_field (1, 1, act_field, 10, 20, 0);
	else
		buf = new_field (1, 30, act_field, 10, 20, 0);
	field_capt.push_back (bez);
	set_field_buffer (buf, 0, (char *) def.c_str ());
	set_field_back (buf, A_UNDERLINE);	/* Print a line for the option */
	field_opts_off (buf, O_AUTOSKIP);	/* Don't go to next field when this */
	if (!need_input){
		field_opts_off (buf, O_VISIBLE);
	}
	act_field++;
	field_vect.push_back (buf);
}

void
Form::set_field_opt (int count, int attr, bool on)
{
	if (on == true)
	{
		field_opts_on (field_vect[count], attr);
	}
	else
	{
		field_opts_off (field_vect[count], attr);
	}
}

void
Form::set_field_int (unsigned int count, unsigned int min, unsigned int max)
{
	set_field_type (field_vect[count], TYPE_INTEGER, 1, min, max);
}

void
Form::set_field_pwdl (unsigned int count)
{
	set_field_num(count,1,0,50);
}

void
Form::set_field_num (unsigned int count,unsigned int prec,unsigned int min,unsigned int max)
{
	set_field_type (field_vect[count], TYPE_NUMERIC, prec, min, max);
}

void
Form::set_field_ipv4 (unsigned int count)
{
	set_field_type (field_vect[count], TYPE_IPV4);
}

void
Form::init ()
{
	cerr << "Form::init" << endl;

	fields = field_vect.size ();

	FIELD *buf;

	buf = new_field (1, 2, act_field + 2, 0, 0, 0);
	set_field_buffer (buf, 0, "OK");
	field_opts_off (buf, O_EDIT);
	field_vect.push_back (buf);

	buf = new_field (1, 6, act_field + 2, 16, 0, 0);
	set_field_buffer (buf, 0, "CANCEL");
	field_opts_off (buf, O_EDIT);
	field_vect.push_back (buf);

	field_vect.push_back (NULL);


	field = new FIELD *[field_vect.size ()];


	for (unsigned int i = 0; i < field_vect.size (); i++)
	{
		field[i] = field_vect[i];
		if (i < (unsigned int) fields)
			move_field (field[i], i, ident_max_size + 1);
	}


	form = new_form (field);

	scale_form (form, &rows, &cols);


	window.init ((Window::__stdscr_getmaxx () - cols) / 2 - 2,
		     (Window::__stdscr_getmaxy () - rows) / 2 - 2, cols + 4,
		     rows + 4, cp_msg_win);


	set_form_win (form, window.get_handle ());
	set_form_sub (form, derwin (window.get_handle (), rows, cols, 2, 2));
	window.__border ();

	post_form (form);
	window.__addstr ((cols - caption.size ()) / 2, 0,
			 (char *) caption.c_str ());
	for (int i = 0; i < fields; i++)
	{
		window.__addstr (2, i + 2, (char *) field_capt[i].c_str ());

	}



	update_panels ();
	doupdate ();

}


void
Form::deinit ()
{
	cerr << "Form::deinit" << endl;
	if (form != NULL)
	{
		unpost_form (form);
		free_form (form);
	}

	for (int i = 0; i < fields - 1; i++)
	{
		free_field (field_vect[i]);
	}

	delete[]field;

	cerr << "Form::deinit end" << endl;
}

vector < string > &Form::get_idents ()
{
	return field_capt;
}

string *
Form::run ()
{
	cerr << "Form::run" << endl;
	int ch;
	window.show ();
	curs_set (1);

	string *settings = new string[fields];

	// aufs erste feld springen
	form_driver (form, REQ_FIRST_FIELD);

	window.__refresh ();

	bool running = true;

	while (running == true)
	{
		ch = getch ();
		if (ch != ERR)
		{
			switch (ch)
			{
			case 9:	//TABULATOR
			case KEY_NPAGE:
			case KEY_DOWN:
				form_driver (form, REQ_NEXT_FIELD);
				form_driver (form, REQ_END_LINE);
				break;

			case KEY_PPAGE:
			case KEY_UP:
				form_driver (form, REQ_PREV_FIELD);
				form_driver (form, REQ_END_LINE);
				break;

			case KEY_LEFT:
				form_driver (form, REQ_PREV_CHAR);
				break;

			case KEY_RIGHT:
				form_driver (form, REQ_NEXT_CHAR);
				break;

			case KEY_HOME:
				form_driver (form, REQ_BEG_LINE);
				break;
			case KEY_END:
				form_driver (form, REQ_END_LINE);
				break;

			case KEY_DC:
				form_driver (form, REQ_DEL_CHAR);
				break;

			case KEY_BACKSPACE:
				form_driver (form, REQ_DEL_PREV);
				break;

			case 10:
				 /*ENTER*/
					// CANCEL KNOPF
					if (current_field (form) ==
					    field[fields + 1])
				{
					delete[]settings;
					settings = NULL;
					running = false;
				}
				else
				{
					form_driver (form, REQ_NEXT_FIELD);	// wichtig, weil sonst wenn nur enter gedrückt wurde nix gespeichert wird
					for (int i = 0; i < fields; i++)
					{

						settings[i] =
							field_buffer (field
								      [i], 0);

						int j = (settings[i].
							 length ()) - 1;

						for (; j >= 0; j--)
						{
							if (settings[i][j]
							    == ' ')
							{
								settings[i].
									erase
									(j,
									 1);
							}
						}
					}
					running = false;
				}
				break;

			default:
				form_driver (form, ch);
				break;
			}
			window.__refresh ();
		}
	}

	curs_set (0);
	window.hide ();
	return settings;
}

void
Form::hide ()
{
	window.hide ();
}

void
Form::show ()
{
	window.show ();
}
