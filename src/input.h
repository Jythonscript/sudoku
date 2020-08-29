#ifndef INPUT_H
#define INPUT_H

#ifdef USE_READLINE
char **readBoard(const char verbose);
#endif // USE_READLINE

char **fileBoard(char *filename);

#endif //end INPUT_H header guard
