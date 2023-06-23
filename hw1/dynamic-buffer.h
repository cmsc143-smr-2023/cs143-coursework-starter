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
int buffer_capacity(struct buffer *buf_p);

/* return the length of the buffer
 */
int buffer_length(struct buffer *buf_p);

/* append a character to the end of the buffer, reallocate if necessary
 */
void buffer_append(struct buffer *buf_p, char c);

/* append a string to the end of the buffer, reallocate if necessary
 */
void buffer_extend(struct buffer *buf_p, const char *str, int n);

#endif
