/* *INDENT-OFF* */ /* ATTRIBUTE_PRINTF confuses indent, avoid running it
		      for now.  */
/* Basic, host-specific, and target-specific definitions for GDB.
   Copyright (C) 1986-2020 Free Software Foundation, Inc.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef DEFS_H
#define DEFS_H

#ifdef GDBSERVER
#  error gdbserver should not include gdb/defs.h
#endif


#include <sys/types.h>
#include <limits.h>

/* The libdecnumber library, on which GDB depends, includes a header file
   called gstdint.h instead of relying directly on stdint.h.  GDB, on the
   other hand, includes stdint.h directly, relying on the fact that gnulib
   generates a copy if the system doesn't provide one or if it is missing
   some features.  Unfortunately, gstdint.h and stdint.h cannot be included
   at the same time, which may happen when we include a file from
   libdecnumber.

   The following macro definition effectively prevents the inclusion of
   gstdint.h, as all the definitions it provides are guarded against
   the GCC_GENERATED_STDINT_H macro.  We already have gnulib/stdint.h
   included, so it's ok to blank out gstdint.h.  */
#define GCC_GENERATED_STDINT_H 1

#include <unistd.h>

#include <fcntl.h>

#ifdef _WIN32
#include "wtou.h"
#endif

#include "gdb_wchar.h"

// #include "ui-file.h"

//#include "gdbsupport/host-defs.h"
//#include "gdbsupport/enum-flags.h"

/* Scope types enumerator.  List the types of scopes the compiler will
   accept.  */

enum compile_i_scope_types
  {
    COMPILE_I_INVALID_SCOPE,

    /* A simple scope.  Wrap an expression into a simple scope that
       takes no arguments, returns no value, and uses the generic
       function name "_gdb_expr". */

    COMPILE_I_SIMPLE_SCOPE,

    /* Do not wrap the expression,
       it has to provide function "_gdb_expr" on its own.  */
    COMPILE_I_RAW_SCOPE,

    /* A printable expression scope.  Wrap an expression into a scope
       suitable for the "compile print" command.  It uses the generic
       function name "_gdb_expr".  COMPILE_I_PRINT_ADDRESS_SCOPE variant
       is the usual one, taking address of the object.
       COMPILE_I_PRINT_VALUE_SCOPE is needed for arrays where the array
       name already specifies its address.  See get_out_value_type.  */
    COMPILE_I_PRINT_ADDRESS_SCOPE,
    COMPILE_I_PRINT_VALUE_SCOPE,
  };



/* Just in case they're not defined in stdio.h.  */

#ifndef SEEK_SET
#define SEEK_SET 0
#endif
#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif

/* The O_BINARY flag is defined in fcntl.h on some non-Posix platforms.
   It is used as an access modifier in calls to open(), where it acts
   similarly to the "b" character in fopen()'s MODE argument.  On Posix
   platforms it should be a no-op, so it is defined as 0 here.  This 
   ensures that the symbol may be used freely elsewhere in gdb.  */

#ifndef O_BINARY
#define O_BINARY 0
#endif

#include "hashtab.h"

//#include "utils.h"

#endif /* #ifndef DEFS_H */
