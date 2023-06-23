/* implementation of substring.h module
 * Author: YOUR NAME HERE
 */

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "substring.h"
#include "dynamic-buffer.h"

struct sublist {
        struct substring *subs;
        int capacity;
        int length;
};

static bool is_in_sep(char c, const char *sep);
static void sublist_init(struct sublist *list);
static void sublist_append(struct sublist *list, char *start, char *end);

void substring_print(struct substring sub, FILE *fp)
{
        assert(fp != NULL);

        while (sub.start < sub.end) {
                fputc(*(sub.start++), fp);
        }
}

int substring_length(const struct substring sub)
{
        return sub.end - sub.start;
}

int split(char *s, const char *sep, struct substring **subs_p)
{
        assert(s != NULL && sep != NULL && *sep != '\0' && subs_p != NULL);

        struct sublist list;
        sublist_init(&list);

        char *start = s;
        bool in_sep = true;

        for (; *s != '\0'; s++) {
                bool is_sep = is_in_sep(*s, sep);

                if (is_sep && !in_sep) {
                        sublist_append(&list, start, s);
                        in_sep = true;
                } else if (!is_sep && in_sep) {
                        start = s;
                        in_sep = false;
                }
        }

        if (start < s && !in_sep) {
                sublist_append(&list, start, s);
        }

        *subs_p = list.subs;
        return list.length;
}

char *join(struct substring *subs, int length, const char *sep)
{
        assert(subs != NULL && sep != NULL);

        struct buffer buf;
        buffer_init(&buf, 32);

        bool need_sep = false;
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


static bool is_in_sep(char c, const char *sep)
{
        while (*sep != '\0') {
                if (c == *(sep++)) {
                        return true;
                }
        }

        return false;
}

static void sublist_init(struct sublist *list)
{
        int capacity = 8;
        list->subs = malloc(capacity * sizeof(*list->subs));
        list->capacity = 8;
        list->length = 0;
}

static void sublist_append(struct sublist *list, char *start, char *end)
{
        if (list->length >= list->capacity) {
                list->capacity *= 2;
                list->subs = realloc(list->subs,
                                     list->capacity * sizeof(*list->subs));
        }

        int len = list->length;
        list->subs[len].start = start;
        list->subs[len].end = end;

        list->length++;
}
