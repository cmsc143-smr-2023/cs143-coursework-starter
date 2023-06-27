/* Unit-testing the testing framework */
#include "tests.h"

void should_all_pass(void)
{
        expect_eq(1 + 2, 3);
        expect_null(NULL);
        expect_non_null((void *) should_all_pass);
        char hello[] = "hello";
        expect_mem(hello, hello, 5);
        expect_str(hello, hello);
}

struct unittest tests[] = {
        Test(should_all_pass)
};

const int n_tests = sizeof(tests) / sizeof(tests[0]);

int main(int argc, char *argv[])
{
        return test_main(argc, argv, tests, n_tests);
}
