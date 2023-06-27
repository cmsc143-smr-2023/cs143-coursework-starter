/*
 * Implementation of a simple testing infrastructure.
 *
 * Author: Byron Zhong (byronzhong@cs.uchicago.edu)
 * Description: This file implements the "test.h" interface, providing the main
 * function for the unit tests to run and implementing the checking facilities.
 */
#include "tests.h"

#include <setjmp.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* indicate whether the jmp_buf is set */
static bool initialized = false;

/* the place to jump to in case of an error */
static jmp_buf error_jmp;

int test_main(int argc, char *argv[], struct unittest tests[], int n_tests)
{
        /* TODO: add a fail-fast flag */
        (void) argc;
        (void) argv;

        initialized = true;

        int n_test_failed = 0;
        int n_test_run = 0;
        for (int i = 0; i < n_tests; i++) {
                n_test_run++;
                if (setjmp(error_jmp) == 0) {
                        printf("Running tests: %-32s", tests[i].name);
                        tests[i].run();
                        printf("\t\tPASS\n");
                } else {
                        n_test_failed++;
                }
        }

        printf("%d tests are registered, %d tests ran, "
               "%d succeeded, %d failed.\n",
               n_tests,
               n_test_run,
               n_test_run - n_test_failed,
               n_test_failed);

        if (n_test_failed > 0) {
                return EXIT_FAILURE;
        } else {
                return EXIT_SUCCESS;
        }
}

FILE *mkfile(const char *str)
{
        return mkfilen(str, strlen(str));
}

FILE *mkfilen(const char *str, size_t n)
{
        FILE *file = tmpfile();
        if (file == NULL) {
                fprintf(stderr, "Unable to run tests because a tmpfile cannot "
                                "be created in the current directory");
                exit(EXIT_FAILURE);
        }

        for (size_t i = 0; i < n; i++) {
                fputc(str[i], file);
        }

        fflush(file);
        rewind(file);

        return file;
}

void test_fail(const char *format, ...)
{
        if (!initialized) {
                fprintf(stderr,
                        "INTERNAL ERROR: tests are run outside of test_main\n");
                abort();
        }

        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);

        longjmp(error_jmp, 1);
}

void test_expect_eq(unsigned long exp, unsigned long actual,
                const char *file, int line)
{
        if (exp == actual) {
                return;
        }

        test_fail("\t\tFAIL\n\t%s:%d: expecting %ld but received %ld\n",
                        file, line, exp, actual);
}

void test_expect_null(const void *s, const char *file, int line)
{
        if (s == NULL) {
                return;
        }

        test_fail("\t\tFAIL\n\t%s:%d: expecting NULL but received %p\n",
                        file, line, s);
}

void test_expect_non_null(const void *s, const char *file, int line)
{
        if (s != NULL) {
                return;
        }

        test_fail("\t\tFAIL\n\t%s:%d: expecting non-NULL but received NULL\n",
                        file, line);
        longjmp(error_jmp, 1);
}

void test_expect_mem(const void *s1, const void *s2, size_t n,
        const char *file, int line)
{
        if (memcmp(s1, s2, n) == 0) {
                return;
        }

        printf("\t\tFAIL\n\t%s:%d: %p and %p differ\n", file, line, s1, s2);

        if (n >= 64) {
                printf("Difference omitted.\n");
        } else {
                for (size_t i = 0; i < n; i++) {
                        char b1 = *((char *)s1 + i);
                        char b2 = *((char *)s2 + i);

                        printf("%p+%02lu: %3d, 0x%02x, '%c'\n",
                                        s1, i, b1, b1, b1);
                        printf("%p+%02lu: %3d, 0x%02x, '%c'\n",
                                        s2, i, b2, b2, b2);
                }
        }

        longjmp(error_jmp, 1);
}

void test_expect_str(const char *s1, const char *s2,
        const char *file, int line)
{
        if (strcmp(s1, s2) == 0) {
                return;
        }

        test_fail("\t\tFAIL\n\t%s:%d: \"%s\" and \"%s\" differ\n", file, line,
                        s1, s2);

}

