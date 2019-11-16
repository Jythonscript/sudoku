#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>

#include "sudoku.h"

char **readBoard(const char quiet) {
	
	char **board = createBoard();

	if (quiet == 0) {
		printf("Enter a 9x9 board below\n"
				"Enter a zero or non-digit character if the tile value is not known\n");
	}

	for (int row = 0; row < 9; row++) {

		char *input = readline("");
		if (input == NULL) {
			exit(1);
		}

		int i = 0;
		int chars = 0;
		char currentChar[1] = "0";

		while (chars < 9 && input[i] != EOF && input[i] != '\0') {
			currentChar[0] = input[i];
			if (input[i] != ' ' && input[i] != '\t') {
				board[row][chars] = atoi(currentChar);
				chars++;
			}
			i++;
		}
	}
	return board;
}
