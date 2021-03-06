# Sudoku Solver
This C program solves sudoku puzzles. 

`./sudoku -h` after building for a list and description of all command-line arguments

## Dependencies
* getopts
* make
* gcc
* pkg-config
* GTK3 (optional)
* readline (optional)

## Make commands
`make`: standard compilation

`make debug`: compile with debugging information

`make clean`: remove build files

To enable or disable the optional dependencies, change the Makefile variables `USE_GTK`, `USE_READLINE` to 1 (enabled) or 0 (disabled) before compiling. You may need to run `make clean` if you have already compiled for this to take effect.

## How it works
This program uses a two-dimensional char array to represent the board, and uses a two-dimensional array of nine-char structs to represent the possible values that could be valid in each position.

First, the program runs through the board and eliminates possibilities for what numbers can go in each spot based on what numbers are already on the board. It does this over and over again until an iteration gains no new information.

The next phase of the solving algorithm uses backtracing to look through the remaining possible boards. It uses an efficient method where it only checks the necessary parts of the board when a change is made to see if the board is valid, so it never needs to scan the entire board to check for inconsistencies.

## Future plans
* Improving the hint system
* Adding a file selector to the GUI
