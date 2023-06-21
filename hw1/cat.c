/*
 * Concatenating all files given on the command line to standard output.
 * Author: Byron Zhong (byronzhong@uchicago.edu)
 *
 * Usage: ./cat [file1] [file2] ...
 * Description: this program concatenates all files on the command line in the
 * order in which they are passed, and output the result to standard output.
 * If no files are specified, the program reads from the standard input.
 *
 * Note: this file uses the readline function in readline.c, but it is
 * otherwise complete.
 */

#include <stdio.h>
#include <stdlib.h>

#include "readline.h"

/*
 * print all lines from fp to standard out. fp cannot NULL.
 */
void print_all_lines(FILE *fp);

/*
 * main takes two arguments in this case. argc is the argument count and argv is
 * an *array* of strings that are the arguments passed in the command line. The
 * array, argv, has argc number of arguments, and the first element in argv,
 * argv[0], is the name of the executable.
 *
 * For example, when running the following command,
 *   `./cat one two three`
 * main will be called with
 *    argc = 4
 *    argv[0] = "./cat"
 *    argv[1] = "one"
 *    argv[2] = "two"
 *    argv[3] = "three"
 */
int main(int argc, char *argv[])
{
        if (argc == 1) {
                /* When argc == 1, the program is run with only the program
                 * name. In this case, we use print all lines from stdin.
                 */
                print_all_lines(stdin);
                return EXIT_SUCCESS;
        }

        for (int i = 1; i < argc; i++) {
                FILE *fp = fopen(argv[i], "rb"); // open file for (r)eading
                if (fp == NULL) {
                        fprintf(stderr, "No such file '%s'\n", argv[i]);
                        return EXIT_FAILURE;
                }
                print_all_lines(fp);
                fclose(fp); // files need to be closed
        }

        return EXIT_SUCCESS;
}

/*
 * call readline repeatedly until there is nothing more to read
 */
void print_all_lines(FILE *fp)
{
        char *line;
        int len;

        while ((len = readline(fp, &line)) != 0) {
                // printing character by character because there might be '\0'
                // in the middle of a line
                for (int i = 0; i < len; i++) {
                        putchar(line[i]);
                }
                free(line); // releasing the memory held by line
        }
}


