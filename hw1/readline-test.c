/*
 * Unit tests for readline.h using criterion.
 *
 * Author: Byron Zhong (byronzhong@uchicago.edu)
 * Description: this file tests for properties that your readline implementation
 * should satisfy. The test works by creating a temporary file on the disk and
 * writing the test contents into the file; we then check whether the readline
 * function reads the same string as we put in.
 */

#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include "readline.h"

/* create a temporary file that contains str; the returned file pointer is
 * rewound to the beginning */
FILE *mkfile(const char *str);

/* same as the above, but takes the length as argument */
FILE *mkfilen(const char *str, int n);

/* reading one line */
Test(readline, 01_simple)
{
        const char *test = "Hello, world!\nHello";
        FILE *file = mkfile(test);

        char *line = NULL;
        int len = readline(file, &line);

        cr_assert_not_null(line);                           // line is not NULL
        cr_assert_eq(len, (int) strlen("Hello, world!\n")); // len is correct

        cr_expect_str_eq(line, "Hello, world!\n"); // line has correct content

        free(line);
        fclose(file);
}

/* reading the last line (line not ended by \n) */
Test(readline, 02_simple_no_newline)
{
        const char *test = "Hello, world!";
        FILE *file = mkfile(test);

        char *line = NULL;
        int len = readline(file, &line);

        cr_assert_not_null(line);
        cr_assert_eq(len, (int) strlen(test));
        cr_expect_str_eq(line, test);

        free(line);
        fclose(file);
}

/* reading empty file */
Test(readline, 03_simple_empty)
{
        const char *test = "";
        FILE *file = mkfile(test);

        char *line = NULL;
        int len = readline(file, &line);

        cr_assert_eq(len, 0); // len should be 0
        cr_assert_null(line); // line should be NULL

        fclose(file);
}

/* reading all contents from the file */
Test(readline, 04_simple_all)
{
        const char *test = "Hello, world!\nHello";
        FILE *file = mkfile(test);

        char *line = NULL;
        int len = readline(file, &line);

        // the first line: "Hello, world!\n"
        const char *expected = "Hello, world!\n";
        cr_assert_not_null(line);
        cr_assert_eq(len, (int) strlen(expected));
        cr_expect_str_eq(line, expected);
        free(line);

        // the second line: "Hello"
        len = readline(file, &line);
        expected = "Hello";
        cr_assert_not_null(line);
        cr_assert_eq(len, (int) strlen(expected));
        cr_expect_str_eq(line, expected);
        free(line);

        // reading again should return 0
        len = readline(file, &line);
        cr_expect_eq(len, 0);
        cr_expect_null(line);

        fclose(file);
}

/* contains a character that looks like EOF */
Test(readline, 05_confused_with_EOF)
{
        const char *test = "Hello,\xFFworld!\n";
        FILE *file = mkfile(test);

        char *line = NULL;
        int len = readline(file, &line);

        cr_assert_not_null(line);
        cr_assert_eq(len, (int) strlen(test));
        cr_expect_str_eq(line, test);

        free(line);
        fclose(file);
}

/* contains \0 in the line */
Test(readline, 06_nul_in_line)
{
        const char *test = "Hello,\0world!\n";
        FILE *file = mkfilen(test, 14);

        char *line = NULL;
        int len = readline(file, &line);

        cr_assert_not_null(line);
        cr_assert_eq(len, 14);

        for (int i = 0; i < len; i++) {
                cr_expect_eq(line[i], test[i]);
        }

        free(line);
        fclose(file);
}

/* readline should abort if file is NULL */
Test(readline, 07_null_file, .signal = SIGABRT)
{
        char *line;
        readline(NULL, &line);
}

/* readline should abort if line_p is NULL */
Test(readline, 08_null_line_p, .signal = SIGABRT)
{
        FILE *file = mkfile("hello");
        readline(file, NULL);
        fclose(file);
}

/* reading a very long line */
Test(readline, 09_long_line)
{
        const char *test = "I am a really really really really really really"
                           "really really really really really really really"
                           "really really really really really really really"
                           "really really really really really really really"
                           "really really really really really really really"
                           "really really really really really really really"
                           "really really really really really really really"
                           "really really really really really really really"
                           "really really really really really really really"
                           "really really really really really really really"
                           "really really really really really really really"
                           "really really really really really really really"
                           "really really really really really really really"
                           "really really really really really really really"
                           "really long line\n";
        FILE *file = mkfile(test);

        char *line = NULL;
        int len = readline(file, &line);

        cr_assert_not_null(line);
        cr_assert_eq(len, (int) strlen(test));
        cr_expect_str_eq(line, test);

        free(line);
        fclose(file);
}

/* ... ADD MORE TESTS HERE ... */


/*************** Helper Function ****************/
FILE *mkfile(const char *str)
{
        return mkfilen(str, strlen(str));
}

FILE *mkfilen(const char *str, int n)
{
        FILE *file = tmpfile();
        if (file == NULL) {
                fprintf(stderr, "Unable to run tests because a tmpfile cannot "
                                "be created in the current directory");
                exit(EXIT_FAILURE);
        }

        for (int i = 0; i < n; i++) {
                fputc(str[i], file);
        }

        fflush(file);
        rewind(file);

        return file;
}

