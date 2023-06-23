/* implementation of readline.h module
 *
 * Author: Byron Zhong (byronzhong@uchicago.edu)
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "readline.h"
#include "dynamic-buffer.h"

int readline(FILE *file, char **line_p)
{
        assert(file != NULL && line_p != NULL);

        struct buffer buf;
        buffer_init(&buf, 32);

        int c;
        while ((c = fgetc(file)) != EOF) {
                buffer_append(&buf, c);
                if (c == '\n') {
                        break;
                }
        }

        int len = buffer_length(&buf);
        if (len == 0) {
                free(buf.start);
                *line_p = NULL;
                return 0;
        }

        buffer_append(&buf, '\0');
        *line_p = buf.start;
        return len;
}
