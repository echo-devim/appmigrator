#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include "main_header.h"
#include <stdlib.h>
#include <string.h>

int savePackagesList(char *id_distro);
int readFile(char* filename, void (*line_handler)(char*));
const char* writeTempInputFile(char *packages);
int installPackets(char *id_distro, char* packages, void (*result_handler)(char*));

#endif