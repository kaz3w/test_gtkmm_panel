#include <string>
#include <unistd.h>
#include <libgen.h>
#include <linux/limits.h>
#include <gtk/gtk.h>

std::string getpath() 
{
  char buf[PATH_MAX + 1];

  if (readlink("/proc/self/exe", buf, sizeof(buf) - 1) == -1)
  	throw std::string("readlink() failed");
  std::string str(buf);
  return str.substr(0, str.rfind('/'));
}

GtkWidget*  button_with_modify_font(const char * caption) 
{
    GtkWidget*  widget = gtk_button_new_with_label("");
    GtkWidget*  label = gtk_bin_get_child(reinterpret_cast<GtkBin *>(widget));

    char str[32] = {0};
    snprintf(str, 31, "<b>%s</b>", caption);
    gtk_label_set_markup(GTK_LABEL(label), str);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);

    PangoAttrList *attrlist = pango_attr_list_new();
    PangoAttribute *attr = pango_attr_size_new_absolute(80 * PANGO_SCALE);
    pango_attr_list_insert(attrlist, attr);
    gtk_label_set_attributes(GTK_LABEL(label), attrlist);
    pango_attr_list_unref(attrlist);
    gtk_widget_show(label);
    return widget;
}