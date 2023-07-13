/* implementation of the table module */

#include "table.h"

#include <assert.h>
#include <limits.h>
#include <stdlib.h>

/* a list of prime numbers for selecting the initial size */
static const int PRIMES[] = {
        73, 179, 283, 419, 811, 1663, 3259, 6481, 12893, 25667, 51263, INT_MAX,
};

/* representation of buckets */
struct bucket {
        void *key;
        void *value;
        struct bucket *next;
};

/* internal representation of a table */
struct table {
        int size;
        int length;
        int (*eq)(void *, void *);
        uint64_t (*hash)(void *);
        struct bucket *buckets[];
};


struct table *table_create(int hint,
                int (*eq)(void *, void *),
                uint64_t (*hash)(void *key))
{
        assert(hint >= 0);
        assert(eq != NULL && hash != NULL);

        /* find the closest prime that is greater than the hint */
        int i;
        for (i = 1; PRIMES[i] < hint; i++);
        int size = PRIMES[i - 1];

        struct table *t = malloc(sizeof(*t) + size * sizeof(t->buckets[0]));
        t->size = size;
        t->length = 0;
        t->eq = eq;
        t->hash = hash;

        for (i = 0; i < size; i++) {
                t->buckets[i] = NULL;
        }

        return t;
}

void table_free(struct table *t)
{
        assert(t != NULL);

        assert(0 && "TODO");
}

void *table_get(struct table *t, void *key)
{
        assert(t != NULL && key != NULL);

        assert(0 && "TODO");

        return NULL;
}

void *table_insert(struct table *t, void *key, void *value)
{
        assert(t != NULL && key != NULL && value != NULL);

        assert(0 && "TODO");

        return NULL;

}

void *table_remove(struct table *t, void *key)
{
        assert(t != NULL && key != NULL);

        assert(0 && "TODO");

        return NULL;
}

static void print_kv(void *key, void *value, void *data)
{
        FILE *fp = data;
        fprintf(fp, "%p -> %p\n", key, value);
}

void table_print(struct table *t, FILE *fp)
{
        table_walk(t, print_kv, fp);
}

void table_walk(struct table *t,
                void (*visit)(void *key, void *value, void *data),
                void *data)
{
        assert(t != NULL && visit != NULL);

        for (int i = 0; i < t->size; i++) {
                for (struct bucket *b = t->buckets[i]; b != NULL; b = b->next) {
                        visit(b->key, b->value, data);
                }
        }
}


