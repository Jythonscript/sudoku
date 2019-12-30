#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <gtk/gtk.h>
#include "input.h"
#include "sudoku.h"
#include "window.h"

int main(int argc, char **argv) {

	char *helpstring = "Usage: sudoku [OPTION]\n"
					   "When no options are specified, a GTK user interface is ran\n"
					   "\n"
					   "  -i, --input		input the board in text\n"
					   "  -q, --quiet		reduce verbosity of instructional text in input\n"
					   "  -c, --color		print the board with the changed numbers colored in\n"
					   "  -h, --help		display this help and exit\n"
					   "  -z, --zeroes      print zeroes instead of blank spaces when printing the board\n"
					   "  -d, --debug		run solve on a test board\n"
					   "\n"
					   "Source: <https://github.com/Jythonscript/sudoku>";

	// flags
	char input = 0;
	char quiet = 0;
	char debug = 0;
	char color = 0;
	char printZeroes = 0;
	char window = (argc == 1) ? (1) : (0);

	// getopts
	while (1) {

		static struct option long_options[] = {
			{"input", no_argument, 0, 'i'},
			{"quiet", no_argument, 0, 'q'},
			{"color", no_argument, 0, 'c'},
			{"help", no_argument, 0, 'h'},
			{"debug", no_argument, 0, 'd'},
			{"zeroes", no_argument, 0, 'z'},
			{0, 0, 0, 0}
		};

		int option_index = 0;
		int c = getopt_long(argc, argv, "iqchdz", long_options, &option_index);

		if (c == -1) {
			break;
		}

		switch (c) {
			case 'i':
				input = 1;
				break;
			case 'q':
				quiet = 1;
				break;
			case 'c':
				color = 1;
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
				fprintf(stderr, "Error in parsing options\n");
				return 1;
			default:
				printf("No argument\n");
				return 0;
		}
	}

	if (debug) {
		char newBoard[9][9] = {{7,6,0,0,2,0,9,0,0}, {0,0,4,0,0,0,0,2,0}, {8,0,0,0,0,4,0,0,3}, {0,2,8,0,0,1,3,0,7}, {6,3,1,0,7,0,4,8,2}, {4,0,7,8,0,0,5,6,0}, {2,0,0,5,0,0,0,0,6}, {0,8,0,0,0,0,7,0,0}, {0,0,5,0,8,0,0,4,9}};
		//char newBoard[9][9] = {{0,0,2,1,0,5,0,6,0}, {9,0,5,4,0,0,3,0,0}, {0,0,1,0,2,9,0,0,0}, {0,0,4,0,0,0,0,1,0}, {8,0,0,9,0,2,0,0,6}, {0,0,0,0,0,0,2,0,0}, {0,0,0,0,5,0,0,0,0}, {0,0,7,0,0,6,1,0,2}, {0,1,0,3,0,4,8,0,0}};
		//char newBoard[9][9] = {{9, 6, 4, 1, 2, 7, 3, 8, 5}, {7, 3, 5, 6, 9, 8, 4, 1, 2}, {8, 1, 2, 3, 4, 5, 9, 7, 6}, {6, 2, 9, 7, 8, 1, 5, 3, 4}, {4, 8, 1, 5, 3, 2, 7, 6, 9}, {3, 5, 7, 4, 6, 9, 1, 2, 8}, {5, 9, 3, 8, 7, 6, 2, 4, 1}, {2, 4, 6, 9, 1, 3, 8, 5, 7}, {1, 7, 8, 2, 5, 4, 6, 9, 3}};

		// put the board into the heap so it can be passed as a parameter
		char **board = createBoard();
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				board[i][j] = newBoard[i][j];
			}
		}
		char **originalBoard = createBoard();
		boardcpy(board, originalBoard, 9);
		// show the original board, then solve it
		printf("Initial board\n");
		printBoard(board, printZeroes);

		if (solve(board)) {
			printf("\nSolved board\n");
			if (color) {
				printBoardDiff(originalBoard, board);
			}
			else {
				printBoard(board, printZeroes);
			}
		}
		else {
			printf("The board is not solvable\n");
		}
		deleteBoard(board);
	}
	else if (input) {
		char **board = readBoard(quiet);
		char **originalBoard = createBoard();
		boardcpy(board, originalBoard, 9);

		if (quiet == 0) {
			printf("Entered board\n");
			printBoard(board, printZeroes);
			putchar('\n');
		}

		if (isValid(board) && solve(board)) {
			printf("Solved board\n");
			if (color) {
				printBoardDiff(originalBoard, board);
			}
			else {
				printBoard(board, printZeroes);
			}
		}
		else {
			fprintf(stderr, "The board is not solvable\n");
		}

		// free allocated memory
		deleteBoard(board);
		deleteBoard(originalBoard);
	}
	// start GTK application if no command-line flags, like input or debug
	else if (window){
		puts("Ran GTK app");
		app_new(argc, argv);
	}

	return 0;
}
