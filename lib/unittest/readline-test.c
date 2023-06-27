/* Unit-testing the readline function */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "readline.h"
#include "tests.h"

void simple(void)
{
        const char *test = "Hello, world!\nHello";
        FILE *file = mkfile(test);

        char *line = NULL;
        int len = readline(file, &line);

        expect_non_null(line);                           // line is not NULL
        expect_eq(len, (int) strlen("Hello, world!\n")); // len is correct

        expect_str(line, "Hello, world!\n"); // line has correct content

        free(line);
        fclose(file);
}

void simple_no_newline(void)
{
        const char *test = "Hello, world!";
        FILE *file = mkfile(test);

        char *line = NULL;
        int len = readline(file, &line);

        expect_non_null(line);
        expect_eq(len, (int) strlen(test));
        expect_str(line, test);

        free(line);
        fclose(file);
}

void simple_empty(void)
{
        const char *test = "";
        FILE *file = mkfile(test);

        char *line = NULL;
        int len = readline(file, &line);

        expect_eq(len, 0); // len should be 0
        expect_null(line); // line should be NULL

        fclose(file);
}

void simple_all(void)
{
        const char *test = "Hello, world!\nHello";
        FILE *file = mkfile(test);

        char *line = NULL;
        int len = readline(file, &line);

        // the first line: "Hello, world!\n"
        const char *expected = "Hello, world!\n";
        expect_non_null(line);
        expect_eq(len, (int) strlen(expected));
        expect_str(line, expected);
        free(line);

        // the second line: "Hello"
        len = readline(file, &line);
        expected = "Hello";
        expect_non_null(line);
        expect_eq(len, (int) strlen(expected));
        expect_str(line, expected);
        free(line);

        // reading again should return 0
        len = readline(file, &line);
        expect_eq(len, 0);
        expect_null(line);

        fclose(file);
}

void confused_with_EOF(void)
{
        const char *test = "Hello,\xFFworld!\n";
        FILE *file = mkfile(test);

        char *line = NULL;
        int len = readline(file, &line);

        expect_non_null(line);
        expect_eq(len, (int) strlen(test));
        expect_str(line, test);

        free(line);
        fclose(file);
}

void nul_in_line(void)
{
        const char *test = "Hello,\0world!\n";
        FILE *file = mkfilen(test, 14);

        char *line = NULL;
        int len = readline(file, &line);

        expect_non_null(line);
        expect_eq(len, 14);

        for (int i = 0; i < len; i++) {
                expect_eq(line[i], test[i]);
        }

        free(line);
        fclose(file);
}

void long_line(void)
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

        expect_non_null(line);
        expect_eq(len, (int) strlen(test));
        expect_str(line, test);

        free(line);
        fclose(file);
}

struct unittest tests[] = {
        Test(simple),
        Test(simple_no_newline),
        Test(simple_empty),
        Test(simple_all),
        Test(confused_with_EOF),
        Test(nul_in_line),
        Test(long_line),
};

const int n_tests = sizeof(tests) / sizeof(tests[0]);

int main(int argc, char *argv[])
{
        return test_main(argc, argv, tests, n_tests);
}

