#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "input.h"
#include "sudoku.h"

int main(int argc, char **argv) {

	char *helpstring = "Usage: sudoku [OPTION]\n"
					   "  -i, --input		input the board in text\n"
					   "  -q, --quiet		reduce verbosity of instructional in input\n"
					   "  -h, --help		display this help and exit\n"
					   "      --debug		run solve on a test board\n"
					   "\nSource: <https://github.com/Jythonscript/sudoku>";

	// flags
	char input = 0;
	char quiet = 0;
	char debug = 0;

	if (argc == 1) {
		puts(helpstring);
		return 0;
	}

	// getopts
	while (1) {

		static struct option long_options[] = {
			{"help", no_argument, 0, 'h'},
			{"input", no_argument, 0, 'i'},
			{"quiet", no_argument, 0, 'q'},
			{"debug", no_argument, 0, 'd'},
			{0, 0, 0, 0}
		};

		int option_index = 0;
		int c = getopt_long(argc, argv, "hiq", long_options, &option_index);

		if (c == -1) {
			break;
		}

		switch (c) {
			case 'h':
				puts(helpstring);
				return 0;
			case 'i':
				input = 1;
				break;
			case 'q':
				quiet = 1;
				break;
			case 'd':
				debug = 1;
				break;
			case '?':
				return 1;
			default:
				printf("No argument\n");
				return 0;
		}
	}

	if (debug) {
		char newBoard[9][9] = {{0,0,2,1,0,5,0,6,0}, {9,0,5,4,0,0,3,0,0}, {0,0,1,0,2,9,0,0,0}, {0,0,4,0,0,0,0,1,0}, {8,0,0,9,0,2,0,0,6}, {0,0,0,0,0,0,2,0,0}, {0,0,0,0,5,0,0,0,0}, {0,0,7,0,0,6,1,0,2}, {0,1,0,3,0,4,8,0,0}};
		//char newBoard[9][9] = {{9, 6, 4, 1, 2, 7, 3, 8, 5}, {7, 3, 5, 6, 9, 8, 4, 1, 2}, {8, 1, 2, 3, 4, 5, 9, 7, 6}, {6, 2, 9, 7, 8, 1, 5, 3, 4}, {4, 8, 1, 5, 3, 2, 7, 6, 9}, {3, 5, 7, 4, 6, 9, 1, 2, 8}, {5, 9, 3, 8, 7, 6, 2, 4, 1}, {2, 4, 6, 9, 1, 3, 8, 5, 7}, {1, 7, 8, 2, 5, 4, 6, 9, 3}};

		// put the board into the heap so it can be passed as a parameter
		char **board = createBoard();
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				board[i][j] = newBoard[i][j];
			}
		}
		// show the original board, then solve it
		printf("Initial board\n");
		printBoard(board);

		if (solve(board)) {
			printf("\nSolved board\n");
			printBoard(board);
		}
		else {
			printf("The board is not solvable\n");
		}
		deleteBoard(board);
	}
	else if (input) {
		char **board = readBoard(quiet);
		if (quiet == 0) {
			printf("Entered board\n");
			printBoard(board);
			putchar('\n');
		}

		if (isValid(board) && solve(board)) {
			printf("Solved board\n");
			printBoard(board);
		}
		else {
			fprintf(stderr, "The board is not solvable\n");
		}
	}

	return 0;
}
