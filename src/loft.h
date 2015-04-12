/*
 * vim: set expandtab tabstop=4 shiftwidth=4 softtabstop=4 foldmethod=marker:
 *
 * loft.h
 *
 * C.C.Allison
 * chris.allison@hotmail.com
 *
 * Started: Sunday 12 April 2015, 09:26:56
 * Version: 0.00
 * Last Modified: Sunday 12 April 2015, 09:30:40
 *
 * Copyright (c) 2015 Chris Allison chris.allison@hotmail.com
 *
 * This file is part of loft.
 * 
 * loft is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * loft is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with loft.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sys/types.h>
#include "defs.h"
#include "macros.h"
#include "tools.h"
#include "configfile.h"
#include <argtable2.h>

/* globals */
struct ConfigItem *configuration;
struct sigaction *siga;
int timetodie=0;

int main(int argc,char **argv);
