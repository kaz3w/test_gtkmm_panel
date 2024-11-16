#ifndef __TYPEDEFS_HH__INCLUDED__
#define __TYPEDEFS_HH__INCLUDED__

#include <gtk/gtk.h>
#include <string>

typedef struct  
{
    GtkWidget* widget;
    void (*cb)(GtkWidget*, void*);
    std::string caption;
    gint x;
    gint y;
    gint w;
    gint h;
}  MY_WIDGET_PARAM;

#endif //!__TYPEDEFS_HH__INCLUDED__
