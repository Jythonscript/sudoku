#include <stdlib.h>
#include "window.h"
#include "sudoku.h"

void solve_button_clicked(GtkButton *button, gpointer user_data) {
	puts("solve button clicked");
	char **inputBoard = createBoard();
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			// TODO - add safety check to ensure valid characters
			char *temp = g_strndup(gtk_entry_get_text((GtkEntry *)boxes[i][j]), 1);
			inputBoard[i][j] = (char) atoi(temp);
		}
	}

	solve(inputBoard);
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			char str[2];
			sprintf(str, "%d", inputBoard[i][j]);
			gtk_entry_set_text((GtkEntry *)boxes[i][j], str);
		}
	}
}

void reset_button_clicked(GtkButton *button, gpointer user_data) {
	puts("reset button clicked");
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			gtk_entry_set_text((GtkEntry *)boxes[i][j], "");
		}
	}
}

void exit_button_clicked(GtkButton *button, gpointer user_data) {
	exit(0);
}

// set up widgets onto window
static void activate(GtkApplication *app, gpointer user_data) {
	// widgets
	GtkWidget *window;
	GtkWidget *fixed;
	GtkWidget *entryBox;
	GtkWidget *gridMain;
	GtkWidget *grids[3][3];
	// buttons
	GtkWidget *solveButton;
	GtkWidget *resetButton;
	GtkWidget *exitButton;

	// set up 2d array for boxes
	boxes = (GtkWidget ***) malloc(sizeof(GtkWidget **) * 9);
	GtkWidget **all_boxes = (GtkWidget **) malloc(sizeof(GtkWidget *) * 81);
	for (int i = 0; i < 9; i++) {
		boxes[i] = (all_boxes + (i * 9));
	}

	// set up window
	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW (window), "Sudoku");
	//gtk_window_set_default_size(GTK_WINDOW (window), 1000, 800);

	// set up grid
	gridMain = gtk_grid_new();

	// place textboxes
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			grids[i][j] = gtk_grid_new();
			for (int k = 0; k < 3; k++) {
				for (int l = 0; l < 3; l++) {
					int row = (i * 3) + k;
					int col = (j * 3) + l;
					// insert textboxes
					GtkWidget *entry = gtk_entry_new();
					boxes[row][col] = entry;
					gtk_entry_set_width_chars((GtkEntry *)entry, 1);
					gtk_grid_attach(GTK_GRID (grids[i][j]), boxes[row][col], k, l, 1, 1);

					gtk_grid_set_column_spacing((GtkGrid *)grids[i][j],2);
					gtk_grid_set_row_spacing((GtkGrid *)grids[i][j], 2);

					//gtk_grid_set_column_homogeneous((GtkGrid *)grids[i][j], TRUE);
					//gtk_grid_set_row_homogeneous((GtkGrid *)grids[i][j], TRUE);

					gtk_widget_set_margin_start((GtkWidget *) grids[i][j], 5);
					gtk_widget_set_margin_end((GtkWidget *) grids[i][j], 5);
					gtk_widget_set_margin_top((GtkWidget *) grids[i][j], 5);
					gtk_widget_set_margin_bottom((GtkWidget *) grids[i][j], 5);

					// insert grids into master grid
					gtk_grid_attach(GTK_GRID(gridMain), grids[i][j], i, j, 1, 1);
				}
			}
		}
	}

	// grid properties
	gtk_widget_set_margin_start((GtkWidget *) gridMain, 10);
	gtk_widget_set_margin_end((GtkWidget *) gridMain, 10);
	gtk_widget_set_margin_top((GtkWidget *) gridMain, 10);
	gtk_widget_set_margin_bottom((GtkWidget *) gridMain, 10);

	//gtk_grid_set_column_homogeneous((GtkGrid *)gridMain, TRUE);
	//gtk_grid_set_row_homogeneous((GtkGrid *)gridMain, TRUE);

	gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(gridMain));

	// set up buttons
	solveButton = gtk_button_new_with_label("Solve");
	gtk_grid_attach(GTK_GRID(gridMain), solveButton, 0, 3, 1, 1);
	g_signal_connect(GTK_BUTTON(solveButton),
			"clicked",
			G_CALLBACK(solve_button_clicked),
			G_OBJECT(window));

	resetButton = gtk_button_new_with_label("Reset");
	gtk_grid_attach(GTK_GRID(gridMain), resetButton, 1, 3, 1, 1);
	g_signal_connect(GTK_BUTTON(resetButton),
			"clicked",
			G_CALLBACK(reset_button_clicked),
			G_OBJECT(window));

	exitButton = gtk_button_new_with_label("Exit");
	gtk_grid_attach(GTK_GRID(gridMain), exitButton, 2, 3, 1, 1);
	g_signal_connect(GTK_BUTTON(exitButton),
			"clicked",
			G_CALLBACK(exit_button_clicked),
			G_OBJECT(window));

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
