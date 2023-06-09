/*
 This file is part of SLRN.

 Copyright (c) 2004-2006 Thomas Schultz <tststs@gmx.de>

 This program is free software; you can redistribute it and/or modify it
 under the terms of the GNU General Public License as published by the Free
 Software Foundation; either version 2 of the License, or (at your option)
 any later version.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 more details.

 You should have received a copy of the GNU General Public License along
 with this program; if not, write to the Free Software Foundation, Inc.,
 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/
#ifndef _SLRN_HELP_H
#define _SLRN_HELP_H

extern void slrn_help_init_keysym_table (void);
extern char *slrn_help_keyseq_to_string (char *, int);
extern char *slrn_help_string_to_keyseq (SLFUTURE_CONST char *);
extern char *slrn_help_keyseq_from_function (char *, SLKeyMap_List_Type *);

#endif /* _SLRN_HELP_H */
