#include "window.h"

static void activate(GtkApplication *app, gpointer user_data) {
	GtkWidget *window;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW (window), "Sudoku");
	gtk_window_set_default_size(GTK_WINDOW (window), 1000, 800);

	gtk_widget_show_all(window);
}

void app_new (int argc, char **argv) {
	GtkApplication *app;
	int status;

	app = gtk_application_new("org.github.jythonscript.sudoku", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run(G_APPLICATION (app), argc, argv);
	g_object_unref(app);
}
