#ifndef WINDOW_H
#define WINDOW_H

#include <gtk/gtk.h>

GtkWidget *** boxes; // the grid of textboxes
char **unsolvedBoard; // the board before solve was clicked

static void activate(GtkApplication *app, gpointer user_data);
void app_new (int argc, char **argv);

#endif //end WINDOW_H header guard
