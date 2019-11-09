#ifndef SUDOKU_H
#define SUDOKU_H

void printBoard(char **myBoard);
void setValue(char **board, int row, int col, int value);
int isValid(char **board);
int numZeroes(char **board);
int pointIsValid(char **board, int row, int column);
void fillZeroes(int* list, int length);
void boardcpy(char **arr1, int **arr2, int n);
char **solve(char **board);
char **createBoard();
void deleteBoard(char **board);

#endif //end SUDOKU_H header guard
