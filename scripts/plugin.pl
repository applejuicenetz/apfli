#!/usr/bin/perl

#
#	Script zum generieren eines Plugins
#
#	(C) 20/07/2004 by Dominic Scharfe
#	http://apfli.sourceforge.net
#

@Questions = (
'Plugin Name z.B. Download',
'Autor',
'Homepage, Email',
);

$i=0;
foreach $question (@Questions) {
	print ($i+1);
	print ") ${question}\n";
	$Answers[$i] = <>;
	
	chomp($Answers[$i]);	
	
	if ($i==0) {

	    $file = "Plugin_$Answers[0]";
	    $FILE = uc ($file);

	    if (-e "../src/$file.cpp" || -e "../include/$file.h") {
	        die ("Plugin existiert schon!");
	    }
	}
	

	$i++;
}


$gpl = 
'/***************************************************************************
 *   Copyright (C) 2004 by '.$Answers[1].'
 *   '.$Answers[2].'                                                     
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

';


$srcfile_str = 
'#include "../include/'.$file.'.h"

'.$file.'::'.$file.'()
{
    set_name("'.$Answers[0].'");
}

void function()
{
    // erforderlich damit auf per pthis auf das aktuelle Plugin 
    //und per content auf den aktuellen Content zugefriffen werden kann
    LINK();
    // hier folgt alles was das Plugin machen soll
}';


$incfile_str =
'#ifndef '.$FILE.'_H
#define '.$FILE.'_H
#include "Plugin.h"
using namespace std;

class '.$file.' : public Plugin
{
    public:
	    '.$file.'();
	    void function();
    
    private:

};

#endif
';

open(OUT, ">../src/$file.cpp");
print OUT $gpl;
print OUT $srcfile_str;
close(OUT);

open(OUT, ">../include/$file.h");
print OUT $gpl;
print OUT $incfile_str;
close(OUT);

