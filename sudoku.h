#ifndef SUDOKU_H
#define SUDOKU_H

typedef struct point {
	char row;
	char column;
} point_t;

typedef struct numbers {
	char n[9];
} nums_t;

typedef struct hint {
	char row;
	char column;
	char value;
} hint_t;

void printBoard(char **board, int zeroes);
void printBoardDiff(char **firstBoard, char **solvedBoard, int zeroes);
void setValue(char **board, int row, int col, int value);
int isValid(char **board);
int numZeroes(char **board);
int pointIsValid(char **board, int row, int column, char value);
void fillZeroes(int* list, int length);
void boardcpy(char **arr1, char **arr2, int n);
char **createBoard();
void deleteBoard(char **board);
nums_t **createNums();
void deleteNums(nums_t **nums);
hint_t *createHint();
void deleteHint(hint_t *hint);
void printNums(nums_t **nums);
void revertBoard(char **board, point_t *stack, point_t **ptr);
void pushPoint(point_t *point, point_t **ptr);
int solve(char **board);
void printStackInfo(point_t *stack, int length);
char **pointStackSolve(char **board, nums_t **nums, point_t *stack, point_t *ptr, char *solved, int *zeroes);
int backtraceSolve(char **board, nums_t **nums, int row, int col);
void setRow(nums_t **nums, int row, int number, char value);
void setColumn(nums_t **nums, int col, int number, char value);
void setSquare(nums_t **nums, int row, int col, int number, char value);
void setOtherNums(nums_t **nums, int row, int col, char value, char set);
int getSingleOption(nums_t **nums, int row, int col);
nums_t** simplify(char **board);
hint_t* getHint(char **board);

#endif //end SUDOKU_H header guard
