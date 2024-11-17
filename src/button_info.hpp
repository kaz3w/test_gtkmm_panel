#ifndef __BUTTON_INFO_H__INCLUDED__
#define __BUTTON_INFO_H__INCLUDED__

#include <gtk/gtk.h>

extern void clicked_info(GtkWidget* widget, gpointer data);
extern gboolean info_timer_cb(gpointer data);

#endif //!__BUTTON_INFO_H__INCLUDED__

