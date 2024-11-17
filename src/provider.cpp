#include <gtk/gtk.h>
#include "utils.h"
#include "provider.hpp"

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



void test_provider()
{
    GtkCssProvider *provider;
    provider = gtk_css_provider_new ();

    GdkDisplay *display;
    GdkScreen *screen;
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen,
        GTK_STYLE_PROVIDER (provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gtk_css_provider_load_from_data (GTK_CSS_PROVIDER(provider),
        " GtkWindow {\n"
        "   background-color: rgb (103, 103, 103);\n"
        "}\n", -1, NULL);
    g_object_unref (provider);   
}