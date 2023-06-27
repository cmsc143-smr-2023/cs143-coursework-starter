/* Unit-testing the dynamic-buffer */

#include <stdlib.h>

#include "dynamic-buffer.h"
#include "tests.h"

void simple(void)
{
        struct buffer buf;
        buffer_init(&buf, 4);
        expect_eq(4, buffer_capacity(&buf));
        expect_eq(0, buffer_length(&buf));

        buffer_append(&buf, 'a');
        buffer_append(&buf, 'b');
        buffer_append(&buf, 'c');
        buffer_append(&buf, 'd');

        expect_eq(4, buffer_length(&buf));

        buffer_extend(&buf, "efg", 3);
        buffer_append(&buf, '\0');

        expect_str("abcdefg", buf.start);

        free(buf.start);
}

struct unittest tests[] = {
        Test(simple),
};

const int n_tests = sizeof(tests) / sizeof(tests[0]);

int main(int argc, char *argv[])
{
        return test_main(argc, argv, tests, n_tests);
}




