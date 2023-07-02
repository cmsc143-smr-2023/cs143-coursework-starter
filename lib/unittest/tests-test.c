/* Unit-testing the testing framework */
#include "tests.h"

#include <assert.h>
#include <signal.h>

void should_all_pass(void)
{
        expect_eq(1 + 2, 3);
        expect_null(NULL);
        expect_non_null((void *) should_all_pass);
        char hello[] = "hello";
        expect_mem(hello, hello, 5);
        expect_str(hello, hello);
}

void should_fail(void)
{
        expect_eq(1 + 1, 3);
}

void should_abort(void)
{
        assert(0);
}

void should_segfault(void)
{
        raise(SIGSEGV);
}

struct unittest tests[] = {
        Test(should_all_pass),
        Test(should_fail),
        Test(should_abort),
        Test(should_segfault),
};

const int n_tests = sizeof(tests) / sizeof(tests[0]);

int main(int argc, char *argv[])
{
        (void) n_tests;
        return test_main(argc, argv, tests, 1);
}
