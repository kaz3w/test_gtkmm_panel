#ifndef __TYPEDEFS_H__INCLUDED__
#define __TYPEDEFS_H__INCLUDED__

#include <gtk/gtk.h>
#include <string>

typedef struct  
{
    bool label_only;
    GtkWidget* widget;
    void (*click_cb)(GtkWidget *, gpointer data);
    guint timer_id;
    gboolean (*timer_cb)(gpointer data);
    std::string caption;
    std::string bkColor;
    gint x;
    gint y;
    gint w;
    gint h;
}  MY_WIDGET_PARAM;

#endif //!__TYPEDEFS_H__INCLUDED__
