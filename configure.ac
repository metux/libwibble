dnl Process this file with autoconf to produce a configure script.
AC_INIT(libwibble, [0.1.7], [libapt-front-devel@lists.alioth.debian.org])
AC_CONFIG_SRCDIR([configure.ac])
dnl AC_CONFIG_AUX_DIR(admin)
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_HEADERS(wibble/config.h)
AC_CONFIG_HEADERS(wibble/shared.h)

dnl To use subdirs
AC_PROG_MAKE_SET

AC_LANG([C++])

AC_ISC_POSIX
AC_PROG_CC
AC_PROG_CXX
AM_PROG_CC_STDC
AC_HEADER_STDC

AM_PROG_CC_C_O

#AM_PROG_LEX
#AC_PROG_YACC

dnl Use libtool
AM_ENABLE_STATIC
AM_DISABLE_SHARED
AM_PROG_LIBTOOL

CXXFLAGS="-Wall -W $CXXFLAGS"

AC_CONFIG_FILES([
Makefile
wibble/Makefile
wibble/tests/Makefile
wibble/libwibble.pc
wibble/libwibble-gc.pc
])
AC_OUTPUT

