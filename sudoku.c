#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

#define COLUMNS 9
#define ROWS 9

#define COLOR "\033[0;31m"
#define NOCOLOR "\033[0m"

void fillZeroes(int* list, int length);

// print board
void printBoard(char **board) {

	for (int k = 0; k < COLUMNS * 2 + 7; k++) {
		if (k != 0 && k == (COLUMNS / 3) * 2 + 2 || k == (COLUMNS / 3) * 4 + 4) {
			fputs("┬", stdout);
		}
		else if (k == 0) {
			fputs("┌", stdout);
		}
		else if (k == COLUMNS * 2 + 6) {
			fputs("┐", stdout);
		}
		else {
			fputs("─", stdout);
		}
	}
	putchar('\n');
	for (int i = 0; i < ROWS; i++) {
		// print horizontal board lines
		if (i != 0 && i % 3 == 0) {
			fputs("├", stdout);
			for (int k = 0; k < COLUMNS * 2 + 5; k++) {
				if (k != 0 && k == (COLUMNS / 3) * 2 + 1 || k == (COLUMNS / 3) * 4 + 3) {
					fputs("┼", stdout);
				}
				else {
					fputs("─", stdout);
				}
			}
			fputs("┤", stdout);
			putchar('\n');
		}
		fputs("│ ", stdout);
		for (int j = 0; j < COLUMNS; j++) {
			// print vertical board lines
			if (j != 0 && j % 3 == 0) {
				fputs("│ ", stdout);
			}
			printf("%d", board[i][j]);
			if (j != COLUMNS - 1) {
				putchar(' ');
			}
		}
		fputs(" │", stdout);
		putchar('\n');
	}
	for (int k = 0; k < COLUMNS * 2 + 7; k++) {
		if (k != 0 && k == (COLUMNS / 3) * 2 + 2 || k == (COLUMNS / 3) * 4 + 4) {
			fputs("┴", stdout);
		}
		else if (k == 0) {
			fputs("└", stdout);
		}
		else if (k == COLUMNS * 2 + 6) {
			fputs("┘", stdout);
		}
		else {
			fputs("─", stdout);
		}
	}
	putchar('\n');
}

// print solvedBoard with colored numbers that were originally blank
void printBoardDiff(char **firstBoard, char **solvedBoard) {

	for (int k = 0; k < COLUMNS * 2 + 7; k++) {
		if (k != 0 && k == (COLUMNS / 3) * 2 + 2 || k == (COLUMNS / 3) * 4 + 4) {
			fputs("┬", stdout);
		}
		else if (k == 0) {
			fputs("┌", stdout);
		}
		else if (k == COLUMNS * 2 + 6) {
			fputs("┐", stdout);
		}
		else {
			fputs("─", stdout);
		}
	}
	putchar('\n');
	for (int i = 0; i < ROWS; i++) {
		// print horizontal board lines
		if (i != 0 && i % 3 == 0) {
			fputs("├", stdout);
			for (int k = 0; k < COLUMNS * 2 + 5; k++) {
				if (k != 0 && k == (COLUMNS / 3) * 2 + 1 || k == (COLUMNS / 3) * 4 + 3) {
					fputs("┼", stdout);
				}
				else {
					fputs("─", stdout);
				}
			}
			fputs("┤", stdout);
			putchar('\n');
		}
		fputs("│ ", stdout);
		for (int j = 0; j < COLUMNS; j++) {
			// print vertical board lines
			if (j != 0 && j % 3 == 0) {
				fputs("│ ", stdout);
			}
			// print current number
			if (firstBoard[i][j] == 0) {
				fputs(COLOR, stdout);
			}
			printf("%d", solvedBoard[i][j]);
			if (firstBoard[i][j] == 0) {
				fputs(NOCOLOR, stdout);
			}
			if (j != COLUMNS - 1) {
				putchar(' ');
			}
		}
		fputs(" │", stdout);
		putchar('\n');
	}
	for (int k = 0; k < COLUMNS * 2 + 7; k++) {
		if (k != 0 && k == (COLUMNS / 3) * 2 + 2 || k == (COLUMNS / 3) * 4 + 4) {
			fputs("┴", stdout);
		}
		else if (k == 0) {
			fputs("└", stdout);
		}
		else if (k == COLUMNS * 2 + 6) {
			fputs("┘", stdout);
		}
		else {
			fputs("─", stdout);
		}
	}
	putchar('\n');
}

// set board[x][y] to value, if it is not out-of-bounds
void setValue(char **board, int row, int col, int value) {

	if (row >= 0 && col >= 0 && row < ROWS && col < COLUMNS) {
		board[row][col] = value;
	}
	else {
		fprintf(stderr, "Invalid attempt to modify row %d column %d\n", row, col);
	}
}

// check if the current state of the board is valid by the rules of Sudoku
// return 1 if valid and 0 if invalid
int isValid(char **board) {
	
	//check all rows for unique values
	for (int i = 0; i < ROWS; i++) {

		int valueCounts[COLUMNS];
		fillZeroes(valueCounts, COLUMNS);
		for (int j = 0; j < COLUMNS; j++) {

			int currentValue = board[i][j];
			if (currentValue > 0 && currentValue <= COLUMNS) {
				valueCounts[currentValue - 1]++;
				if (valueCounts[currentValue - 1] > 1) {
					//printf("Did not pass row test for i=%d j=%d currentvalue=%d\n", i, j, currentValue);
					return 0;
				}
			}
		} // end for
	} //end for

	//check all columns for unique values
	for (int j = 0; j < COLUMNS; j++) {

		int valueCounts[ROWS];
		fillZeroes(valueCounts, ROWS);
		for (int i = 0; i < ROWS; i++) {

			int currentValue = board[i][j];
			if (currentValue > 0 && currentValue <= ROWS) {
				valueCounts[currentValue - 1]++;
				if (valueCounts[currentValue - 1] > 1) {
					//printf("Did not pass column test for i=%d j=%d currentvalue=%d\n", i, j, currentValue);
					return 0;
				}
			}
		} // end for
	} //end for

	// divide the board into 9 squares and check each for unique values
	for (int startRow = 0; startRow < ROWS; startRow += (ROWS / 3)) {
		for (int startCol = 0; startCol < COLUMNS; startCol += (COLUMNS / 3)){

			int valueCounts[(ROWS / 3) * (COLUMNS / 3)];
			fillZeroes(valueCounts, (ROWS / 3) * (COLUMNS / 3));
			for (int i = startRow; i < startRow + (ROWS / 3); i++) {
				for (int j = startCol; j < startCol + (COLUMNS / 3); j++) {

					int currentValue = board[i][j];
					if (currentValue > 0 && currentValue <= ROWS) {
						valueCounts[currentValue - 1]++;
						if (valueCounts[currentValue - 1] > 1) {
							//printf("Did not pass square test for i=%d j=%d currentvalue=%d\n", i, j, currentValue);
							return 0;
						}
					}
				} // end for
			} // end for
		} // end for
	} // end for

	return 1;
}

// return the number of tiles with a zero in them (blank spaces)
int numZeroes(char **board) {
	
	int count = 0;
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (board[i][j] == 0) {
				count++;
			}

		}
	}
	return count;
}

// check if the current board is valid by looking at only the given row and column
// this is faster that isValid if only one tile has been changed
// return 1 if valid and 0 if invalid
int pointIsValid(char **board, int row, int column) {
	
	//check the given row for unique values
	int valueCounts[COLUMNS];
	fillZeroes(valueCounts, COLUMNS);
	for (int j = 0; j < COLUMNS; j++) {

		int currentValue = board[row][j];
		if (currentValue > 0 && currentValue <= COLUMNS) {
			valueCounts[currentValue - 1]++;
			if (valueCounts[currentValue - 1] > 1) {
				//printf("Did not pass row test for row=%d j=%d currentvalue=%d\n", row, j, currentValue);
				return 0;
			}
		}
	} // end for

	//check the given column for unique values
	fillZeroes(valueCounts, COLUMNS);
	for (int i = 0; i < ROWS; i++) {

		int currentValue = board[i][column];
		if (currentValue > 0 && currentValue <= ROWS) {
			valueCounts[currentValue - 1]++;
			if (valueCounts[currentValue - 1] > 1) {
				//printf("Did not pass column test for i=%d column=%d currentvalue=%d\n", i, column, currentValue);
				return 0;
			}
		}
	} // end for


	// check the current square for unique values
	int startRow = row - (row % (ROWS / 3));
	int startCol = column - (column % (COLUMNS / 3));
	fillZeroes(valueCounts, COLUMNS);
	for (int i = startRow; i < startRow + (ROWS / 3); i++) {
		for (int j = startCol; j < startCol + (COLUMNS / 3); j++) {

			int currentValue = board[i][j];
			if (currentValue > 0 && currentValue <= ROWS) {
				valueCounts[currentValue - 1]++;
				if (valueCounts[currentValue - 1] > 1) {
					//printf("Did not pass square test for i=%d j=%d currentvalue=%d\n", i, j, currentValue);
					return 0;
				}
			}
		} // end for
	} // end for

	return 1;
}

// fill the argument list with zeroes
void fillZeroes(int* list, int length) {

	for (int i = 0; i < length; i++) {
		list[i] = 0;
	}
}

// copy the contents of n by n 2d array arr1 into arr2
void boardcpy(char **arr1, char **arr2, int n) {
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			arr2[i][j] = arr1[i][j];
		}
	}
}

// return a pointer to a new board
char **createBoard() {
	
	char *values = (char *) malloc(sizeof(char) * 9 * 9);
	char **board = (char **) malloc(sizeof(char *) * 9);

	// set up the board array with pointers to values
	for (int i = 0; i < 9; i++) {
		board[i] = values + (i * 9);
	}
	return board;
}

// free the memory allocated by the given board
void deleteBoard(char **board) {

	free(*board);
	free(board);
}

// revert the board by the latest point on the stack
void revertBoard(char **board, point_t *stack, point_t **ptr) {

	(*ptr)--;
	board[(int)(*ptr)->row][(int)(*ptr)->column] = 0;
}

// push a point onto the stack
void pushPoint(point_t *point, point_t **ptr) {

	(*ptr)->row = point->row;
	(*ptr)->column = point->column;
	(*ptr)++;
	//ptr++;
}

// wrapper for pointStackSolve that sets up the stack and pointer
// return 1 if the board is solved
// return 0 if the board is not solvable
int solve(char **board) {

	int *zeroes = (int *) malloc(sizeof(int));
	(*zeroes) = numZeroes(board);
	
	point_t *stack = (point_t *) malloc(sizeof(point_t) * (*zeroes));
	point_t *ptr = stack;
	char *solved = (char *) malloc(sizeof(char));
	*solved = 0;

	// solve the board
	pointStackSolve(board, stack, ptr, solved, zeroes);

	//free memory
	free(stack);
	free(solved);
	return isValid(board);
}

// print stack info for debugging
void printStackInfo(point_t *stack, int length) {

	for (int i = 0; i < length; i++) {
		printf("row: %d\tcolumn: %d\n", (stack + i)->row, (stack + i)->column);
	}
}

// return a solved board, using a stack of points to track the changes
char **pointStackSolve(char **board, point_t *stack, point_t *ptr, char *solved, int *zeroes) {

	// if the board is good, return it
	if (*solved) {
		return board;
	}

	int numChanges = 0;
	
	// try each branch
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			// find zeroes
			if (board[i][j] == 0) {
				// save each change on the stack
				numChanges++;
				point_t *myPoint = (point_t *) malloc(sizeof(point_t));
				myPoint->row = i;
				myPoint->column = j;
				pushPoint(myPoint, &ptr);
				(*zeroes)--;
				free(myPoint);

				// replace zeroes with each number
				for (int k = 1; k <= COLUMNS; k++) {
					board[i][j] = k;
					if (pointIsValid(board, i, j)) {
						// keep going since the branch is good
						pointStackSolve(board, stack, ptr, solved, zeroes);

						//if the board is good, return it
						if ((*zeroes) == 0 && isValid(board)) {
							*solved = 1;
							return board;
						}
					}
				}
			}
		}
	}

	// revert the changes made by this iteration because it did not find the solved board
	for (int i = 0; i < numChanges; i++) {
		revertBoard(board, stack, &ptr);
		(*zeroes)++;
	}

	return board;
}
