/* implementation of dynamic-buffer.h module
 *
 * Author: Byron Zhong (byronzhong@uchicago.edu)
 */
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "dynamic-buffer.h"

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

/******************************************************************************/
/*                        Helper Function Definitions                         */
/******************************************************************************/

void buffer_expand(struct buffer *buf_p, int new_len)
{
        // we can ignore the assertion here because this function is only
        // used internally

        int used_len = buffer_length(buf_p);
        char *new_mem = realloc(buf_p->start, new_len);

        buf_p->start = new_mem;
        buf_p->next  = new_mem + used_len;
        buf_p->end   = new_mem + new_len;
}
