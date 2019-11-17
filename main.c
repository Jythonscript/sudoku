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
					   "\nSource: <https://github.com/Jythonscript/sudoku>";

	// flags
	char input = 0;
	char quiet = 0;

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
			case '?':
				return 1;
			default:
				printf("No argument\n");
				return 0;
		}
	}

	if (input) {
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
