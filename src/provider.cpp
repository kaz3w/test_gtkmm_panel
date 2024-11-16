#include <gtk/gtk.h>
#include "utils.h"

bool LoadCss(){

    GtkCssProvider *provider = gtk_css_provider_new();
    GError* error;

    std::string css_path = getpath() + "/test.css";
    gtk_css_provider_load_from_path(provider, css_path.c_str(), &error);

    if( error != NULL ){
        // exit(EXIT_FAILURE);
        return false;
    }
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    return true;
}
