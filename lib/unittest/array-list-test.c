/* unit-testing for array-list */

#include "array-list.h"
#include "tests.h"

#include <stdlib.h>
#include <stdint.h>

void create_free(void)
{
        struct alist *l = alist_create();
        alist_free(l);
}

void simple_append(void)
{
        struct alist *l = alist_create();

        for (int i = 0; i < 1024; i++) {
                alist_append(l, (void *)(intptr_t) i);
        }

        for (int i = 0; i < 1024; i++) {
                long num = (intptr_t) *alist_at(l, i);
                expect_eq(i, num);
        }

        alist_free(l);
}

void simple_prepend(void)
{
        struct alist *l = alist_create();

        for (int i = 0; i < 1024; i++) {
                alist_prepend(l, (void *)(intptr_t) i);
        }

        for (int i = 0; i < 1024; i++) {
                long num = (intptr_t) *alist_at(l, i);
                expect_eq(1024 - i - 1, num);
        }

        alist_free(l);
}

void test_len(void)
{
        struct alist *l = alist_create();

        for (int i = 0; i < 1024; i++) {
                alist_append(l, (void *)(intptr_t) i);
        }

        expect_eq(1024, alist_len(l));

        alist_free(l);
}

void test_insert_at(void)
{
        struct alist *l = alist_create();

        for (int i = 0; i < 1024; i++) {
                alist_append(l, (void *)(intptr_t) i);
        }

        for (int i = 0; i < 1024; i++) {
                alist_insert_at(l, 0, (void *)(intptr_t) i);
        }

        expect_eq(2048, alist_len(l));

        for (int i = 0; i < 1024; i++) {
                long num = (intptr_t) *alist_at(l, i);
                expect_eq(1024 - i - 1, num);
        }

        alist_free(l);
}

void test_remove_at(void)
{
        struct alist *l = alist_create();

        for (int i = 0; i < 1024; i++) {
                alist_append(l, (void *)(intptr_t) i);
        }

        expect_eq(1024, alist_len(l));

        for (int i = 0; i < 1024; i++) {
                long num = (intptr_t) *alist_at(l, 0);
                expect_eq(i, num);
                alist_remove_at(l, 0);
        }

        expect_eq(0, alist_len(l));

        alist_free(l);
}

void test_empty(void)
{
        struct alist *l = alist_create();
        expect_eq(true, alist_is_empty(l));

        alist_append(l, NULL);

        expect_eq(false, alist_is_empty(l));
        alist_free(l);
}

struct unittest tests[] = {
        Test(create_free),
        Test(simple_append),
        Test(simple_prepend),
        Test(test_len),
        Test(test_insert_at),
        Test(test_remove_at),
        Test(test_empty),
};

const int n_tests = sizeof(tests) / sizeof(tests[0]);

int main(int argc, char *argv[])
{
        return test_main(argc, argv, tests, n_tests);
}

