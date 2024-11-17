#include "gtk/gtk.h"
#include "utils.h"
#include "button_info.hpp"

static gint count = 0;
static guint timer_id;


void clicked_info(GtkWidget* widget, gpointer data)
{
    GtkWidget *dialog;
    GtkWidget *parent;
    GtkWidget *label;
    gint response;

    parent = GTK_WIDGET(data);

    //YES、NOボタン付きのダイアログを生成
    dialog = gtk_dialog_new_with_buttons("Information", 
                                        GTK_WINDOW(parent), 
                                        GTK_DIALOG_MODAL,
                                        "Close",    GTK_RESPONSE_YES, 
                                        NULL);

    label = gtk_label_new("");

	gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &colorBlue);

	char str[1024] = {0};
	snprintf(str, sizeof(str) - 1, "<span background=#00FF007F>َ</span><b>Information</b><br>12345");
	gtk_label_set_markup(GTK_LABEL(label), str);
	gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);

	PangoAttrList *attrlist = pango_attr_list_new();
	int size = 60;
	PangoAttribute *attr = pango_attr_size_new_absolute(size * PANGO_SCALE);
	pango_attr_list_insert(attrlist, attr);
	gtk_label_set_attributes(GTK_LABEL(label), attrlist);
	pango_attr_list_unref(attrlist);
	gtk_widget_show(label);

    gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), label);
    // gtk_widget_set_size_request(dialog, 400, 100);
    gtk_widget_show_all(dialog);
    gtk_window_fullscreen((GtkWindow*)dialog);

    response = gtk_dialog_run(GTK_DIALOG(dialog));
    if( response == GTK_RESPONSE_YES )
    {
	    gtk_widget_destroy(dialog);
    }
    else{
        g_print( "Another response was received.\n" );
    }
}


gboolean info_timer_cb(gpointer data) 
{
	return TRUE;
}
