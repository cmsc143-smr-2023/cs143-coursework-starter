#include "students.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* prints the usage message and exit the program */
static void usage(const char *prog_name);

/* Given an input file, compress the records in the file and output the result
 * to the standard output
 */
void compress(FILE *file);

/* Given an input file, extract the records and output the result to the
 * standard output
 */
void extract(FILE *file);

int main(int argc, char *argv[])
{
        if (argc != 3) {
                usage(argv[0]);
        }

        /* parse the first command-line argument */
        bool to_compress = false;
        if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--compress") == 0) {
                to_compress = true;
        } else if (strcmp(argv[1], "-x") == 0 ||
                        strcmp(argv[1], "--extract") == 0) {
                to_compress = false;
        } else {
                usage(argv[0]);
        }

        /* parse the second command-line argument */
        FILE *file;
        if (strcmp(argv[2], "-") == 0) {
                file = stdin;
        } else {
                file = fopen(argv[2], "r");
                if (file == NULL) {
                        printf("cannot open file '%s'\n", argv[2]);
                        usage(argv[0]);
                }
        }

        if (to_compress) {
                compress(file);
        } else {
                extract(file);
        }

        if (file != stdin) {
                fclose(file);
        }

        return 0;
}

static void usage(const char *prog_name)
{
        printf("usage: %s [-c|-x] <file>\n", prog_name);
        printf("\t-c,--compress\t(c)ompress a student record file\n");
        printf("\t-x,--extract\te(x)tract a compressed file\n");
        printf("\t<file>\t the filename. If the filename is \"-\","
               " then the program will read from the standard input.\n");

        exit(EXIT_FAILURE);
}

const char FILE_HEADER[] = "CS143 student binary format\n";

void compress(FILE *file)
{
        /* output the file header for compressed format */
        printf("%s", FILE_HEADER);

        (void) file;
        assert(0 && "todo");
}

void extract(FILE *file)
{
        /* This block of code checks if the file format has the expected header.
         * If the header is not found, this function returns immediately. */
        char *header_line = NULL;
        size_t linecap;
        getline(&header_line, &linecap, file);
        if (strcmp(header_line, FILE_HEADER) != 0) {
                fprintf(stderr, "wrong binary format\n");
                return;
        }
        free(header_line);

        assert(0 && "todo");
}

