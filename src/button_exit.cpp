#include <stdio.h>
#include <stdlib.h>
#include "button_exit.hpp"

void clicked_exit_button(GtkWidget* widget, gpointer data)
{
    GtkWidget *dialog;
    GtkWidget *parent;
    GtkWidget *label;
    gint response;

    parent = GTK_WIDGET(data);


    //YES、NOボタン付きのダイアログを生成
    dialog = gtk_dialog_new_with_buttons("EXit Confirmation", 
                                        GTK_WINDOW(parent), 
                                        GTK_DIALOG_MODAL,
                                        "Exit Panel", 
                                        GTK_RESPONSE_YES, 
                                        "Cancel", 
                                        GTK_RESPONSE_REJECT, 
                                        NULL);

    label = gtk_label_new("Exit or  Cancel");
    gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), label);
    gtk_widget_set_size_request(dialog, 400, 100);
    gtk_widget_show_all(dialog);
    gtk_window_fullscreen((GtkWindow*)dialog);


    response = gtk_dialog_run(GTK_DIALOG(dialog));
    if( response == GTK_RESPONSE_NO )
    {
        gtk_main_quit();
    }
    else if( response == GTK_RESPONSE_YES )
    {
        gtk_main_quit();
    }
    else{
        g_print( "Another response was received.\n" );
    }
    gtk_widget_destroy(dialog);
}
