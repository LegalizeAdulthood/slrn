dnl# -*- sh -*-
AC_INIT(src/slrn.c)
JD_INIT

AC_CONFIG_AUX_DIR(autoconf)
AC_CANONICAL_HOST

AC_PROG_MAKE_SET
AC_PROG_INSTALL

JD_ANSI_CC

# determine X include and needed libs
AC_PATH_XTRA

#------------------------------------------------------------------------
# Useful macros
#------------------------------------------------------------------------

AC_DEFUN([CF_COMPILE_OPTION],[
 optionvalue=$4
 AC_ARG_ENABLE($1,[$2],[
  if test "x$enableval" = "xyes" ; then
   optionvalue=1
  else
   optionvalue=0
  fi
 ])
 AC_SUBST($3, $optionvalue)
])dnl


#---------------------------------------------------------------------------
# Configure options
#---------------------------------------------------------------------------
dnl# Unfortunately, autoconf lacks a --docdir option. This is a workaround:
AC_ARG_WITH(docdir,
    [  --with-docdir=DIR       Where to put the documentation],
    [ if test "x$withval" = xyes || test "x$withval" = xno; then
         docdir='${prefix}/share/doc/slrn'
      else
         docdir="$withval"
      fi
    ], [ docdir='${prefix}/share/doc/slrn' ])
AC_SUBST(docdir)

AC_ARG_WITH(slrnlib,
    [  --with-slrnlib=DIR       Place for the slrn library files])
if test -z "$with_slrnlib" || test "x$with_slrnlib" = xyes || test "x$with_slrnlib" = xno; then
	if test "x$prefix" = xNONE; then
		slrn_lib_dir="${ac_default_prefix}/lib/slrn"
	else
		slrn_lib_dir="${prefix}/lib/slrn"
	fi
else
	slrn_lib_dir="$with_slrnlib"
fi
AC_SUBST(SLRN_LIB_DIR,"$slrn_lib_dir")

dnl# directory where .mo (translation) files should be placed
AC_ARG_WITH(localedir,
[  --with-localedir=DIR    Where to put locale files])
if test -z "$with_localedir" || test "x$with_localedir" = xyes || test "x$with_localedir" = xno; then
    if test "x$prefix" = xNONE; then
	LOCALEDIR="${ac_default_prefix}/share/locale"
    else
        LOCALEDIR="${prefix}/share/locale"
    fi
else
    LOCALEDIR="$with_localedir"
fi		    
AC_SUBST(LOCALEDIR)

optionvalue=0
AC_ARG_WITH(slrnpull,
    [  --with-slrnpull         Build slrnpull and add support for it to slrn],
    [if test "x$withval" = "xyes" ; then
      optionvalue=1
      SLRNPULL="slrnpull\$(EXEEXT)"
      MAN_SLRNPULL="slrnpull.1"
     fi
    ])dnl
AC_SUBST(SLRN_HAS_PULL_SUPPORT, $optionvalue)
AC_SUBST(SLRNPULL)
AC_SUBST(MAN_SLRNPULL)

CF_COMPILE_OPTION(nntp,
    [  --disable-nntp          Disable NNTP support],
    [SLRN_HAS_NNTP_SUPPORT], 1)

CF_COMPILE_OPTION(spool,
    [  --enable-spool          Enable support for reading directly from spool],
    [SLRN_HAS_SPOOL_SUPPORT], 0)

CF_COMPILE_OPTION(inews,
    [  --enable-inews          Enable inews posting support],
    [SLRN_HAS_INEWS_SUPPORT], 0)
if test "x$enable_inews" = xyes ; then
  dnl# find inews
  AC_PATH_PROG(INEWS, inews, no, $PATH:/usr/local/bin:/usr/bin)
  if test "x$ac_cv_path_INEWS" != xno; then
      dnl# AC_DEFINE_UNQUOTED(SLRN_INEWS_COMMAND, "$ac_cv_path_INEWS -S -h")
      AC_SUBST(SLRN_INEWS_COMMAND, "$ac_cv_path_INEWS -S -h")
  else
      AC_MSG_ERROR([
I cannnot find an inews executable.  When using --enable-inews, please make
sure inews can be found in your \$PATH.
])
  fi
else
  AC_SUBST(SLRN_INEWS_COMMAND, "/usr/local/bin/inews -S -h")
fi

CF_COMPILE_OPTION(force-inews,
    [  --enable-force-inews    Enforce the use of inews],
    [SLRN_FORCE_INEWS], 0)

CF_COMPILE_OPTION(strict-from,
    [  --enable-strict-from    Disallow custom From headers],
    [SLRN_HAS_STRICT_FROM], 0)

CF_COMPILE_OPTION(charmap,
    [  --disable-charmap       Disable mapping ISO-Latin to native charsets],
    [SLRN_HAS_CHARACTER_MAP], 1)

CF_COMPILE_OPTION(setgid-code,
    [  --enable-setgid-code    Allow running slrnpull as an unpriviledged user],
    [SLRNPULL_USE_SETGID_POSTS], 0)
CF_COMPILE_OPTION(spoilers,
    [  --disable-spoilers      Disable spoiler support],
    [SLRN_HAS_SPOILERS], 1)
CF_COMPILE_OPTION(emph-text,
    [  --disable-emph-text     Disable emphasized text support],
    [SLRN_HAS_EMPHASIZED_TEXT], 1)
CF_COMPILE_OPTION(gen-mid,
    [  --disable-gen-mid       Prevent slrn (and user) from generating Message-IDs],
    [SLRN_HAS_GEN_MSGID], 1)
CF_COMPILE_OPTION(mid-cache,
    [\
  --enable-mid-cache      Make slrn cache Message-IDs to eliminate cross-posts
                          (only needed when server has no xref headers)],
    [SLRN_HAS_MSGID_CACHE], 0)
CF_COMPILE_OPTION(fake-refs,
    [  --disable-fake-refs     Do not use In-Reply-To if References is not available],
    [SLRN_HAS_FAKE_REFS], 1)
CF_COMPILE_OPTION(grouplens,
    [  --enable-grouplens      Enable GroupLens support],
    [SLRN_HAS_GROUPLENS], 0)

jd_with_uu_library=no
JD_CHECK_FOR_LIBRARY(uu,uudeview.h)
if test $jd_with_uu_library = yes
then
  LINK_LIBUU="-luu"
  AC_DEFINE(HAVE_UUDEVIEW_H)
  optionvalue=1
else
  optionvalue=0
  LINK_LIBUU=""
fi
AC_SUBST(LINK_LIBUU)
AC_SUBST(SLRN_HAS_UUDEVIEW,$optionvalue)

jd_with_canlock_library=no
JD_CHECK_FOR_LIBRARY(canlock)
if test $jd_with_canlock_library = yes
then
  LINK_LIBCANLOCK="-lcanlock"
  AC_DEFINE(HAVE_CANLOCK_H)
  optionvalue=1
else
  optionvalue=0
  LINK_LIBCANLOCK=""
fi
AC_SUBST(LINK_LIBCANLOCK)
AC_SUBST(SLRN_HAS_CANLOCK,$optionvalue)


#---------------------------------------------------------------------------
# gettext
#---------------------------------------------------------------------------
m4_include([./include/gettext.m4])
m4_include([./include/iconv.m4])
m4_include([./include/nls.m4])
m4_include([./include/po.m4])
m4_include([./include/lib-ld.m4])
m4_include([./include/lib-link.m4])
m4_include([./include/lib-prefix.m4])
m4_include([./include/mkdirp.m4])
m4_include([./include/progtest.m4])
AM_ICONV
AM_GNU_GETTEXT(external)
AC_SUBST(INCICONV)dnl# AM_GNU_GETTEXT does not do this.  Why???

#---------------------------------------------------------------------------
# SSL stuff
#---------------------------------------------------------------------------
AC_CACHE_CHECK(if you want SSL support,jd_use_ssl,
[
  AC_ARG_WITH(ssl, 
  [  --with-ssl[=path]       for SSL support],
  [jd_use_ssl=$withval], [jd_use_ssl=no])
])
case "x$jd_use_ssl" in
xno)
   SSLINC=
   SSLLIB=
  ;;
x|xyes)
   SSLINC="-I/usr/local/ssl/include"
   SSLLIB="-L/usr/local/ssl/lib -lssl -lcrypto"
;;
*)
   SSLINC="-I$jd_use_ssl/include"
   SSLLIB="-L$jd_use_ssl/lib -lssl -lcrypto"
esac
AC_SUBST(SSLINC)
AC_SUBST(SSLLIB)
if test "x$SSLINC" != x; then
 AC_DEFINE(USE_SSL)
fi

#---------------------------------------------------------------------------
# Check head files
#---------------------------------------------------------------------------

AC_CHECK_HEADERS( \
stdlib.h \
unistd.h \
memory.h \
fcntl.h \
malloc.h \
termios.h \
sys/socket.h \
socket.h \
sys/wait.h \
netinet/in.h \
arpa/inet.h \
sys/utsname.h \
locale.h \
)

#AC_CHECK_LIB(socket, socket, [LIBSOCKET="-lnsl -lsocket"]) dnl for Solaris
#AC_CHECK_LIB(bsd, gethostbyname, [LIBSOCKET="-lbsd"]) dnl for LynxOS
#AC_SUBST(LIBSOCKET)

AC_HEADER_DIRENT

AC_TYPE_MODE_T
AC_TYPE_PID_T
AC_TYPE_UID_T

AC_CHECK_FUNCS(\
memset \
memcpy \
putenv \
getcwd \
getdomainname \
sigaction \
sigemptyset \
sigprocmask \
sigaddset \
siglongjmp \
vsnprintf \
uname \
setlocale \
isalpha isspace isdigit isalnum ispunct \
)

AC_CACHE_CHECK(for domain in /etc/resolv.conf, slrn_cv_domain,
[if test -f /etc/resolv.conf; then
	slrn_cv_domain=`(grep "^domain" /etc/resolv.conf ||
	                 grep "^search" /etc/resolv.conf) |
			awk '{ print [$]2 }' | head -1`
 fi
 if test -z "$slrn_cv_domain"; then
	slrn_cv_domain=no
 fi
])

if test "$slrn_cv_domain" != no; then
	AC_DEFINE(USE_DOMAIN_NAME)
	AC_DEFINE_UNQUOTED(MY_DOMAIN_NAME, "${slrn_cv_domain}")
fi


JD_SET_OBJ_SRC_DIR
JD_TERMCAP
JD_WITH_LIBRARY(slang)
JD_GCC_WARNINGS
JD_GET_MODULES(src/modules.lis)
JD_CREATE_MODULE_ORULES

AC_CONFIG_HEADER(src/sysconf.h:src/config.hin)
AC_CONFIG_FILES(po/Makefile.in)

AC_OUTPUT(src/slrnfeat.h:src/slrnfeat.hin)
AC_OUTPUT(Makefile:autoconf/Makefile.in src/Makefile)
AC_OUTPUT(po/Makefile)

JD_CREATE_ORULE(chkslang)

JD_CREATE_ORULE(sltcp)
JD_CREATE_ORULE(nntplib)
JD_CREATE_EXEC_RULE(slrnpull)

JD_APPEND_RULES(src/Makefile)

if test "$slrn_cv_domain" != no; then
  echo ""
  echo "Your DOMAIN appears to be: $slrn_cv_domain"
  echo "If this is not correct, edit src/sysconf.h!!!"
fi

echo ""
echo "For some INSTALLATION options,  edit src/Makefile."
echo "For INEWS, LOCAL SPOOL, GROUPLENS, SLANG, ... support, edit src/slrnfeat.h"
echo ""
