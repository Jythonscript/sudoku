# Sudoku Solver
This C program solves sudoku puzzles. 

## Dependencies
* getopts
* readline
* GTK3

## How it works
This program uses a two-dimensional char array to represent the board, and uses a two-dimensional array of nine-char structs to represent the possible values that could be valid in each position.

First, the program runs through the board and eliminates possibilities for what numbers can go in each spot based on what numbers are already on the board. It does this over and over again until an iteration gains no new information.

The next phase of the solving algorithm uses a variant of brute-force to look through the remaining possible boards. There is only one board in memory at a time, so a preallocated stack is used to revert modifications to the board when a branch is found to be invalid.

## Future plans
Future plans include to improve the solving algorithm, allowing for multiple threads to be used when solving, and improving on the hint system.
