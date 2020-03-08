# Sudoku Solver
This C program solves sudoku puzzles. 

## Dependencies
* getopts
* readline
* GTK3

## Make commands
`make`: standard compilation

`make debug`: compile with debugging information

`make clean`: remove

## How it works
This program uses a two-dimensional char array to represent the board, and uses a two-dimensional array of nine-char structs to represent the possible values that could be valid in each position.

First, the program runs through the board and eliminates possibilities for what numbers can go in each spot based on what numbers are already on the board. It does this over and over again until an iteration gains no new information.

The next phase of the solving algorithm uses backtracing to look through the remaining possible boards. It uses an efficient method where it only checks the necessary parts of the board when a change is made to see if the board is valid, so it never needs to scan the entire board to check for inconsistencies.

## Future plans
Future plans include to improve the solving algorithm, allowing for multiple threads to be used when solving, and improving on the hint system which is very limited right now.
