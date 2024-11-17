#include <cairo.h>
#include <gtk/gtk.h>
#include <list>
#include "typedefs.h"
#include "utils.h"
#include "provider.hpp"
#include "button_stub.hpp"
#include "button_cart.hpp"
#include "button_wifi.hpp"
#include "button_main.hpp"
#include "button_power.hpp"
#include "button_ss.hpp"
#include "button_info.hpp"
#include "button_exit.hpp"


static void
activate(GtkApplication* app, gpointer user_data)
{
    GtkWidget *window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
    gtk_widget_show_all (window);
}


int main (int argc, char* argv[])
{
    int status = EXIT_SUCCESS;

#if 1
    LoadCss();

    GtkWidget *window;
    GtkWidget *grid;

    std::list<MY_WIDGET_PARAM> widgets = {{
        true, NULL, NULL, 0, wifi_timer_cb, "stat1",   "lightgray", 0, 0, 1, 1 },{
        true, NULL, NULL, 0, main_timer_cb, "stat2",   "orange", 1, 0, 1, 1 },{
        true, NULL, NULL, 0, cart_timer_cb, "stat3",   "lightgray", 2, 0, 1, 1 },{
        false, NULL, clicked_ss, 0, NULL, "Start/Stop", "black",  0, 1, 2, 1 },{
        false, NULL, clicked_info, 0, NULL, "info",     "black",2, 1, 1, 1 },{
        false, NULL, clicked_power_button, 0, NULL, "Power",     "black",0, 2, 1, 1 },{
        false, NULL, clicked_stub, 0, NULL, "Preference",     "black",1, 2, 1, 1 },{
        false, NULL, clicked_exit_button, 0, NULL, "Exit",     "black",2, 2, 1, 1
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
        if ((*it).label_only) {
            (*it).widget = label_with_modify_font(window, (*it).caption.c_str(), (*it).bkColor.c_str());
        }
        else {
            (*it).widget = button_with_modify_font(window, (*it).caption.c_str());
            g_signal_connect( (*it).widget, "clicked", G_CALLBACK((*it).click_cb), window );
        }

        gtk_grid_attach (GTK_GRID(grid), (*it).widget, (*it).x, (*it).y, (*it).w, (*it).h);
        if ((*it).timer_cb) {
            (*it).timer_id = g_timeout_add(100, (GSourceFunc)(*it).timer_cb,(*it).widget);
        }
    }
    gtk_widget_show_all(window);
    gtk_main();

#else
    GtkApplication *app;
    app = gtk_application_new ("jp.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);
#endif
    return status;
}
