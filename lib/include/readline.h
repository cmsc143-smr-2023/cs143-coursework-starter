#ifndef READLINE_H_
#define READLINE_H_

#include <stdio.h>

/*
 * Read a single line from file.
 *
 * This function reads each character until either a newline character '\n'
 * or EOF, and returns a heap-allocated string.
 */
int readline(FILE *file, char **line);

#endif
