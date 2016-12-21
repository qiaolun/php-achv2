dnl $Id$
dnl config.m4 for extension achv2

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(achv2, for achv2 support,
dnl Make sure that the comment is aligned:
dnl [  --with-achv2             Include achv2 support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(achv2, whether to enable achv2 support,
[  --enable-achv2           Enable achv2 support])

if test "$PHP_ACHV2" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-achv2 -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/achv2.h"  # you most likely want to change this
  dnl if test -r $PHP_ACHV2/$SEARCH_FOR; then # path given as parameter
  dnl   ACHV2_DIR=$PHP_ACHV2
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for achv2 files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       ACHV2_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$ACHV2_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the achv2 distribution])
  dnl fi

  dnl # --with-achv2 -> add include path
  dnl PHP_ADD_INCLUDE($ACHV2_DIR/include)

  dnl # --with-achv2 -> check for lib and symbol presence
  dnl LIBNAME=achv2 # you may want to change this
  dnl LIBSYMBOL=achv2 # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $ACHV2_DIR/$PHP_LIBDIR, ACHV2_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_ACHV2LIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong achv2 lib version or lib not found])
  dnl ],[
  dnl   -L$ACHV2_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(ACHV2_SHARED_LIBADD)

  PHP_NEW_EXTENSION(achv2, achv2.c, $ext_shared)
fi
