#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 9
#define ROWS 9

int board[9][9];

void fillZeroes(int* list, int length);

void printBoard() {
	
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			printf("%d ", board[i][j]);
		}
		putchar('\n');
	}
}

// replace the contents of the board with a new board
void setBoard(int newBoard[9][9]) {
	
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			board[i][j] = newBoard[i][j];
		}
	}
}

// set board[x][y] to value, if it is not out-of-bounds
void setValue(int row, int col, int value) {

	if (row >= 0 && col >= 0 && row < ROWS && col < COLUMNS) {
		board[row][col] = value;
	}
	else {
		fprintf(stderr, "Invalid attempt to modify row %d column %d\n", row, col);
	}
}

// check if the current state of the board is valid by the rules of Sudoku
// return 1 if valid and 0 if invalid
int isValid() {
	
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
int pointIsValid(int row, int column) {
	
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

//return a solved board
int **solve() {
	
	int **original = (int **) malloc(sizeof(int*) * ROWS);
	//int *columns = (int *) malloc(sizeof(int) * COLUMNS);
	/*

	// backup the original board
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			columns[j] = board[i][j];
		}
		original[i] = columns;
	}

	//free(original);

	//setBoard(original);
	*/
	//return board;
	return original;
}
