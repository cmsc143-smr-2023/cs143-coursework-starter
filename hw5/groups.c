#include "table.h"
#include "array-list.h"
#include "hash.h"
#include "readline.h"
#include "substring.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct table *index_file(FILE *file);
void add_entry(struct table *t, char *fingerprint, char *name);
void print_group(void *key, void *value, void *data);
void free_group(void *key, void *value, void *data);

int main(int argc, char *argv[])
{
        if (argc != 2) {
                printf("usage: %s <file>\n", argv[0]);
                return EXIT_FAILURE;
        }

        FILE *file = fopen(argv[1], "r");
        if (file == NULL) {
                printf("cannot open '%s'\n", argv[1]);
                return EXIT_FAILURE;
        }

        struct table *table = index_file(file);
        fclose(file);

        table_walk(table, print_group, NULL);
        table_walk(table, free_group, NULL);

        table_free(table);
        return EXIT_SUCCESS;
}

struct table *index_file(FILE *file)
{
        struct table *table = table_create(1000, strcmp_, strhash);

        int len;
        char *line;
        while ((len = readline(file, &line)) != 0) {
                struct substring *subs;
                int n_subs = split(line, "\t\n", &subs);

                assert(n_subs == 2);

                char *fingerprint = strndup(subs[0].start,
                                            substring_length(subs[0]));
                char *name = strndup(subs[1].start,
                                     substring_length(subs[1]));

                add_entry(table, fingerprint, name);

                free(subs);
                free(line);
        }

        return table;
}

void add_entry(struct table *t, char *fingerprint, char *name)
{
        struct alist *list = table_get(t, fingerprint);

        if (list == NULL) {
                list = alist_create();
                table_insert(t, fingerprint, list);
        } else {
                free(fingerprint);
        }

        alist_append(list, name);
}

void print_group(void *key, void *value, void *data)
{
        char *fingerprint = key;
        struct alist *list = value;
        (void) data;

        int len = alist_len(list);
        if (len < 2) {
                return;
        }

        printf("%s:\n", fingerprint);
        for (int i = 0; i < len; i++) {
                char *name = *alist_at(list, i);
                printf("%s\n", name);
        }
        putchar('\n');
}

void free_group(void *key, void *value, void *data)
{
        (void) data;

        struct alist *list = value;

        int len = alist_len(list);
        for (int i = 0; i < len; i++) {
                char *name = *alist_at(list, i);
                free(name);
        }
        alist_free(list);
        free(key);
}
