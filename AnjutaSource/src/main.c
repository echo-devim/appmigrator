/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
 * Copyright (C) 2015 Devim <>
 * 
 * AppMigrator is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * AppMigrator is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "main_header.h"



typedef struct _Private Private;
struct _Private
{
	/* ANJUTA: Widgets declaration for gtkappmigration.ui - DO NOT REMOVE */
};

static Private* priv = NULL;

/* For testing purpose, define TEST to use the local (not installed) ui file */
//#define TEST
#ifdef TEST
#define UI_MAIN "src/appmigrator.ui"
#define UI_BACKUP "src/backupWindow.ui"
#define UI_RESTORE "src/restoreWindow.ui"
#else
#define UI_MAIN "appmigrator.ui"
#define UI_BACKUP "backupWindow.ui"
#define UI_RESTORE "restoreWindow.ui"
#endif
#define TOP_WINDOW "window"

/* Signal handlers */
/* Note: These may not be declared static because signal autoconnection
 * only works with non-static methods
 */

/* Called when the window is closed */
void
destroy (GtkWidget *widget, gpointer data)
{
	gtk_main_quit ();
}

static GtkWidget*
create_window (const gchar *window_name)
{
	GtkWidget *window;
	GtkBuilder *builder;
	GError* error = NULL;

	/* Load UI from file */
	builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, window_name, &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (builder, NULL);

	/* Get the window object from the ui file */
	window = GTK_WIDGET (gtk_builder_get_object (builder, TOP_WINDOW));
        if (!window)
        {
                g_critical ("Widget \"%s\" is missing in file %s.",
				TOP_WINDOW,
				UI_MAIN);
        }

	priv = g_malloc (sizeof (struct _Private));
	/* ANJUTA: Widgets initialization for appmigrator.ui - DO NOT REMOVE */

	g_object_unref (builder);

	
	return window;
}

void createWindow(int argc, char *argv[], const gchar *window_name){
	GtkWidget *window;
	
#ifdef ENABLE_NLS

	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif
	
	gtk_init (&argc, &argv);

	window = create_window (window_name);
	gtk_widget_show (window);

	gtk_main ();


	g_free (priv);

}

int main (int argc, char *argv[])
{
	createWindow(argc, argv, UI_MAIN);
	return 0;
}

void
on_btnBackupWindow_clicked (GtkButton *button, gpointer user_data)
{
	createWindow(0,NULL, UI_BACKUP);
}

void
on_btnRestoreWindow_clicked (GtkButton *button, gpointer user_data)
{
	createWindow(0,NULL, UI_RESTORE);
}
