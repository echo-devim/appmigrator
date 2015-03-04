## Process this file with automake to produce Makefile.in

## Created by Anjuta


uidir = $(pkgdatadir)/ui
ui_DATA = appmigrator.ui \
	backupWindow.ui \
	restoreWindow.ui


AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(APPMIGRATOR_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = appmigrator

appmigrator_SOURCES = \
	main.c \
	backupWindow.c \
	backupWindow.h \
	functions.c \
	functions.h \
	main_header.h \
	restoreWindow.c \
	restoreWindow.h \
	common_gui_func.c \
	common_gui_func.h


appmigrator_LDFLAGS = \
	-Wl,--export-dynamic

appmigrator_LDADD = $(APPMIGRATOR_LIBS)




EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(pkgdatadir)

