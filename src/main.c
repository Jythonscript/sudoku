#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "input.h"
#include "sudoku.h"
#include "window.h"

#ifdef USE_GTK
#include <gtk/gtk.h>
#endif

int main(int argc, char **argv) {

	char *helpstring = "Usage: sudoku [OPTION]\n"
#ifdef USE_GTK
					   "When no options are specified, a GTK user interface is ran\n"
#endif
					   "\n"
					   "Input control:\n"
					   "  -f, --file        input the board through the specified text file\n"
#ifdef USE_READLINE
					   "  -i, --input       input the board through readline\n"
#endif
					   "\n"
					   "Output control:\n"
					   "  -c, --color       print the board with the changed numbers colored in\n"
					   "  -q, --quiet       reduce verbosity of instructional text in input\n"
					   "  -t, --hint        print only a hint to solving the board, then exit\n"
					   "  -z, --zeroes      print zeroes instead of blank spaces when printing the board\n"
					   "\n"
					   "Miscellaneous:\n"
					   "  -d, --debug       print additional info before solving\n"
					   "  -h, --help        display this help and exit\n"
					   "\n"
					   "Source: <https://github.com/Jythonscript/sudoku>";

	int filename_len = 30;

	// flags
	char input = 0;
	char useFile = 0;
	char *filename = (char *) malloc(sizeof(char *) * filename_len);
	char quiet = 0;
	char debug = 0;
	char color = 0;
	char printZeroes = 0;
	char hint = 0;
	char window = (argc == 1) ? (1) : (0);

	// getopts
	while (1) {

		static struct option long_options[] = {
			{"file", required_argument, 0, 'f'},
			{"input", no_argument, 0, 'i'},
			{"quiet", no_argument, 0, 'q'},
			{"color", no_argument, 0, 'c'},
			{"hint", no_argument, 0, 't'},
			{"zeroes", no_argument, 0, 'z'},
			{"debug", no_argument, 0, 'd'},
			{"help", no_argument, 0, 'h'},
			{0, 0, 0, 0}
		};

		int option_index = 0;
		int c = getopt_long(argc, argv, "f:cdhiqzt", long_options, &option_index);

		if (c == -1) {
			break;
		}

		switch (c) {
			case 'i':
				input = 1;
				break;
			case 'f':
				useFile = 1;
				// copy the filename from 'optarg' to 'filename'
				int current_index = 0;
				do {
					if (current_index >= filename_len) {
						filename_len *= 2;
						filename = realloc(filename, filename_len);
					}
					if (filename == NULL) {
						fputs("invalid filename\n", stderr);
						exit(1);
					}
					else {
						filename[current_index] = optarg[current_index];
					}
				} while (optarg[current_index++] != '\0');
				break;
			case 'q':
				quiet = 1;
				break;
			case 'c':
				color = 1;
				break;
			case 't':
				hint = 1;
				break;
			case 'h':
				puts(helpstring);
				return 0;
			case 'd':
				debug = 1;
				break;
			case 'z':
				printZeroes = 1;
				break;
			case '?':
				return 1;
			default:
				printf("No argument\n");
				return 0;
		}
	}

	// start GTK application if no command-line arguments specified
	if (window){
#ifdef USE_GTK
		puts("Ran GTK app");
		app_new(argc, argv);
#else
		puts(helpstring);
#endif
	}
	// otherwise run the solver
	else {
		char **board;
		char **originalBoard;

		if (useFile) {
			board = fileBoard(filename);
		}
		else if (input) {
#ifdef USE_READLINE
			board = readBoard(quiet);
#else
			fprintf(stderr, "-i flag not supported, sudoku not compiled with readline support\n");
			exit(1);
#endif
		}
		originalBoard = createBoard();
		boardcpy(board, originalBoard, 9);

		if (!quiet) {
			printf("Entered board\n");
			printBoard(board, printZeroes);
			putchar('\n');
		}

		if (!hint && isValid(board) && solve(board, debug)) {
			printf("Solved board\n");
			if (color) {
				printBoardDiff(originalBoard, board, printZeroes);
			}
			else {
				printBoard(board, printZeroes);
			}
		}
		else if (hint) {
			char **firstBoard = createBoard();
			boardcpy(board, firstBoard, 9);

			hint_t *hint = getHint(board);

			if (hint->value == -1) {
				printf("No hint found\n");
			}
			else {
				printBoardDiff(firstBoard, board, printZeroes);
			}
			deleteBoard(firstBoard);
		}
		else {
			fprintf(stderr, "The board is not solvable\n");
		}

		// free allocated memory
		deleteBoard(board);
		deleteBoard(originalBoard);
	}

	return 0;
}
