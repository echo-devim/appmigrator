#include "functions.h"

#define CMD_SIZE 100

int savePackagesList(char *id_distro)
{
	char cmd[CMD_SIZE] = BACKUP_SCRIPT;
	strcat(cmd, " ");
	strcat(cmd, id_distro);
	strcat(cmd, " ");
	strcat(cmd, OUTPUT_BACKUP_SCRIPT);
	return system(cmd);
}

int readFile(char* filename, void (*line_handler)(char*))
{
	int size = 1024, pos,file_size;
	int c, ret;
	char *buffer = (char *)malloc(size);

	FILE *f = fopen(filename, "r");
	if (f) {
		fseek(f, 0, SEEK_END); // seek to end of file
		file_size = ftell(f); // get current file pointer
		if (file_size > 0){
			fseek(f, 0, SEEK_SET); // seek back to beginning of file
			do { // read all lines in file
				pos = 0;
				do{ // read one line
					c = fgetc(f);
					if(c != EOF) buffer[pos++] = (char)c;
					if(pos >= size - 1) { // increase buffer length
						size *=2;
						buffer = (char*)realloc(buffer, size);
					}
				}while(c != EOF && c != '\n');
				if (pos!=0){
					buffer[pos-1] = '\0';
					// line is now in buffer
					line_handler(buffer);
				}
			} while(c != EOF); 
			fclose(f);
		} //else do nothing..
		ret = 1; //success
    }else
		ret = 0; //fail
    free(buffer);
	return ret;
}

/* This function is called by installPackets and create
 * a file with names of packages to install
 */
const char* writeTempInputFile(char *packages)
{
	const char* temp_file = "gui_temp_input.txt";
	FILE *fp = fopen(temp_file, "w");
	fwrite(packages,1,strlen(packages),fp);
	fclose(fp);
	return temp_file;
}

int installPackets(char *id_distro, char* packages, void (*result_handler)(char*))
{
	const char *temp_input_file = writeTempInputFile (packages);
	char *temp_result = "gui_diff_result.txt";
	char cmd[CMD_SIZE] = INSTALL_SCRIPT;
	int ret=0;
	strcat(cmd, " ");
	strcat(cmd, id_distro);
	strcat(cmd, " ");
	strcat(cmd, temp_input_file);
	strcat(cmd, " ");
	strcat(cmd, temp_result);
	system(cmd);
	remove(temp_input_file);
	ret = readFile(temp_result,result_handler);
	remove(temp_result);
	return ret;
}