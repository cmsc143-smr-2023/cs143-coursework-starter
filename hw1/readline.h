#ifndef READLINE_H_
#define READLINE_H_

#include <stdio.h>

/*
 * Read a single line from file.
 *
 * This function reads each character until either a newline character '\n'
 * or EOF, assigns a heap-allocated string to *line_p, and return the length of
 * the string.
 *
 * Raise an exception if file or line_p is NULL.
 */
int readline(FILE *file, char **line_p);

#endif
