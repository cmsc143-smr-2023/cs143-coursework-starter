#include "linked-list.h"

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

/* You don't need to understand the implementation of this function */
struct llist *llist_list(void *x, ...)
{
        va_list args;
        struct llist *list = NULL;
        struct llist **curr_p = &list;

        va_start(args, x);
        for(; x != NULL; x = va_arg(args, void *)) {
                *curr_p = malloc(sizeof(**curr_p));
                (*curr_p)->elem = x;
                curr_p = &(*curr_p)->next;
        }
        va_end(args);

        *curr_p = NULL;
        return list;
}

void llist_free(struct llist *l)
{
        (void) l;
        assert(0 && "TODO");
}

struct llist *llist_append(struct llist *l, void *elem)
{
        (void) l, (void) elem;
        assert(0 && "TODO");
        return NULL;
}

struct llist *llist_prepend(struct llist *l, void *elem)
{
        (void) l, (void) elem;
        assert(0 && "TODO");
        return NULL;
}

void llist_print(struct llist *l, FILE *file)
{
        for (; l != NULL; l = l->next) {
                fprintf(file, "%p->", l->elem);
        }
        fputs("NULL", file);
}


struct llist *llist_concat(struct llist *l, struct llist *tail)
{
        (void) l, (void) tail;
        assert(0 && "TODO");
        return NULL;
}

struct llist *llist_copy(struct llist *l)
{
        (void) l;
        assert(0 && "TODO");
        return NULL;
}

struct llist *llist_reverse(struct llist *l)
{
        struct llist *prev = NULL, *curr = l, *next;

        while (curr != NULL) {
                next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
        }

        return prev;
}

struct llist *llist_insert_at(struct llist *l, int i, void *elem)
{
        (void) l, (void) i, (void) elem;
        assert(0 && "TODO");
        return NULL;
}

/* return the resulting list, but assign the removed element to *elem_p */
struct llist *llist_remove_at(struct llist *l, int i, void **elem_p)
{
        (void) l, (void) i, (void) elem;
        assert(0 && "TODO");
        return NULL;
}

int llist_len(struct llist *l)
{
        (void) l;
        return 0;
}
