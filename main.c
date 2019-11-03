#include <stdio.h>
#include "sudoku.h"

int main(int argc, char **argv) {

	//int newBoard[9][9] = {{1, 0, 1, 0, 1, 0, 1, 0, 1}, {2, 0, 2, 0, 2, 0, 2, 0, 2}, {3, 0, 3, 0, 3, 0, 3, 0, 3}, {4, 0, 4, 0, 4, 0, 4, 0, 4}, {5, 0, 5, 0, 5, 0, 5, 0, 5}, {6, 0, 6, 0, 6, 0, 6, 0, 6}, {7, 0, 7, 0, 7, 0, 7, 0, 7}, {8, 0, 8, 0, 8, 0, 8, 0, 8}, {9, 0, 9, 0, 9, 0, 9, 0, 9}};
	int newBoard[9][9] = {{1, 2, 3, 4, 5, 6, 7, 8, 9}, {9, 8, 7, 6, 5, 4, 3, 2, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}};
	//int newBoard[9][9] = {{0, 0, 4, 0, 2, 0, 3, 0, 0}, {7, 0, 0, 0, 0, 0, 0, 0, 2}, {0, 1, 0, 3, 0, 0, 9, 0, 0}, {0, 0, 0, 7, 8, 0, 0, 0, 0}, {0, 8, 1, 0, 0, 0, 0, 6, 0}, {0, 0, 0, 0, 6, 9, 0, 0, 0}, {0, 9, 3, 0, 0, 6, 0, 4, 0}, {2, 0, 0, 0, 0, 0, 0, 5, 7}, {0, 0, 8, 0, 5, 0, 0, 0, 0}};
	//int newBoard[9][9] = {{0, 9, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 9, 0, 0, 4, 8, 3}, {0, 1, 0, 4, 0, 6, 0, 0, 5}, {6, 4, 0, 0, 3, 0, 0, 0, 0}, {0, 3, 5, 0, 0, 0, 8, 4, 0}, {0, 0, 0, 0, 6, 0, 0, 5, 9}, {9, 0, 0, 2, 0, 5, 0, 7, 0}, {5, 7, 4, 0, 0, 3, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 3, 0}};

	//int newBoard[9][9] = {{0, 9, 1, 0, 0, 0, 3, 4, 0}, {0, 0, 6, 8, 0, 2, 0, 0, 0}, {0, 4, 0, 0, 0, 0, 8, 6, 7}, {9, 0, 0, 1, 0, 0, 6, 0, 0}, {0, 3, 0, 0, 6, 0, 0, 1, 0}, {0, 0, 8, 0, 0, 4, 0, 0, 5}, {4, 2, 9, 0, 0, 0, 0, 3, 0}, {0, 0, 0, 6, 0, 3, 2, 0, 0}, {0, 6, 3, 0, 0, 0, 1, 8, 0}};

	setBoard(newBoard);

	//solve();

	//printf("%d\n", pointIsValid(0, 4));

	printBoard();
	return 0;
}
