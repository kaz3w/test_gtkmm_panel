#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gio/gio.h>
#include <glib.h>
// #include <NetworkManager.h>
// #include <iostream>
#include "button_wifi.hpp"

static gint count = 0;

void clicked_wifi(GtkWidget* widget, gpointer data) {}

// libnm-dev, network-manager-dev, libnma-dev

// static void
// print_setting(const char *setting_name, GVariant *setting)
// {
//     GVariantIter iter;
//     const char * property_name;
//     GVariant *   value;
//     char *       printed_value;

//     g_print("  %s:\n", setting_name);
//     g_variant_iter_init(&iter, setting);
//     while (g_variant_iter_next(&iter, "{&sv}", &property_name, &value)) {
//         printed_value = g_variant_print(value, FALSE);
//         if (strcmp(printed_value, "[]") != 0)
//             g_print("    %s: %s\n", property_name, printed_value);
//         g_free(printed_value);
//         g_variant_unref(value);
//     }
// }

gboolean wifi_timer_cb(gpointer data) 
{
	GtkLabel *label = GTK_LABEL(data);

	const char *caption = "Wi-Fi ";
	char str[1024] = {0};

	const char *wifi_ssid = "unavailable";

    // struct wapi_interface iface;
    // wapi_get_interface("wlan0", &iface);
    // printf("SSID: %s\n", iface.ssid);

	int sec = ++count;
	int h = (count/10) / 3600;
	int m =  (count/10) / 60;
	int s =  (count/10) % 60;
	int ms = count % 10;

	snprintf(str, sizeof(str) - 1, "<span foreground='white' size='x-large'><b>%s</b></span>\n"
	"<span foreground='white'>%s</span>",
	//"<span color='lightgreen'><b>%02d:%02d:%02d</b></span>", 
	caption, wifi_ssid
	// ,h,m,s
	);
	
	gtk_label_set_markup(GTK_LABEL(label), str);
	gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
	
	int size = 40;
	PangoAttrList *attrlist = pango_attr_list_new();
	PangoAttribute *attr = pango_attr_size_new_absolute(size * PANGO_SCALE);
	pango_attr_list_insert(attrlist, attr);
	gtk_label_set_attributes(GTK_LABEL(label), attrlist);
	pango_attr_list_unref(attrlist);

	return true;
}
