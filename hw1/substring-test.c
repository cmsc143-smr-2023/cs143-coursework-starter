/*
 * Unit tests for substring.h using criterion.
 *
 * Author: Byron Zhong (byronzhong@uchicago.edu)
 */

#include <criterion/criterion.h>

#include "substring.h"

Test(substring, 00_length_simple)
{
        char *test = "hello";
        struct substring sub = { .start = test, .end = test + 5 };

        cr_expect_eq(substring_length(sub), 5);
}

Test(substring, 01_length_zero)
{
        char *test = "hello";
        struct substring sub = { .start = test, .end = test };

        cr_expect_eq(substring_length(sub), 0);
}

Test(substring, 02_split_simple)
{
        struct substring *subs;

        int n = split("usr/bin/clang", "/", &subs);

        cr_assert_eq(n, 3);

        cr_expect_arr_eq(subs[0].start, "usr", substring_length(subs[0]));
        cr_expect_arr_eq(subs[1].start, "bin", substring_length(subs[1]));
        cr_expect_arr_eq(subs[2].start, "clang", substring_length(subs[2]));

        free(subs);
}

Test(substring, 03_split_start)
{
        struct substring *subs;

        int n = split("/usr/bin/clang", "/", &subs);

        cr_assert_eq(n, 3);

        cr_expect_arr_eq(subs[0].start, "usr", substring_length(subs[0]));
        cr_expect_arr_eq(subs[1].start, "bin", substring_length(subs[1]));
        cr_expect_arr_eq(subs[2].start, "clang", substring_length(subs[2]));

        free(subs);
}

Test(substring, 04_split_end)
{
        struct substring *subs;

        int n = split("/usr/bin/clang/", "/", &subs);

        cr_assert_eq(n, 3);

        cr_expect_arr_eq(subs[0].start, "usr", substring_length(subs[0]));
        cr_expect_arr_eq(subs[1].start, "bin", substring_length(subs[1]));
        cr_expect_arr_eq(subs[2].start, "clang", substring_length(subs[2]));

        free(subs);
}

Test(substring, 05_split_none)
{
        struct substring *subs;

        int n = split("hello", "/", &subs);

        cr_assert_eq(n, 1);

        cr_expect_arr_eq(subs[0].start, "hello", substring_length(subs[0]));

        free(subs);
}

Test(substring, 06_split_start_many)
{
        struct substring *subs;

        int n = split("/////usr/bin/clang/", "/", &subs);

        cr_assert_eq(n, 3);

        cr_expect_arr_eq(subs[0].start, "usr", substring_length(subs[0]));
        cr_expect_arr_eq(subs[1].start, "bin", substring_length(subs[1]));
        cr_expect_arr_eq(subs[2].start, "clang", substring_length(subs[2]));

        free(subs);
}

Test(substring, 07_split_middle_many)
{
        struct substring *subs;

        int n = split("/////usr////bin/clang/", "/", &subs);

        cr_assert_eq(n, 3);

        cr_expect_arr_eq(subs[0].start, "usr", substring_length(subs[0]));
        cr_expect_arr_eq(subs[1].start, "bin", substring_length(subs[1]));
        cr_expect_arr_eq(subs[2].start, "clang", substring_length(subs[2]));

        free(subs);
}

Test(substring, 08_split_end_many)
{
        struct substring *subs;

        int n = split("/////usr////bin/clang/////", "/", &subs);

        cr_assert_eq(n, 3);

        cr_expect_arr_eq(subs[0].start, "usr", substring_length(subs[0]));
        cr_expect_arr_eq(subs[1].start, "bin", substring_length(subs[1]));
        cr_expect_arr_eq(subs[2].start, "clang", substring_length(subs[2]));

        free(subs);
}

Test(substring, 09_sep_many)
{
        struct substring *subs;

        int n = split("usr \nbin\t clang\t", " \t\n\r", &subs);

        cr_assert_eq(n, 3);

        cr_expect_arr_eq(subs[0].start, "usr", substring_length(subs[0]));
        cr_expect_arr_eq(subs[1].start, "bin", substring_length(subs[1]));
        cr_expect_arr_eq(subs[2].start, "clang", substring_length(subs[2]));

        free(subs);
}

Test(substring, 10_join_simple)
{
        struct substring *subs;

        int n = split("/usr/bin/clang", "/", &subs);
        char *str = join(subs, n, "/");

        cr_expect_str_eq(str, "usr/bin/clang");

        free(subs);
        free(str);
}

Test(substring, 11_join_long_sep)
{
        struct substring *subs;

        int n = split("/usr/bin/clang", "/", &subs);
        char *str = join(subs, n, "////");

        cr_expect_str_eq(str, "usr////bin////clang");

        free(subs);
        free(str);
}

Test(substring, 12_empty_sep)
{
        struct substring *subs;

        int n = split("/usr/bin/clang", "/", &subs);
        char *str = join(subs, n, "");

        cr_expect_str_eq(str, "usrbinclang");

        free(subs);
        free(str);
}

/* ... ADD MORE TESTS HERE ... */

