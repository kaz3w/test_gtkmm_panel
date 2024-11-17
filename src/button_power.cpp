#include <stdio.h>
#include <stdlib.h>
#include "button_power.hpp"

void clicked_power_button(GtkWidget* widget, gpointer data)
{
    GtkWidget *dialog;
    GtkWidget *parent;
    GtkWidget *label;
    gint response;

    parent = GTK_WIDGET(data);

    dialog = gtk_dialog_new_with_buttons("Save Confirmation", 
                                        GTK_WINDOW(parent), 
                                        GTK_DIALOG_MODAL,
                                        "REBOOT",       GTK_RESPONSE_NO, 
                                        "Power OFF",    GTK_RESPONSE_YES, 
                                        "Cancel",       GTK_RESPONSE_REJECT, 
                                        NULL);

    label = gtk_label_new("REBOOT, Power OFF or CANCEL ?");
    gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), label);
    gtk_widget_set_size_request(dialog, 400, 100);
    gtk_widget_show_all(dialog);
    gtk_window_fullscreen((GtkWindow*)dialog);

    response = gtk_dialog_run(GTK_DIALOG(dialog));
    if( response == GTK_RESPONSE_NO )
    {
        gtk_main_quit();
        system("sudo /usr/bin/sudo reboot");
    }
    else if( response == GTK_RESPONSE_YES )
    {
        gtk_main_quit();
        system("sudo /usr/bin/sudo poweroff");
    }
    else{
        g_print( "Another response was received.\n" );
    }
    gtk_widget_destroy(dialog);
}
