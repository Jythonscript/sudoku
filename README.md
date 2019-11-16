# Sudoku Solver
This C program solves sudoku puzzles. 

## Dependencies
* getopts
* readline

## How it works
This program uses a two-dimensional char array to represent the board and uses recursion to iterate through the board that are possibly valid. There is only one board in memory at a time, so a preallocated stack is used to revert modifications to the board when a branch is found to be invalid.

## Future plans
Future plans include to allow input from a file or a GUI using SDL.
