#ifndef SUDOKU_H
#define SUDOKU_H

void printBoard(int **myBoard);
void setValue(int **board, int row, int col, int value);
int isValid(int **board);
int numZeroes(int **board);
int pointIsValid(int *board[9][9], int row, int column);
void fillZeroes(int* list, int length);
void boardcpy(int **arr1, int **arr2, int n);
int **solve(int **board);
int **createBoard();
void deleteBoard(int **board);

#endif //end SUDOKU_H header guard
