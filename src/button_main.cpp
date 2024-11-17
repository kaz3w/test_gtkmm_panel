#include "button_main.hpp"
#include <stdio.h>
#include <time.h>

static gint count = 0;

void clicked_main(GtkWidget* widget, gpointer data) {

	// GtkLabel *label = GTK_LABEL(widget);
	// gchar format[] = "%2d";
	// gchar str[9];
	// g_snprintf(str, sizeof(str), format, ++count);
	// gtk_label_set_text(label, str);
}


gboolean main_timer_cb(gpointer data) 
{
	GtkLabel *label = GTK_LABEL(data);

	const char *current_status = "Ready";
	char buf[32] = {0};
	time_t current_time = time(NULL);
	struct tm tm_result;
	localtime_r(&current_time, &tm_result);

	const char *w_text[7] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
	const char *w_jtext[7] = {"日曜日","月曜日","火曜日","水曜日","木曜日","金","土曜日"};
	const char *w_color[7] = {"red", "white", "white", "white", "white", "white", "lightblue"};
	const char *w_color2[7] = {"red", "black", "black", "black", "black", "black", "blue"};

	char str[1024] = {0};
	int sec = ++count;
	int h = (count/10) / 3600;
	int m =  (count/10) / 60;
	int s =  (count/10) % 60;
	int ms = count % 10;

	snprintf(str, sizeof(str)-1, "<span fgcolor='black' bgcolor='orange'>%d-%d-%d</span><span color='%s'>(%s)</span>\n"
								// "<span fgcolor='black' bgcolor='orange' font_desc='DSEG7 Classic' style='normal' font_weight='bold'>%02d:%02d:%02d</span>\n"
								"<span fgcolor='black' bgcolor='orange'><b>%02d:%02d:%02d</b></span>\n"
								"<span fgcolor='black' bgcolor='orange' size='x-large'><b>%s</b></span>\n"
								"<span fgcolor='red' bgcolor='orange'><b>%02d:%02d:%02d.%d</b></span>",
					 tm_result.tm_year+1900, tm_result.tm_mon, tm_result.tm_mday, w_color2[tm_result.tm_wday], w_text[tm_result.tm_wday],
					 tm_result.tm_hour, tm_result.tm_min, tm_result.tm_sec,
					current_status,
					h, m, s, ms);
					 
	gtk_label_set_markup(GTK_LABEL(label), str);
	gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
	
	int size = 40;
	PangoAttrList *attrlist = pango_attr_list_new();
	PangoAttribute *attr = pango_attr_size_new_absolute(size * PANGO_SCALE);
	pango_attr_list_insert(attrlist, attr);
	gtk_label_set_attributes(GTK_LABEL(label), attrlist);
	pango_attr_list_unref(attrlist);

	return true;
}
