#ifndef _COMMON_GUI_FUNC_H
#define _COMMON_GUI_FUNC_H

#include "main_header.h"

void show_message(gpointer window, char title[], char text[], int type);
char* show_file_dialog(gpointer window);

#endif