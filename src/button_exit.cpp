#include "button_exit.hpp"

void clicked_exit_button(GtkWidget* widget, gpointer data)
{
    gtk_main_quit();
}
