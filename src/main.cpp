#include <gtk/gtk.h>
#include <list>
#include "typedefs.h"
#include "utils.h"
#include "provider.hpp"
#include "button_stub.hpp"
#include "button_wifi.hpp"
#include "button_main.hpp"
#include "button_exit.hpp"


static void
activate(GtkApplication* app, gpointer user_data)
{
    GtkWidget *window;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
    gtk_widget_show_all (window);
}


int main (int argc, char* argv[])
{
#if 1
    LoadCss();

    GtkWidget *window;
    GtkWidget *grid;

    std::list<MY_WIDGET_PARAM> widgets = {{
        NULL, clicked_wifi, "stat1",   0, 0, 1, 1 },{
        NULL, clicked_main, "stat2",   1, 0, 1, 1 },{
        NULL, clicked_stub, "stat3",   2, 0, 1, 1 },{
        NULL, clicked_stub, "Start/Stop",   0, 1, 2, 1 },{
        NULL, clicked_stub, "info",   2, 1, 1, 1 },{
        NULL, clicked_stub, "Power",   0, 2, 1, 1 },{
        NULL, clicked_stub, "Preference",   1, 2, 1, 1 },{
        NULL, clicked_exit_button, "Exit",   2, 2, 1, 1
        }};

    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_fullscreen((GtkWindow*)window);
    gtk_window_set_title(GTK_WINDOW(window), "Panel");
 
    grid = gtk_grid_new();
    gtk_grid_set_row_spacing        (GTK_GRID(grid),    4          );
    gtk_grid_set_column_spacing     (GTK_GRID(grid),    4          );
    gtk_grid_set_row_homogeneous    (GTK_GRID(grid),    TRUE        );
    gtk_grid_set_column_homogeneous (GTK_GRID(grid),    TRUE        );
    gtk_container_add               (GTK_CONTAINER(window), grid    );

    for (auto it = widgets.begin(); it != widgets.end(); it++)
    {
        (*it).widget = button_with_modify_font((*it).caption.c_str());
        gtk_grid_attach (GTK_GRID(grid), (*it).widget, (*it).x, (*it).y, (*it).w, (*it).h);
        g_signal_connect( (*it).widget, "clicked", G_CALLBACK((*it).cb), window );
    }
    gtk_widget_show_all(window);
    gtk_main();
#else
    GtkApplication *app;
    int status;
    app = gtk_application_new ("jp.otsl.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);
    return status;
#endif
}