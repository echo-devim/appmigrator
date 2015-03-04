#ifndef _RESTORE_WINDOW_H
#define _RESTORE_WINDOW_H

#include "main_header.h"

//Global variables
char* packages_list_path;
GtkListStore *listPackages;
GtkLabel *label_info;

#define print_info(TEXT) (gtk_label_set_text(label_info,TEXT))

void on_btnSelectPackagesList_clicked (GtkButton *button, gpointer user_data);
void on_entryFilePath_changed (GtkEditable *editable, gpointer user_data);
void package_line_handler(char* line);
void on_btnOpenFile_clicked (GtkButton *button, gpointer user_data);
void on_window_realize (GtkWidget *widget, gpointer user_data);
void on_lblInfo_realize (GtkWidget *widget, gpointer user_data);
void on_cellrenderertoggle1_toggled (GtkCellRendererToggle *cellrenderertoggle, gchararray *path, gpointer user_data);
void setAllToggles(GtkListStore *liststore, gboolean value);
void on_btnSelectAll_clicked (GtkButton *button, gpointer user_data);
void on_btnDeselectAll_clicked (GtkButton *button, gpointer user_data);
void checkResult(char *package_not_installed);
void on_btnInstall_clicked (GtkButton *button, gpointer user_data);

#endif