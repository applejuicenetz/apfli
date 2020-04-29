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
#define _LANG_DEUTSCH
//------------------------English------------------------------------
#ifdef _LANG_ENGLISH
#define L_YES_CHAR				"y"
#define L_NO_CHAR				"n"

#define L_NO_CONFIG				"Config file error..."
#define L_ASK_CONFIG			"Do you want to enter the important settings?(y/n)\nIf not the standard settings will be used"
#define L_NO_IP					"IP is not set. Standard("
#define L_NO_PW					"Passwort is not set. Standard("
#define L_NO_PORT				"Port is not set. Standard("

#define L_CONSOLE_INIT_ERROR	"Failed to init Console Buffer. Maybe not enough memory available"

#define L_OS					"operating system: %s"
#define L_NO_OS					"No operating system found"
#define L_CORE_VERSION			"Core Version: %s"
#define L_NO_CORE				"no core found"
#define L_USER					"%s user are sharing "
#define L_NO_USER				"no user found"
#define L_FILES					"%s files "
#define L_NO_FILES				"no files found"
#define L_SIZE					"with a size of %s MB"
#define L_SERVER				"with server: %s conncted"
#define L_NO_SERVER				"no server connection"

//PLUGIN_ABOUT
#define L_ABOUT_NO_FILE			"File ABOUT was not found"

//PLUGIN_HELP
#define L_HELP_NO_FILE			"File README was not found"

//PLUGIN_LIZENS
#define L_LIZENS_NO_FILE		"File LIZENS was not found"

//PLUGIN_EDIT_SETTINGS
#define L_SETTINGS_CORE			"Core Settings"

#define L_SETTINGS				"Settings"
#define L_STATISTICS			"Statistics"
#define L_UPLOAD				"Upload"
#define L_DOWNLOAD				"Download"
#define L_ABOUT					"About"
#define L_MAIN					"Main"
#define L_CORE_EXIT				"close Core+GUI"
#define L_EXIT					"Exit"

#define L_HELP0					"Syntax: linuxgui [OPTION] [ARGUMENTS]"
#define L_HELP_PL				"-pl [Link1] [Link2]\tlead link to core"
#define L_HELP_PW				"-pw\t\t\tset password"
#define L_HELP_PORT				"-port\t\t\tset port"
#define L_HELP_IP				"-ip\t\t\tset IP address"
#define L_HELP_SP				"-sp\t\t\tpath to the GUI-settingssource"
#define L_HELP_ROWS				"-rows\t\t\tZeilenanzahl der GUI angeben"
#define L_HELP_COLS				"-cols\t\t\tSpaltenanzahl der GUI angeben"
#define L_HELP_UPDT				"-updt\t\t\tWartezeit (in s) aller der vom Core neue Daten angefordert werden"

#define L_DOC_PARSE_ERROR		"Dokument nicht richtig geparst. \n"
#define L_EMPTY_DOC				"Leeres Dokument\n"
#define L_WRONG_DOC_TYPE		"document of the wrong type"

#define	L_SEARCH				"Search"
#define	L_LOAD					"Load"
#define	L_FEWMEM				"not enough memory"
#define L_GETREADY				"Complete"
#define L_WRONGREADY			"Complete failed"
#define L_READY					"Ready"
#define L_ABORT					"Abort"
#define	L_CREATEDATA			"Create .data"
#define	L_ABBORTED				"Aborted"
#define	L_PAUSE					"Paused"
#define L_NO_ITEMS				"No Entries"

#define L_WANT_CORE_EXIT		"Do you really want to close Core+GUI?"

//Downloadmenue
#define L_DL_ABORT				"Abort"
#define L_DL_ABORT_CONFIRM		"Do you really want to abort?"
#define L_DL_PAUSE				"Pause/Resume"
#define L_DL_PWDL				"Change Powerdownload"
#define L_DL_RESUME_ALL			"Resume all"
#define L_DL_PAUSE_ALL_EXCEPT	"Pause all except of this"
#define L_DL_PWDL				"Change Powerdownload"
#define L_DL_DETAILS			"Details"

//Uploadmenu
#define L_UL_ACTIVE				"active uploads:"
#define L_UL_STAT				"%i from %i uploads are aktiv"
#endif


//------------------------Deutsch------------------------------------
#ifdef _LANG_DEUTSCH
#define L_YES_CHAR				"j"
#define L_NO_CHAR				"n"

//Fehler
#define L_NO_CONFIG				"Problem mit Konfigurationsdatei"
#define L_ASK_CONFIG			"Sollen die wichtigsten Einstellungen jetzt abgefragt werden?(j/n)\nAnsonsten werden die Standarteinstellungen genutzt"
#define L_NO_IP					"IP ist nicht gesetzt. Standart("
#define L_NO_PW					"Passwort ist nicht gesetzt. Standart("
#define L_NO_PORT				"Port ist nicht gesetzt. Standart("

#define L_CONSOLE_INIT_ERROR	"Konnte Konsole Buffer nicht initalisieren. Eventuell nicht genug Speicher vorhanden"

//Hilfe
#define L_HELP					"Syntax: linuxgui [OPTION] [ARGUMENTE]"
#define L_HELP_PL				"-pl [Link1] [Link2]\tLink an core weiterleiten"
#define L_HELP_PW				"-pw\t\t\tPasswort setzen"
#define L_HELP_PORT				"-port\t\t\tPort setzen"
#define L_HELP_IP				"-ip\t\t\tIP setzen"
#define L_HELP_SP				"-sp\t\t\tOrt der GUI Einstellungsdatei angeben"
#define L_HELP_ROWS				"-rows\t\t\tZeilenanzahl der GUI angeben"
#define L_HELP_COLS				"-cols\t\t\tSpaltenanzahl der GUI angeben"
#define L_HELP_UPDT				"-updt\t\t\tDatenabfrage Intervall vom Core in s"
#define L_HELP_AJCORE			"-ajcore\t\t\tPfad zum AppleJuice Core"

//PLUGIN_MAIN
#define L_OS					"Betriebsystem: %s"
#define L_NO_OS					"Kein Betriebsystem gefunden"
#define L_CORE_VERSION			"Core Version: %s"
#define L_NO_CORE				"Keine Coreversion gefunden"
#define L_USER					"%s Nutzer sharen "
#define L_NO_USER				"Keine Netzwerknutzer gefunden"
#define L_FILES					"%s Dateien "
#define L_NO_FILES				"Keine Dateien gefunden"
#define L_SIZE					"mit einem Volumen von %s MB"
#define L_SERVER				"Mit Server: %s verbunden"
#define L_NO_SERVER				"Mit keinem Server verbunden"

//PLUGIN_ABOUT
#define L_ABOUT_NO_FILE			"Datei ABOUT wurde nicht gefunden"

//PLUGIN_HELP
#define L_HELP_NO_FILE			"Datei README wurde nicht gefunden"

//PLUGIN_LIZENS
#define L_LINZENS_NO_FILE		"Datei LIZENS wurde nicht gefunden"

//PLUGIN_EDIT_SETTINGS
#define L_SETTINGS_CORE			"Core Settings"

//Navigation
#define L_SETTINGS				"Settings"
#define L_STATISTICS			"Statistiken"
#define L_DOWNLOAD				"Download"
#define L_UPLOAD				"Upload"
#define L_ABOUT					"About"
#define L_MAIN					"Main"
#define L_CORE_EXIT				"Core+GUI beenden"
#define L_EXIT					"Beenden"


// Core Menue
#define L_EXIT_CORE				"Beenden"
#define L_START_CORE			"Starten"
#define L_CORE_INFO				"Info"

//XML
#define L_DOC_PARSE_ERROR		"Dokument nicht richtig geparst. \n"
#define L_EMPTY_DOC				"Leeres Dokument\n"
#define L_WRONG_DOC_TYPE		"Das Dokument ist nicht korrekt"

//Download/Upload
#define	L_SEARCH				"Suche"
#define	L_LOAD					"Lade"
#define	L_FEWMEM				"Zu wenig Speicher"
#define L_GETREADY				"Fertigstellen"
#define L_WRONGREADY			"Fertigstellen fehlgeschlagen"
#define L_READY					"Fertig"
#define L_ABORT					"Abbrechen"
#define	L_CREATEDATA			"Erstelle .data"
#define	L_ABBORTED				"Abgebrochen"
#define	L_PAUSE					"Pause"
#define L_NO_ITEMS				"Keine Einträge vorhanden"

//Coreexit
#define L_WANT_CORE_EXIT		"Willst du Core+GUI wirklich beenden?"

//Downloadmenue
#define L_DL_ABORT				"Downlaod Abbrechen"
#define L_DL_ABORT_CONFIRM		"willst du den Download wirklich Abbrechen?"
#define L_DL_PAUSE				"pausieren/fortsetzen"
#define L_DL_PAUSE_ALL			"Alle pausieren"
#define L_DL_RESUME_ALL			"Alle fortsetzen"
#define L_DL_PAUSE_ALL_EXCEPT	"Alle pausieren ausser diesen"
#define L_DL_PWDL				"Powerdownload aendern"
#define L_DL_DETAILS			"Details"

//Uploadmenu
#define L_UL_ACTIVE				"Aktive Uploads:"
#define L_UL_STAT				"%i von %i Uploads aktiv"



#endif
