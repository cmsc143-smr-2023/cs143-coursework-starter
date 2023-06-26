/* implementation of substring.h module
 *
 * Author: Byron Zhong (byronzhong@uchicago.edu)
 */

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "substring.h"
#include "dynamic-buffer.h"

/* The following definitions are only used internally. */

// define a structure sublist containing a substring array,
// capacity (max size of the array), and length (current size)
struct sublist {
        struct substring *subs;
        int capacity;
        int length;
};

static bool is_in_sep(char c, const char *sep);
static void sublist_init(struct sublist *list);
static void sublist_append(struct sublist *list, char *start, char *end);

/******************************************************************************/
/*                            Exported Functions                              */
/******************************************************************************/

void substring_print(struct substring sub, FILE *fp)
{
        assert(fp != NULL);

        // loop over the range from start to end and print each character
        while (sub.start < sub.end) {
                fputc(*(sub.start++), fp);
        }
}

int substring_length(const struct substring sub)
{
        // length is the difference between end pointer and start pointer
        return sub.end - sub.start;
}

int split(char *s, const char *sep, struct substring **subs_p)
{
        assert(s != NULL && sep != NULL && *sep != '\0' && subs_p != NULL);

        struct sublist list;
        sublist_init(&list); // initialize the sublist

        char *start = s;
        bool in_sep = true; // flag to check if currently in separator

        for (; *s != '\0'; s++) {
                bool is_sep = is_in_sep(*s, sep);

                if (is_sep && !in_sep) {
                        // If *s is a separator but we are not already in a
                        // separator, this means we just exited a substring.
                        // We append the substring from start to the current
                        // character.
                        sublist_append(&list, start, s);
                        in_sep = true;
                } else if (!is_sep && in_sep) {
                        // If we are in a separator but this character is not,
                        // this means we just exited a run of separators.
                        // We record the start location.
                        start = s;
                        in_sep = false;
                }
        }

        if (start < s && !in_sep) {
                // After reaching the end of the string, we need to handle the
                // the last substring.
                sublist_append(&list, start, s);
        }

        if (list.length == 0) {
                free(list.subs);
                *subs_p = NULL;
                return 0;
        }

        *subs_p = list.subs;
        return list.length;
}

char *join(struct substring *subs, int length, const char *sep)
{
        assert(subs != NULL && sep != NULL);

        struct buffer buf;
        buffer_init(&buf, 32); // initialize the buffer with size 32

        bool need_sep = false; // flag to determine if separator is needed
                               // we are printing a separator before each
                               // substring except the first one
        int sep_len = strlen(sep);

        for (int i = 0; i < length; i++) {
                if (need_sep) {
                        buffer_extend(&buf, sep, sep_len);
                }
                buffer_extend(&buf, subs[i].start, subs[i].end - subs[i].start);
                need_sep = true;
        }

        buffer_append(&buf, '\0');

        return buf.start;
}

/******************************************************************************/
/*                        Helper Function Definitions                         */
/******************************************************************************/

// return true if c is in the separator string
static bool is_in_sep(char c, const char *sep)
{
        while (*sep != '\0') {
                if (c == *(sep++)) {
                        return true;
                }
        }

        return false;
}

// initialize a substring list
static void sublist_init(struct sublist *list)
{
        int capacity = 8;
        list->subs = malloc(capacity * sizeof(*list->subs));
        list->capacity = 8;
        list->length = 0;
}

// append a substring to the substring list, expand if needed
static void sublist_append(struct sublist *list, char *start, char *end)
{
        int len = list->length;
        if (len >= list->capacity) {
                list->capacity *= 2;
                list->subs = realloc(list->subs,
                                     list->capacity * sizeof(*list->subs));
        }

        list->subs[len].start = start;
        list->subs[len].end = end;

        list->length++;
}
