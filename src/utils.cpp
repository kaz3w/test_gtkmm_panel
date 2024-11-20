#include <string>
#include <unistd.h>
#include <libgen.h>
#include <linux/limits.h>
#include <gtk/gtk.h>
#include <gdk/gdkrgba.h>
#include "utils.h"

std::string getpath() 
{
  char buf[PATH_MAX + 1];

  if (readlink("/proc/self/exe", buf, sizeof(buf) - 1) == -1)
  	throw std::string("readlink() failed");
  std::string str(buf);
  return str.substr(0, str.rfind('/'));
}


GdkRGBA colorBlack;
GdkRGBA colorBlue;
GdkRGBA colorRed;
GdkRGBA colorGreen;
GdkRGBA colorYellow;
GdkRGBA colorGray;
GdkRGBA colorLightGray;
GdkRGBA colorCustom01 = {0, 0xAAAA, 0x1234, 0xF0F0};
GdkRGBA colorCustom02;

void
set_panel_color (void)
{
  gdk_rgba_parse (&colorBlack, "black");
  gdk_rgba_parse (&colorBlue, "#000080");
  gdk_rgba_parse (&colorRed, "red");
  gdk_rgba_parse (&colorGreen, "lightgreen");
  gdk_rgba_parse (&colorYellow, "yellow" );
  gdk_rgba_parse (&colorGray, "gray");
  gdk_rgba_parse (&colorLightGray, "lightgray");
  gdk_rgba_parse (&colorCustom02, "#20F0DF");
}



static void do_drawing (cairo_t *, GtkWidget * widget);

struct
{
  cairo_surface_t *image;
} glob;

static gboolean
on_draw_event (GtkWidget * widget, cairo_t * cr, gpointer user_data)
{
  cr = gdk_cairo_create (gtk_widget_get_window (widget));
  do_drawing (cr, widget);
  cairo_destroy (cr);

  return FALSE;
}


static void
do_drawing (cairo_t * cr, GtkWidget * widget)
{
  gfloat screen_width;
  gfloat screen_height;
  gfloat image_width;
  gfloat image_height;
  gfloat x_scaling;
  gfloat y_scaling;

  /* Display screen dimension in console  */
  screen_width = gdk_screen_get_width (gdk_screen_get_default ());
  screen_height = gdk_screen_get_height (gdk_screen_get_default ());
  g_message ("Screen width %f", screen_width);
  g_message ("Screen height %f", screen_height);

  /* Scale the loaded image to occupy the entire screen  */
  image_width = cairo_image_surface_get_width (glob.image);
  image_height = cairo_image_surface_get_height (glob.image);

  g_message ("Image width %f", image_width);
  g_message ("Image height %f", image_height);

  x_scaling = screen_width / image_width;
  y_scaling = screen_height / image_height;

  g_message ("x_scaling %f", x_scaling);
  g_message ("y_scaling %f", y_scaling);

  cairo_scale (cr, x_scaling, y_scaling);

  cairo_set_source_surface (cr, glob.image, 0, 0);
  cairo_paint (cr);
}


static void
load_image ()
{
  glob.image =
    cairo_image_surface_create_from_png ("/home/pi/local/test_gtkmm_panel/icon/amr_200x200.png");
}



static void
draw_mark ()
{
  cairo_t *ic;
  ic = cairo_create (glob.image);
  cairo_set_font_size (ic, 11);

  cairo_set_source_rgb (ic, 0.9, 0.9, 0.9);
  cairo_move_to (ic, 100, 100);
  cairo_show_text (ic, " 343 Industries 2013 , (c) Pinczakko ");
  cairo_stroke (ic);
}


//#define _USE_HBOX

GtkWidget*  label_with_modify_font( GtkWidget *window, const char * caption, const char* bkColor, int size ) 
{
  load_image ();
  draw_mark ();
  set_panel_color();

#ifdef _USE_HBOX
  GtkWidget *hbox = gtk_hbox_new(FALSE, 2);
  GtkWidget *icon = gtk_label_new("");
#else
#endif
  GtkWidget *label = gtk_label_new(caption);

  GdkRGBA colorBk;
  gdk_rgba_parse(&colorBk, bkColor);

  // gtk_widget_modify_bg(label, GTK_STATE_NORMAL, &colorBk);
  gtk_widget_override_background_color( label, GTK_STATE_FLAG_NORMAL, &colorBk);

  char str[1024] = {0};
  snprintf(str, sizeof(str)-1, "<span foreground='white' background='lightblue'>َ<b>%s</b></span>", caption);
  gtk_label_set_markup(GTK_LABEL(label), str);
  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);

  PangoAttrList *attrlist = pango_attr_list_new();
  PangoAttribute *attr = pango_attr_size_new_absolute(size * PANGO_SCALE);
  pango_attr_list_insert(attrlist, attr);
  gtk_label_set_attributes(GTK_LABEL(label), attrlist);
  pango_attr_list_unref(attrlist);
  gtk_widget_show(label);

#ifdef _USE_HBOX
  // GtkWidget *icon;
  // icon = gtk_image_new_from_file ("/home/pi/local/test_gtkmm_panel/icon/amr.png");

  GtkWidget *darea = gtk_drawing_area_new ();
  g_signal_connect (G_OBJECT (darea), "draw", G_CALLBACK (on_draw_event), NULL);

  gtk_box_pack_start (GTK_BOX (hbox), darea, TRUE, TRUE, 2);
  gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 2);
  return hbox;
#else
  return label;
#endif
}


GtkWidget*  button_with_modify_font( GtkWidget *window, const char * caption, int size ) 
{
  set_panel_color();

  GtkWidget *button = gtk_button_new();
  GtkWidget *label = gtk_label_new_with_mnemonic (caption);
  gtk_container_add (GTK_CONTAINER (button), label);

  char str[128] = {0};
  snprintf(str, sizeof(str) - 1, "<span><b>%s</b></span>", caption);
  gtk_label_set_markup(GTK_LABEL(label), str);
  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);

  PangoAttrList *attrlist = pango_attr_list_new();
  PangoAttribute *attr = pango_attr_size_new_absolute(size * PANGO_SCALE);
  pango_attr_list_insert(attrlist, attr);
  gtk_label_set_attributes(GTK_LABEL(label), attrlist);
  pango_attr_list_unref(attrlist);
  gtk_widget_show(label);

  return button;
}