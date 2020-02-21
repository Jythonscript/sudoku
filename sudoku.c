#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

#define COLUMNS 9
#define ROWS 9

#define COLOR "\033[0;31m"
#define NOCOLOR "\033[0m"

void fillZeroes(int* list, int length);

// print board
void printBoard(char **board, int zeroes) {

	for (int k = 0; k < COLUMNS * 2 + 7; k++) {
		if ((k != 0 && k == (COLUMNS / 3) * 2 + 2) || (k == (COLUMNS / 3) * 4 + 4)) {
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
				if ((k != 0 && k == (COLUMNS / 3) * 2 + 1) || (k == (COLUMNS / 3) * 4 + 3)) {
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

			if (!zeroes && board[i][j] == 0) {
				putchar(' ');
			}
			else {
				printf("%d", board[i][j]);
			}

			if (j != COLUMNS - 1) {
				putchar(' ');
			}
		}
		fputs(" │", stdout);
		putchar('\n');
	}
	for (int k = 0; k < COLUMNS * 2 + 7; k++) {
		if ((k != 0 && k == (COLUMNS / 3) * 2 + 2) || (k == (COLUMNS / 3) * 4 + 4)) {
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
void printBoardDiff(char **firstBoard, char **solvedBoard, int zeroes) {

	for (int k = 0; k < COLUMNS * 2 + 7; k++) {
		if ((k != 0 && k == (COLUMNS / 3) * 2 + 2) || (k == (COLUMNS / 3) * 4 + 4)) {
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
				if ((k != 0 && k == (COLUMNS / 3) * 2 + 1) || (k == (COLUMNS / 3) * 4 + 3)) {
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
			if (firstBoard[i][j] == 0 && solvedBoard[i][j] != 0) {
				fputs(COLOR, stdout);
			}

			if (!zeroes && solvedBoard[i][j] == 0) {
				putchar(' ');
			}
			else {
				printf("%d", solvedBoard[i][j]);
			}

			if (firstBoard[i][j] == 0 && solvedBoard[i][j] != 0) {
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
		if ((k != 0 && k == (COLUMNS / 3) * 2 + 2) || (k == (COLUMNS / 3) * 4 + 4)) {
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
	
	char *values = (char *) calloc(9*9, sizeof(char));
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

// return a pointer to a new nums 2d array
nums_t **createNums() {
	
	nums_t *values = (nums_t *) malloc(sizeof(nums_t) * COLUMNS * ROWS);
	nums_t **nums = (nums_t **) malloc(sizeof(nums_t *) * COLUMNS);

	for (int i = 0; i < ROWS; i++) {
		nums[i] = (values + (i * 9));
	}

	// fill with 1s
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLUMNS; col++) {
			for (int i = 0; i < 9; i++) {
				nums[row][col].n[i] = 1;
			}
		}
	}

	return nums;
}

//free the memory allocated by the given nums 2d array
void deleteNums(nums_t **nums) {
	
	free(*nums);
	free(nums);
}

// return a pointer to a new hint with initialized values
hint_t *createHint() {

	hint_t *hint = (hint_t *) malloc(sizeof(hint_t));
	hint->row = -1;
	hint->column = -1;
	hint->value = -1;
	return hint;
}

// free the memory allocated by the given hint
void deleteHint(hint_t *hint) {

	free(hint);
}

// print each value in nums
void printNums(nums_t **nums) {
	
	for (int row = 0; row < ROWS; row++) {
		for (int i = 0; i < 3; i++) {
			for (int col = 0; col < COLUMNS; col++) {
				for (int j = 0; j < 3; j++) {
					printf("%d", nums[row][col].n[(i * 3) + j]);
				}
				putchar(' ');
			}
			putchar('\n');
		}
		putchar('\n');
	}
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
}

// wrapper for pointStackSolve that sets up the stack and pointer
// return 1 if the board is solved
// return 0 if the board is not solvable
int solve(char **board) {

	// simplify the board and set up nums
	nums_t **nums = simplify(board);

	// get the number of zeroes
	int *zeroes = (int *) malloc(sizeof(int));
	(*zeroes) = numZeroes(board);
	
	// set up the stack
	point_t *stack = (point_t *) malloc(sizeof(point_t) * (*zeroes));
	point_t *ptr = stack;
	char *solved = (char *) malloc(sizeof(char));
	*solved = 0;

	// solve the board
	pointStackSolve(board, nums, stack, ptr, solved, zeroes);

	// free memory
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
char **pointStackSolve(char **board, nums_t **nums, point_t *stack, point_t *ptr, char *solved, int *zeroes) {

	// if the board is good, return it
	if (*solved) {
		return board;
	}

	int numChanges = 0;
	
	// try each branch
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLUMNS; col++) {
			// find zeroes
			if (board[row][col] == 0) {
				// save each change on the stack
				numChanges++;
				point_t *myPoint = (point_t *) malloc(sizeof(point_t));
				myPoint->row = row;
				myPoint->column = col;
				pushPoint(myPoint, &ptr);
				(*zeroes)--;
				free(myPoint);

				// replace zeroes with each number, if they are a possiblility
				for (int k = 1; k <= COLUMNS; k++) {

					board[row][col] = k;

					// do not try values that are not possibilities
					if (nums[row][col].n[k - 1] == 1 && pointIsValid(board, row, col)) {
						// keep going since the branch is good
						pointStackSolve(board, nums, stack, ptr, solved, zeroes);

						// if the board is good, return it
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

// set each number in row to the given value, skipping the given column
void setRow(nums_t **nums, int row, int number, char value) {
	
	for (int col = 0; col < COLUMNS; col++) {
		nums[row][col].n[number - 1] = value;
	}
}

// set each number in column to the given value, skipping the given row
void setColumn(nums_t **nums, int col, int number, char value) {
	
	for (int row = 0; row < ROWS; row++) {
		nums[row][col].n[number - 1] = value;
	}
}

// set each number in the given 3 by 3 square to the given value
// row and col correspond to a point in the 3 by 3 square to change
void setSquare(nums_t **nums, int row, int col, int number, char value) {
	
	int startRow = row - (row % 3);
	int startCol = col - (col % 3);
	for (int row = startRow; row < startRow + 3; row++) {
		for (int col = startCol; col < startCol + 3; col++) {
			nums[row][col].n[number - 1] = value;
		}
	}
}

// set all values other than the given value to "set" in the given row and column
void setOtherNums(nums_t **nums, int row, int col, char value, char set) {
	
	for (int i = 0; i < 9; i++) {
		if (i != (value - 1)) {
			nums[row][col].n[i] = set;
		}
	}
}

// return the value of the only possiblility at the row and column, if possible
// return -1 if not possible
int getSingleOption(nums_t **nums, int row, int col) {

	if (row >= 9 || col >= 9) {
		fputs("Out of bounds index in getSingleOption\n", stderr);
		return -1;
	}
	
	char index = -1;
	char foundNonzero = 0;
	for (int i = 0; i < 9; i++) {
		if (nums[row][col].n[i] != 0) {
			if (foundNonzero == 1) {
				return -1;
			}
			index = i;
			foundNonzero = 1;
		}
	}
	return index + 1;
}

// simplify the board by cancelling out possible values, and return a 2d array of possible values for each position
// nums must be freed later
nums_t** simplify(char **board) {

	nums_t **nums = createNums();

	// boolean for checking when to stop
	char foundSimplify = 1;

	while (foundSimplify) {

		foundSimplify = 0;
		// update nums
		for (int row = 0; row < ROWS; row++) {
			for (int col = 0; col < COLUMNS; col++) {
				if (board[row][col] != 0) {

					setSquare(nums, row, col, board[row][col], 0);
					setRow(nums, row, board[row][col], 0);
					setColumn(nums, col, board[row][col], 0);
					nums[row][col].n[board[row][col] - 1] = 1;
					setOtherNums(nums, row, col, board[row][col], 0);
				}
			}
		}

		// fill out nums that were solved definitely
		for (int row = 0; row < ROWS; row++) {
			for (int col = 0; col < COLUMNS; col++) {
				if (board[row][col] == 0) {

					// simplify board if an option has been found
					int option;
					if ((option = getSingleOption(nums, row, col)) != -1) {
						board[row][col] = option;
						foundSimplify = 1;
					}
				}
			}
		}
	}

	return nums;
}

// return a hint from the board, return null if none found
hint_t* getHint(char **board) {

	nums_t **nums = createNums();
	hint_t *hint = createHint();

	// boolean for checking when to stop
	char foundSimplify = 1;

	while (foundSimplify) {

		foundSimplify = 0;
		// update nums
		for (int row = 0; row < ROWS; row++) {
			for (int col = 0; col < COLUMNS; col++) {
				if (board[row][col] != 0) {

					setSquare(nums, row, col, board[row][col], 0);
					setRow(nums, row, board[row][col], 0);
					setColumn(nums, col, board[row][col], 0);
					nums[row][col].n[board[row][col] - 1] = 1;
					setOtherNums(nums, row, col, board[row][col], 0);
				}
			}
		}

		// fill out nums that were solved definitely
		for (int row = 0; row < ROWS; row++) {
			for (int col = 0; col < COLUMNS; col++) {
				if (board[row][col] == 0) {

					// simplify board if an option has been found
					int option;
					if ((option = getSingleOption(nums, row, col)) != -1) {
						// modify the board
						board[row][col] = option;

						// return the hint
						hint->row = row;
						hint->column = col;
						hint->value = option;

						deleteNums(nums);
						return hint;
					}
				}
			}
		}
	}

	deleteNums(nums);

	return hint;
}
