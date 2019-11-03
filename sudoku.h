#ifndef SUDOKU_H
#define SUDOKU_H

void printBoard();
void setBoard(int newBoard[9][9]);
void setValue(int row, int col, int value);
int isValid();
int pointIsValid(int row, int column);
int **solve();

#endif //end SUDOKU_H header guard
