#ifndef SUDOKU_H
#define SUDOKU_H

typedef  struct point {
	char row;
	char column;
} point_t;

void printBoard(char **myBoard);
void setValue(char **board, int row, int col, int value);
int isValid(char **board);
int numZeroes(char **board);
int pointIsValid(char **board, int row, int column);
void fillZeroes(int* list, int length);
void boardcpy(char **arr1, char **arr2, int n);
char **solve(char **board);
char **createBoard();
void deleteBoard(char **board);
void revertBoard(char **board, point_t *stack, point_t *ptr);
char **stackSolve(char **board, point_t *stack);

#endif //end SUDOKU_H header guard
