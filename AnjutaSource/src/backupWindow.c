#include "backupWindow.h"



void on_btnBackup_clicked (GtkButton *button, gpointer user_data)
{
	GtkComboBox *cmbDistro = (GtkComboBox *) G_OBJECT (user_data);
	GtkWidget *main_window = gtk_widget_get_toplevel ((GtkWidget*)button);
	int ret = savePackagesList((char*)gtk_combo_box_get_active_id(cmbDistro));
	char msg[100];
	if (ret == 0){
		sprintf(msg, "Package list saved into %s", OUTPUT_BACKUP_SCRIPT);
		show_message(main_window, "Finish",msg, GTK_MESSAGE_OTHER);
	}else{
		sprintf(msg, "%s failed.\nError code: %d", BACKUP_SCRIPT, ret);
		show_message(main_window, "Error", msg, GTK_MESSAGE_ERROR);
	}
}


void on_btnCancel_clicked (GtkButton *button, gpointer user_data)
{
	GtkWidget *window = (GtkWidget *)G_OBJECT (user_data);
	gtk_widget_destroy(window);
}