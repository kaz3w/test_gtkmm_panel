#include "button_cart.hpp"

static gint count = 0;

void clicked_cart(GtkWidget* widget, gpointer data) {}

gboolean cart_timer_cb(gpointer data) 
{
	GtkLabel *label = GTK_LABEL(data);

	const char *caption = "Mobility";
	char str[1024] = {0};

	const char *stat = "unavailable";

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
	// "<span color='lightgreen'><b>%02d:%02d:%02d</b></span>", 
	caption, stat
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

}
