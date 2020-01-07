#ifndef SUDOKU_H
#define SUDOKU_H

typedef struct point {
	char row;
	char column;
} point_t;

typedef struct numbers {
	char nums[9];
} nums_t;

void printBoard(char **board, int zeroes);
void printBoardDiff(char **firstBoard, char **solvedBoard);
void setValue(char **board, int row, int col, int value);
int isValid(char **board);
int numZeroes(char **board);
int pointIsValid(char **board, int row, int column);
void fillZeroes(int* list, int length);
void boardcpy(char **arr1, char **arr2, int n);
char **createBoard();
void deleteBoard(char **board);
void revertBoard(char **board, point_t *stack, point_t **ptr);
void pushPoint(point_t *point, point_t **ptr);
int solve(char **board);
void printStackInfo(point_t *stack, int length);
char **pointStackSolve(char **board, point_t *stack, point_t *ptr, char *solved, int *zeroes);

#endif //end SUDOKU_H header guard
