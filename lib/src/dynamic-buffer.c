/* implementation of dynamic-buffer.h module
 *
 * Author: Byron Zhong (byronzhong@uchicago.edu)
 */
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "dynamic-buffer.h"

/* helper function used internally */
static void buffer_expand(struct buffer *buf_p, int new_len);

/******************************************************************************/
/*                            Exported Functions                              */
/******************************************************************************/

void buffer_init(struct buffer *buf_p, int len)
{
        assert(buf_p != NULL);

        char *mem = malloc(len);

        buf_p->start = mem;
        buf_p->next  = mem;
        buf_p->end   = mem + len;
}

int buffer_capacity(struct buffer *buf_p)
{
        assert(buf_p != NULL);

        return buf_p->end - buf_p->start;
}

int buffer_length(struct buffer *buf_p)
{
        assert(buf_p != NULL);

        return buf_p->next - buf_p->start;
}

void buffer_append(struct buffer *buf_p, char c)
{
        assert(buf_p != NULL && buf_p->start != NULL);

        if (buf_p->next == buf_p->end) {
                buffer_expand(buf_p, buffer_length(buf_p) * 2);
        }

        *(buf_p->next++) = c;
}

void buffer_extend(struct buffer *buf_p, const char *str, int n)
{
        assert(buf_p != NULL && buf_p->start != NULL && str != NULL);

        for (int i = 0; i < n; i++) {
                buffer_append(buf_p, str[i]);
        }
}

/******************************************************************************/
/*                        Helper Function Definitions                         */
/******************************************************************************/

static void buffer_expand(struct buffer *buf_p, int new_len)
{
        // we can ignore the assertion here because this function is only
        // used internally

        int used_len = buffer_length(buf_p);
        char *new_mem = realloc(buf_p->start, new_len);

        buf_p->start = new_mem;
        buf_p->next  = new_mem + used_len;
        buf_p->end   = new_mem + new_len;
}
