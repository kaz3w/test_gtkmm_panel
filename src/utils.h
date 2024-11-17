#ifndef __UTILS_H__INCLUDED__
#define __UTILS_H__INCLUDED__

#include <gtk/gtk.h>
#include <string>

extern std::string getpath();
extern GtkWidget*  label_with_modify_font(GtkWidget *window, const char * caption, const char* bkColor, int size=80 );
extern GtkWidget*  button_with_modify_font(GtkWidget *window, const char * caption, int size=80 );

extern void set_panel_color (void);

extern GdkRGBA colorBlack;
extern GdkRGBA colorBlue;
extern GdkRGBA colorRed;
extern GdkRGBA colorGreen;
extern GdkRGBA colorYellow;
extern GdkRGBA colorGray;
extern GdkRGBA colorLightGray;
extern GdkRGBA colorCustom01;
extern GdkRGBA colorCustom02;

#endif //!__UTILS_H__INCLUDED__
