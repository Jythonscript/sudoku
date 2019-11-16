#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "sudoku.h"

int main(int argc, char **argv) {

	int c;

	// getopts
	while (1) {

		int option_index = 0;
		static struct option long_options[] = {
			{"help", no_argument, 0, 'h'},
			{0, 0, 0, 0}
		};

		c = getopt_long(argc, argv, "h", long_options, &option_index);

		if (c == -1) {
			break;
		}

		switch (c) {
			case 'h':
				printf("Usage: sudoku [OPTION]\n"
					   "  -h, --help		display this help and exit\n");
				return 0;
			case '?':
				return 1;
			default:
				printf("No argument\n");
				return 0;
		}
	}

	// boards for testing
	//char newBoard[9][9] = {{1, 0, 1, 0, 1, 0, 1, 0, 1}, {2, 0, 2, 0, 2, 0, 2, 0, 2}, {3, 0, 3, 0, 3, 0, 3, 0, 3}, {4, 0, 4, 0, 4, 0, 4, 0, 4}, {5, 0, 5, 0, 5, 0, 5, 0, 5}, {6, 0, 6, 0, 6, 0, 6, 0, 6}, {7, 0, 7, 0, 7, 0, 7, 0, 7}, {8, 0, 8, 0, 8, 0, 8, 0, 8}, {9, 0, 9, 0, 9, 0, 9, 0, 9}};
	//char newBoard[9][9] = {{1, 2, 3, 4, 5, 6, 7, 8, 9}, {9, 8, 7, 6, 5, 4, 3, 2, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}};
	//char newBoard[9][9] = {{0, 0, 4, 0, 2, 0, 3, 0, 0}, {7, 0, 0, 0, 0, 0, 0, 0, 2}, {0, 1, 0, 3, 0, 0, 9, 0, 0}, {0, 0, 0, 7, 8, 0, 0, 0, 0}, {0, 8, 1, 0, 0, 0, 0, 6, 0}, {0, 0, 0, 0, 6, 9, 0, 0, 0}, {0, 9, 3, 0, 0, 6, 0, 4, 0}, {2, 0, 0, 0, 0, 0, 0, 5, 7}, {0, 0, 8, 0, 5, 0, 0, 0, 0}};
	//char newBoard[9][9] = {{0, 9, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 9, 0, 0, 4, 8, 3}, {0, 1, 0, 4, 0, 6, 0, 0, 5}, {6, 4, 0, 0, 3, 0, 0, 0, 0}, {0, 3, 5, 0, 0, 0, 8, 4, 0}, {0, 0, 0, 0, 6, 0, 0, 5, 9}, {9, 0, 0, 2, 0, 5, 0, 7, 0}, {5, 7, 4, 0, 0, 3, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 3, 0}};
	//char newBoard[9][9] = {{0, 9, 1, 0, 0, 0, 3, 4, 0}, {0, 0, 6, 8, 0, 2, 0, 0, 0}, {0, 4, 0, 0, 0, 0, 8, 6, 7}, {9, 0, 0, 1, 0, 0, 6, 0, 0}, {0, 3, 0, 0, 6, 0, 0, 1, 0}, {0, 0, 8, 0, 0, 4, 0, 0, 5}, {4, 2, 9, 0, 0, 0, 0, 3, 0}, {0, 0, 0, 6, 0, 3, 2, 0, 0}, {0, 6, 3, 0, 0, 0, 1, 8, 0}};
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

	return 0;
}
