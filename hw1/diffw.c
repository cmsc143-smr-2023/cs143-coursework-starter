/*
 * Comparing two files up to whitespaces
 * Author: Byron Zhong (byronzhong@uchicago.edu)
 *
 * Usage: ./diffw [file1] [file2]
 *
 * Description: this program compares the two files given on the command line,
 * and outputs all different lines. Two lines are different if they have
 * different words, but not different if they only differ in the number of
 * spaces between words.
 *
 * If one file is longer than the other, the remaining line will *not* be
 * printed.
 *
 */
#include <stdlib.h>
#include <string.h>

#include "readline.h"
#include "substring.h"

/* open a file if the name is not "-"; otherwise, return stdin */
FILE *open_or_stdin(const char *name);

/* return non-zero values if and only if sub1 and sub2 are equal */
int substring_eq(struct substring sub1, struct substring sub2);

/* return non-zero values if and only if all substrings in subs1 are equal
 * to substrings in subs2
 */
int substrings_eq(struct substring *subs1, struct substring *subs2, int n);

/* compare two files */
void compare_files(FILE *file1, FILE *file2);

/* output two lines */
void print_diff(const char *line1, const char *line2);

/* all white space characters */
const char *WHITESPACES = " \t\r\n";

int main(int argc, char *argv[])
{
        if (argc != 3) {
                fprintf(stderr, "usage: %s [file1] [file2]\n", argv[0]);
                return EXIT_FAILURE;
        }

        if (strcmp(argv[1], "-") == 0 && strcmp(argv[2], "-") == 0) {
                // special case: if the two files are both stdin, there is
                // no different lines. Therefore, nothing is printed and
                // exit with success.
                return EXIT_SUCCESS;
        }

        FILE *file1 = open_or_stdin(argv[1]);
        FILE *file2 = open_or_stdin(argv[2]);

        compare_files(file1, file2);

        if (file1 != stdin) {
                fclose(file1);
        }

        if (file2 != stdin) {
                fclose(file2);
        }

        return EXIT_SUCCESS;
}

/********** HELPER FUNCTIONS ***********/

void compare_files(FILE *file1, FILE *file2)
{
        while (1) {
                char *line1, *line2;
                int line1_len = readline(file1, &line1);
                int line2_len = readline(file2, &line2);

                if (line1_len == 0 && line2_len == 0) {
                        break;
                } else if (line1_len == 0) {
                        free(line2);
                        break;
                } else if (line2_len == 0) {
                        free(line1);
                        break;
                }

                struct substring *subs1, *subs2;
                int subs1_len = split(line1, WHITESPACES, &subs1);
                int subs2_len = split(line2, WHITESPACES, &subs2);

                if (subs1_len != subs2_len) {
                        print_diff(line1, line2);
                } else if (!substrings_eq(subs1, subs2, subs1_len)) {
                        print_diff(line1, line2);
                }

                free(subs1);
                free(subs2);

                free(line1);
                free(line2);
        }
}

void print_diff(const char *line1, const char *line2)
{
        // static local variable are allocated only once
        static int need_space = 0;

        if (need_space) {
                putchar('\n');
                need_space = 1;
        }

        printf("%s", line1);
        printf("%s", line2);
}

FILE *open_or_stdin(const char *name)
{
        if (strcmp(name, "-") == 0) {
                return stdin;
        }

        FILE *file = fopen(name, "r");
        if (file == NULL) {
                fprintf(stderr, "no such file '%s'\n", name);
                exit(EXIT_FAILURE);
        }

        return file;
}

/* return non-zero values if and only if sub1 and sub2 are equal */
int substring_eq(struct substring sub1, struct substring sub2)
{
        int len1 = substring_length(sub1);
        int len2 = substring_length(sub2);

        if (len1 != len2) {
                return 0;
        }

        for (int i = 0; i < len1; i++) {
                if (sub1.start[i] != sub2.start[i]) {
                        return 0;
                }
        }

        return 1;
}


/* return non-zero values if and only if all substrings in subs1 are equal
 * to substrings in subs2
 */
int substrings_eq(struct substring *subs1, struct substring *subs2, int n)
{
        for (int i = 0; i < n; i++) {
                if (!substring_eq(subs1[i], subs2[i])) {
                        return 0;
                }
        }

        return 1;
}
