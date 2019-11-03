#ifndef SUDOKU_H
#define SUDOKU_H

void printBoard();
void setBoard(int newBoard[9][9]);
void setValue(int row, int col, int value);
int isValid();

#endif //end SUDOKU_H header guard
