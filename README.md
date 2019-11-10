# Sudoku Solver
This C program solves sudoku puzzles. 

## How it works
This program uses a two-dimensional char array to represent the board and uses recursion to iterate through the board that are possibly valid. There is only one board in memory at a time, so a preallocated stack is used to revert modifications to the board when a branch is found to be invalid.

## Future plans
The algorithm is complete, but there is currently no user interface to the program and boards have to be compiled into the program. Possible input methods could be using readline to get user input, command-line arguments, input from a file, or a GUI using SDL.
