#ifndef __BUTTON_MAIN_H__INCLUDED__
#define __BUTTON_MAIN_H__INCLUDED__

#include <gtk/gtk.h>

extern void clicked_main(GtkWidget* widget, gpointer data);
extern gboolean main_timer_cb(gpointer data);

#endif //!__BUTTON_MAIN_H__INCLUDED__

