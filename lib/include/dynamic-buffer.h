#ifndef DYNAMIC_BUFFER_H_
#define DYNAMIC_BUFFER_H_

struct buffer {
        char *start; /* the starting byte of the buffer         */
        char *next;  /* the next unused byte in the buffer      */
        char *end;   /* the first byte past the allocated space */
};

/* allocate and initialize buffer with given initial capacity
 */
void buffer_init(struct buffer *buf_p, int len);

/* return the capacity of the buffer
 */
static inline int buffer_capacity(struct buffer *buf_p);

/* return the length of the buffer
 */
static inline int buffer_length(struct buffer *buf_p);

/* append a character to the end of the buffer, reallocate if necessary
 */
static inline void buffer_append(struct buffer *buf_p, char c);

/* append a string to the end of the buffer, reallocate if necessary
 */
static inline void buffer_extend(struct buffer *buf_p, const char *str, int n);


/* inlining definitions */
#include <assert.h>

void buffer_expand(struct buffer *buf_p, int new_len);

static inline int buffer_capacity(struct buffer *buf_p)
{
        assert(buf_p != NULL);

        return buf_p->end - buf_p->start;
}

static inline int buffer_length(struct buffer *buf_p)
{
        assert(buf_p != NULL);

        return buf_p->next - buf_p->start;
}

static inline void buffer_append(struct buffer *buf_p, char c)
{
        assert(buf_p != NULL && buf_p->start != NULL);

        if (buf_p->next == buf_p->end) {
                buffer_expand(buf_p, buffer_length(buf_p) * 2);
        }

        *(buf_p->next++) = c;
}

static inline void buffer_extend(struct buffer *buf_p, const char *str, int n)
{
        assert(buf_p != NULL && buf_p->start != NULL && str != NULL);

        for (int i = 0; i < n; i++) {
                buffer_append(buf_p, str[i]);
        }
}

#endif
