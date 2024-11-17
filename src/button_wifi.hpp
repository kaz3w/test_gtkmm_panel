#ifndef __BUTTON_WIFI_H__INCLUDED__
#define __BUTTON_WIFI_H__INCLUDED__

#include <gtk/gtk.h>

extern void clicked_wifi(GtkWidget* widget, gpointer data);
extern gboolean wifi_timer_cb(gpointer data);

#endif //!__BUTTON_WIFI_H__INCLUDED__

