#include "restoreWindow.h"

void on_btnSelectPackagesList_clicked (GtkButton *button, gpointer user_data)
{
	GtkEntry *entryFilePath = (GtkEntry *)G_OBJECT (user_data);
	GtkWidget *main_window = gtk_widget_get_toplevel ((GtkWidget*)button);
	char *filepath = show_file_dialog(main_window);
	if (filepath!=NULL){
		gtk_entry_set_text(entryFilePath,filepath);
		packages_list_path = filepath;
	}
}

void on_entryFilePath_changed (GtkEditable *editable, gpointer user_data)
{
	packages_list_path = (char*)gtk_editable_get_chars(editable,0,-1);
}

void package_line_handler(char* line)
{
	GtkTreeIter iter;
	gtk_list_store_append(listPackages, &iter);
	gtk_list_store_set(listPackages,&iter,0,line,1,TRUE,-1);
}

void on_btnOpenFile_clicked (GtkButton *button, gpointer user_data)
{	
	listPackages = (GtkListStore *)G_OBJECT (user_data);
	GtkWidget *main_window = gtk_widget_get_toplevel ((GtkWidget*)button);
	char msg[100];
	print_info("Opening list of packages..");
	if (!readFile(packages_list_path, &package_line_handler)){
		listPackages=NULL;
		sprintf(msg,"Error: %s",strerror(errno));
		show_message(main_window, "Error", msg, GTK_MESSAGE_ERROR);
	}
	print_info("Done");
}


void on_window_realize (GtkWidget *widget, gpointer user_data)
{
	/* Function called when this window opens.
	 * Useful to fix the alignment of cellrendertoggle to the right margin.
	 */
	GtkCellRenderer *cellrenderertoggle = (GtkCellRenderer *)G_OBJECT (user_data);
	gtk_cell_renderer_set_alignment(cellrenderertoggle,1,0);
	//Initialization of global variables
	listPackages = NULL;
}

void on_lblInfo_realize (GtkWidget *widget, gpointer user_data)
{
	label_info = (GtkLabel *) widget; 
}

void on_cellrenderertoggle1_toggled (GtkCellRendererToggle *cellrenderertoggle, gchararray *path, gpointer user_data)
{
	GtkListStore *listPackages = (GtkListStore *)G_OBJECT (user_data);
    GtkTreeIter iter;
    gboolean toggle_value = gtk_cell_renderer_toggle_get_active (cellrenderertoggle);
    gtk_tree_model_get_iter_from_string (GTK_TREE_MODEL (listPackages), &iter, (gchar*)path);
	gtk_list_store_set (listPackages, &iter, 1, !toggle_value, -1);

}


void setAllToggles(GtkListStore *liststore, gboolean value)
{
	GtkTreeIter iter;
 	gboolean notempty = gtk_tree_model_get_iter_first(GTK_TREE_MODEL (liststore), &iter);
	if (notempty)
		do
			gtk_list_store_set (liststore, &iter, 1, value, -1);
		while (gtk_tree_model_iter_next(GTK_TREE_MODEL (liststore),&iter));
}

void on_btnSelectAll_clicked (GtkButton *button, gpointer user_data)
{
	GtkListStore *listPackages = (GtkListStore *)G_OBJECT (user_data);
	setAllToggles(listPackages,TRUE);
}

void on_btnDeselectAll_clicked (GtkButton *button, gpointer user_data)
{
	GtkListStore *listPackages = (GtkListStore *)G_OBJECT (user_data);
	setAllToggles(listPackages,FALSE);
}

void checkResult(char *package_not_installed)
{
	GtkTreeIter iter;
	const char *package_name;
	char text_row[200];
	GValue value = { 0, }; /* Gtk+ wants the type field initialized to 0 */
	gboolean notempty = gtk_tree_model_get_iter_first(GTK_TREE_MODEL (listPackages), &iter);
	if (notempty)
		do{ //this loop is slow! maybe I'll write an algorithm more efficient (the list is sorted) 
			gtk_tree_model_get_value(GTK_TREE_MODEL (listPackages),&iter,0,&value);
			package_name = (const char*)g_value_get_string(&value);
			if(strcmp(package_name,package_not_installed)==0) {
				sprintf(text_row,"<span foreground=\"red\"><b>%s</b></span>",package_not_installed);
				gtk_list_store_set (listPackages, &iter, 0, text_row, -1);
			}
			g_value_unset (&value); // Reset it to its pristine state
		}while (gtk_tree_model_iter_next(GTK_TREE_MODEL (listPackages),&iter));

}

void on_btnInstall_clicked (GtkButton *button, gpointer user_data)
{
	GtkWidget *main_window = gtk_widget_get_toplevel ((GtkWidget*)button);
	if (listPackages==NULL){
		show_message(main_window, "Error", "Open a file with a list of packages to install, please", GTK_MESSAGE_ERROR);
		return;
	}
	print_info("Installing, wait a few minutes, please..");
	GtkTreeIter iter;
	int size=1024*10; //Attention: This value could be too small
	const char *package_name;
	char *all_packages_string = (char*)malloc(size);
	int pos=0,package_len,ret;
	GValue value = { 0, }; /* Gtk+ wants the type field initialized to 0 */
	gboolean notempty = gtk_tree_model_get_iter_first(GTK_TREE_MODEL (listPackages), &iter);
	if (notempty)
		do{
			gtk_tree_model_get_value(GTK_TREE_MODEL (listPackages),&iter,1,&value);
			if(g_value_get_boolean(&value)) { //Install only checked packets
				g_value_unset (&value); // Reset it to its pristine state
				gtk_tree_model_get_value(GTK_TREE_MODEL (listPackages),&iter,0,&value);
				package_name = (const char*)g_value_get_string(&value);
				package_len=strlen(package_name);
				strncpy(all_packages_string+pos,package_name,package_len);
				pos += package_len;
				all_packages_string[pos]='\n';
				all_packages_string[++pos]='\0';
			}
			g_value_unset (&value);
		}while (gtk_tree_model_iter_next(GTK_TREE_MODEL (listPackages),&iter));

	GtkComboBox *cmbDistro = (GtkComboBox *) G_OBJECT (user_data);
	ret = installPackets((char *)gtk_combo_box_get_active_id(cmbDistro),all_packages_string, &checkResult);
	if (ret)
		show_message(main_window, "Success", "You may see in the list some packages highlighted in red. These packages maybe aren't installed successfully. Try manually, please.", GTK_MESSAGE_OTHER);
	else
		show_message(main_window, "Error", "Failed to open file with results.", GTK_MESSAGE_ERROR);

	print_info("Done");
}
