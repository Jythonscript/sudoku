#ifndef SUDOKU_H
#define SUDOKU_H

void printBoard(int **myBoard);
void setValue(int **board, int row, int col, int value);
int isValid(int **board);
int pointIsValid(int **board, int row, int column);
void fillZeroes(int* list, int length);
int **solve();
int **solveBoard(int **myBoard);

#endif //end SUDOKU_H header guard
