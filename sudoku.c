#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 9
#define ROWS 9

void fillZeroes(int* list, int length);
int **solveBoard(int **myBoard);

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

int numZeroes(int **board) {
	
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
void boardcpy(int **arr1, int **arr2, int n) {
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			arr2[i][j] = arr1[i][j];
		}
	}
}

int **createBoard() {
	
	int *values = malloc(sizeof(int) * 9 * 9);
	int **board = malloc(sizeof(int *) * 9);

	// set up the board array with pointers to values
	for (int i = 0; i < 9; i++) {
		board[i] = values + (i * 9);
	}
	return board;
}

void deleteBoard(int **board) {

	free(*board);
	free(board);
}

// return a solved board
int **solve(int **board) {
	
	// board which will be modified
	int **newBoard = createBoard();
	boardcpy(board, newBoard, COLUMNS);

	//return the board if it is completed
	if (numZeroes(newBoard) == 0 && isValid(newBoard)) {
		return newBoard;
	}

	// try each branch
	for (int i = 0; i < ROWS; i++ ) {
		for (int j = 0; j < COLUMNS; j++) {
			// find zeroes
			if (newBoard[i][j] == 0) {
				// replace zeroes with each number
				for (int k = 1; k <= COLUMNS; k++) {
					newBoard[i][j] = k;
					if (pointIsValid(newBoard, i, j)) {
						// if this branch is good, then keep going
						boardcpy(solve(newBoard), newBoard, COLUMNS);
						//if the board is complete, return it
						if (numZeroes(newBoard) == 0 && isValid(newBoard)) {
							return newBoard;
						}
					}
				}
			}
		}
	}

	return board;
}
