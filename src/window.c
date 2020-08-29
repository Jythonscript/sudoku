#ifdef USE_GTK

#include <stdlib.h>
#include <gtk/gtk.h>
#include "sudoku.h"
#include "input.h"

GtkWidget *** boxes; // the grid of textboxes
char **unsolvedBoard; // the board before solve was clicked

// write the 2d char array to the textboxes
void writeBoardToWindow(char **board) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			char str[2];
			sprintf(str, "%d", board[i][j]);
			if (str[0] == '0') {
				gtk_entry_set_text((GtkEntry *)boxes[i][j], "");
			}
			else {
				gtk_entry_set_text((GtkEntry *)boxes[i][j], str);
			}
		}
	}
}

// solve the board
void solve_button_clicked(GtkButton *button, gpointer user_data) {
	puts("solve button clicked");

	// save board as 2d char array
	char **inputBoard = createBoard();
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			// TODO - add safety check to ensure valid characters
			char *temp = g_strndup(gtk_entry_get_text((GtkEntry *)boxes[i][j]), 1);
			inputBoard[i][j] = (char) atoi(temp);
		}
	}

	// make a backup of the board
	boardcpy(inputBoard, unsolvedBoard, 9);

	// solve the board
	int status = solve(inputBoard, 0);

	// stop if the board is not solvable
	if (status == 0) {
		return;
	}

	// write the solved board to the textboxes
	writeBoardToWindow(inputBoard);
	/*
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			char str[2];
			sprintf(str, "%d", inputBoard[i][j]);
			gtk_entry_set_text((GtkEntry *)boxes[i][j], str);
		}
	}
	*/

	// free the temporary solving board
	deleteBoard(inputBoard);
}

// clear all of the textboxes on the board
void reset_button_clicked(GtkButton *button, gpointer user_data) {
	puts("reset button clicked");
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			gtk_entry_set_text((GtkEntry *)boxes[i][j], "");
		}
	}
}

// quit the program
void exit_button_clicked(GtkButton *button, gpointer user_data) {
	puts("exit button clicked");
	exit(0);
}

// return the board to the state it was in before the solve button was pressed
void unsolve_button_clicked(GtkButton *button, gpointer user_data) {
	puts("unsolve button clicked");
	writeBoardToWindow(unsolvedBoard);
}

// fill in one tile of the board, if one can be determined
void hint_button_clicked(GtkButton *button, gpointer user_data) {
	puts("hint button clicked");

	// transfer the textboxes to a char array
	char **inputBoard = createBoard();
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			// TODO - add safety check to ensure valid characters
			char *temp = g_strndup(gtk_entry_get_text((GtkEntry *)boxes[i][j]), 1);
			inputBoard[i][j] = (char) atoi(temp);
		}
	}

	// get the hint
	hint_t *hint = getHint(inputBoard);

	// apply the hint to the board, if a hint was found
	if (hint->value != -1) {
		char str[2];
		sprintf(str, "%d", hint->value);
		gtk_entry_set_text((GtkEntry *)boxes[hint->row][hint->column], str);
	}

	// free temporary resources used in this function
	deleteHint(hint);
	deleteBoard(inputBoard);
}

// show a dialog where the user can choose a board file to open
void file_button_clicked(GtkButton *button, gpointer user_data) {
	puts("file button clicked");

	GtkWidget *dialog;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;

	// set up the dialog
	dialog = gtk_file_chooser_dialog_new ("Open File",
			NULL, // parent window
			action,
			("Cancel"),
			GTK_RESPONSE_CANCEL,
			("Open"),
			GTK_RESPONSE_ACCEPT,
			NULL);

	// run the dialog
	res = gtk_dialog_run(GTK_DIALOG(dialog));

	// interpret the dialog response
	if (res == GTK_RESPONSE_ACCEPT) {
		char *filename;
		GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
		filename = gtk_file_chooser_get_filename(chooser);
		// read the board and write to the window
		printf("reading board from %s\n", filename);
		char **board = fileBoard(filename);
		writeBoardToWindow(board);
		// clean up memory
		g_free(filename);
	}
	gtk_widget_destroy(dialog);
}

// set up widgets onto window
static void activate(GtkApplication *app, gpointer user_data) {
	// set up board for undoing solve
	unsolvedBoard = createBoard();
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
	GtkWidget *hintButton;
	GtkWidget *unsolveButton;
	GtkWidget *fileButton;

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

	unsolveButton = gtk_button_new_with_label("Unsolve");
	gtk_grid_attach(GTK_GRID(gridMain), unsolveButton, 0, 4, 1, 1);
	g_signal_connect(GTK_BUTTON(unsolveButton),
			"clicked",
			G_CALLBACK(unsolve_button_clicked),
			G_OBJECT(window));

	hintButton = gtk_button_new_with_label("Hint");
	gtk_grid_attach(GTK_GRID(gridMain), hintButton, 1, 4, 1, 1);
	g_signal_connect(GTK_BUTTON(hintButton),
			"clicked",
			G_CALLBACK(hint_button_clicked),
			G_OBJECT(window));

	fileButton = gtk_button_new_with_label("Open file");
	gtk_grid_attach(GTK_GRID(gridMain), fileButton, 2, 4, 1, 1);
	g_signal_connect(GTK_BUTTON(fileButton),
			"clicked",
			G_CALLBACK(file_button_clicked),
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

#endif // USE_GTK
