#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 9
#define ROWS 9

void fillZeroes(int* list, int length);

void printBoard(int **myBoard) {
	
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			printf("%d ", myBoard[i][j]);
		}
		putchar('\n');
	}
}

// set board[x][y] to value, if it is not out-of-bounds
void setValue(int **board, int row, int col, int value) {

	if (row >= 0 && col >= 0 && row < ROWS && col < COLUMNS) {
		board[row][col] = value;
	}
	else {
		fprintf(stderr, "Invalid attempt to modify row %d column %d\n", row, col);
	}
}

// check if the current state of the board is valid by the rules of Sudoku
// return 1 if valid and 0 if invalid
int isValid(int **board) {
	
	//check all rows for unique values
	for (int i = 0; i < ROWS; i++) {

		int valueCounts[COLUMNS];
		fillZeroes(valueCounts, COLUMNS);
		for (int j = 0; j < COLUMNS; j++) {

			int currentValue = board[i][j];
			if (currentValue > 0 && currentValue <= COLUMNS) {
				valueCounts[currentValue - 1]++;
				if (valueCounts[currentValue - 1] > 1) {
					printf("Did not pass row test for i=%d j=%d currentvalue=%d\n", i, j, currentValue);
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
					printf("Did not pass column test for i=%d j=%d currentvalue=%d\n", i, j, currentValue);
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
							printf("Did not pass square test for i=%d j=%d currentvalue=%d\n", i, j, currentValue);
							return 0;
						}
					}
				} // end for
			} // end for
		} // end for
	} // end for

	return 1;
}

// check if the current board is valid by looking at the given row and column
// return 1 if valid and 0 if invalid
int pointIsValid(int **board, int row, int column) {
	
	//check the given row for unique values
	int valueCounts[COLUMNS];
	fillZeroes(valueCounts, COLUMNS);
	for (int j = 0; j < COLUMNS; j++) {

		int currentValue = board[row][j];
		if (currentValue > 0 && currentValue <= COLUMNS) {
			valueCounts[currentValue - 1]++;
			if (valueCounts[currentValue - 1] > 1) {
				printf("Did not pass row test for row=%d j=%d currentvalue=%d\n", row, j, currentValue);
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
				printf("Did not pass column test for i=%d column=%d currentvalue=%d\n", i, column, currentValue);
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
					printf("Did not pass square test for i=%d j=%d currentvalue=%d\n", i, j, currentValue);
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

// return a solved board
int **solve(int **board) {
	
	//int original[ROWS][COLUMNS];

	/*
	int *values = malloc(sizeof(int) * ROWS * COLUMNS);
	int **rows = malloc(sizeof(int *) * ROWS);

	// set up the rows array
	for (int i = 0; i < ROWS; i++) {
		rows[i] = values + (i * COLUMNS);
	}
	*/
	// backup the original board
	/*
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			original[i][j] = board[i][j];
			rows[i][j] = board[i][j];
		}
	}

	setBoard(original);
	*/

	// replace the first zero with 1-9 recursively until an invalid board state is encountered



	return board;
}

int **solveBoard(int **myBoard) {

	for (int i = 0; i < ROWS; i++ ) {
		for (int j = 0; j < COLUMNS; j++) {
			if (myBoard[i][j] == 0) {
				for (int k = 1; k <= COLUMNS; k++) {
					myBoard[i][j] = k;

					if (pointIsValid(myBoard, i, j) == 0) {
						
					}
				}
			}
		}
	}
	return myBoard;
}


