#include <gtk/gtk.h>

void activate();

void clicked_stub(GtkWidget* widget, gpointer data) {}


void clicked_button(GtkWidget* widget, gpointer data)
{
    gtk_main_quit();
}

void LoadCss(){
    // CSS読み込む際に必要です.
    GtkCssProvider* provider = gtk_css_provider_new();
    GError* error;

    // CSSファイルの読み込み.
    gtk_css_provider_load_from_path(provider, "./test.css", &error);

    if( error != NULL ){
        // 読み込み失敗.
        // exit(EXIT_FAILURE);
        return;
    }

    // 読み込んだCSSの適用
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}


GtkWidget*  button_with_modify_font(const char * caption) 
{
    //  = gtk_button_new_with_label(caption);
    GtkWidget*  widget = gtk_button_new_with_label("");

    GtkWidget*  
    label = gtk_bin_get_child(widget);

    char str[32];
    sprintf(str, "<b>%s</b>", caption);
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

int main (int argc, char* argv[])
{
    LoadCss();

    GtkWidget* window;
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_fullscreen((GtkWindow*)window);
    gtk_window_set_title(GTK_WINDOW(window), "Panel");
 
    GtkWidget   *grid;
    grid    =   gtk_grid_new();
    gtk_grid_set_row_spacing        (GTK_GRID(grid),    4          );
    gtk_grid_set_column_spacing     (GTK_GRID(grid),    4          );
    gtk_grid_set_row_homogeneous    (GTK_GRID(grid),    TRUE        );
    gtk_grid_set_column_homogeneous (GTK_GRID(grid),    TRUE        );
    gtk_container_add               (GTK_CONTAINER(window), grid    );

    GtkWidget   *wifi_status;
    GtkWidget   *main_status;
    GtkWidget   *mobility_status;

    GtkWidget   *start_stop;

    GtkWidget   *info2;
    GtkWidget   *power;
    GtkWidget   *preference;

    GtkButton  *exit;


    /*  Buttons         */
    wifi_status    = button_with_modify_font       ("wifi"     );
    main_status    = button_with_modify_font       ("status"  );
    mobility_status    = button_with_modify_font       ("connection" );
    start_stop    = button_with_modify_font       ("START/STOP"    );
    info2    = button_with_modify_font       ("info"     );
    power    = button_with_modify_font       ("Power"  );
    preference    = button_with_modify_font       ("Preference" );
    exit = button_with_modify_font("Exit" );
 
    /*  Attach to grid  */
    gtk_grid_attach (GTK_GRID(grid), wifi_status, 0, 0, 1, 1);
    gtk_grid_attach  (GTK_GRID(grid), main_status, 1, 0, 1, 1);
    gtk_grid_attach  (GTK_GRID(grid), mobility_status, 2, 0, 1, 1);

    gtk_grid_attach (GTK_GRID(grid), start_stop, 0, 1, 2, 1);
    gtk_grid_attach (GTK_GRID(grid), info2, 2, 1, 1, 1);

    gtk_grid_attach (GTK_GRID(grid), power, 0, 2, 1, 1);
    gtk_grid_attach  (GTK_GRID(grid), preference, 1, 2, 1, 1);
    gtk_grid_attach (GTK_GRID(grid), exit, 2, 2, 1, 1);

    g_signal_connect(wifi_status,  "clicked",G_CALLBACK(clicked_stub), window  );
    g_signal_connect(main_status, "clicked", G_CALLBACK(clicked_stub), window  );
    g_signal_connect(start_stop,  "clicked", G_CALLBACK(clicked_stub), window  );
    g_signal_connect(start_stop,"clicked", G_CALLBACK(clicked_stub), window  );
    g_signal_connect(exit, "clicked", G_CALLBACK(clicked_button), NULL);

    gtk_widget_show_all(window);
    gtk_main(); 

    return 0;
}