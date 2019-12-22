#include "window.h"

static void activate(GtkApplication *app, gpointer user_data) {
	// widgets
	GtkWidget *window;
	GtkWidget *fixed;
	GtkWidget *entryBox;
	GtkWidget *grid;

	// set up 2d array for boxes
	boxes = (GtkWidget ***) malloc(sizeof(GtkWidget **) * 9);
	GtkWidget **all_boxes = (GtkWidget **) malloc(sizeof(GtkWidget *) * 81);

	for (int i = 0; i < 9; i++) {
		boxes[i] = (all_boxes + (i * 9));
	}

	// set up window
	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW (window), "Sudoku");
	gtk_window_set_default_size(GTK_WINDOW (window), 1000, 800);

	// set up grid
	grid = gtk_grid_new();

	// place textboxes
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			GtkWidget *entry = gtk_entry_new();
			boxes[i][j] = entry;
			gtk_entry_set_width_chars((GtkEntry *)entry, 1);
			gtk_grid_attach(GTK_GRID(grid), boxes[i][j], i, j, 1, 1);
		}
	}

	// grid properties
	gtk_widget_set_margin_start((GtkWidget *) grid, 10);
	gtk_widget_set_margin_end((GtkWidget *) grid, 10);
	gtk_widget_set_margin_top((GtkWidget *) grid, 10);
	gtk_widget_set_margin_bottom((GtkWidget *) grid, 10);

	//gtk_grid_set_column_homogeneous((GtkGrid *)grid, TRUE);
	//gtk_grid_set_row_homogeneous((GtkGrid *)grid, TRUE);
	gtk_grid_set_column_spacing((GtkGrid *)grid, 10);
	gtk_grid_set_row_spacing((GtkGrid *)grid, 10);

	gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(grid));

	/*
	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), fixed);

	entryBox = gtk_entry_new();
	gtk_fixed_put(GTK_FIXED (fixed), entryBox, 100, 100);

	gtk_entry_set_width_chars((GtkEntry *)entryBox, 1);
	*/

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
