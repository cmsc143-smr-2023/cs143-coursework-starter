#ifndef SUBSTRING_H_
#define SUBSTRING_H_

#include <stdio.h>

/* representation of a substring. The data these pointers point to are assumed
 * to be alive.
 */
struct substring {
        char *start; /* pointer to the first byte of the substring */
        char *end;   /* pointer to the first byte past the end */
};

/* print the substring to file
 *
 * The data is assumed to be alive when this function is called. An
 * assertion is raised if file is NULL.
 */
void substring_print(const struct substring sub, FILE *file);

/* return the length of the substring
 */
int substring_length(const struct substring sub);

/* split a string to an array of substrings by sep.
 *
 * Given a string s, the function splits it into an array of substrings
 * separated by any character in the string sep and assigns the array to
 * *subs_p, returning the length of the array. The caller of this function is
 * responsible for freeing the array of substrings.
 *
 * An assertion is raised if s, sep, orsubs_p is NULL. Furthermore, if sep is an
 * empty string, an assertion is raised as well.
 */
int split(char *str, const char *sep, struct substring **subs_p);

/* join an array of substrings by the given separator.
 *
 * Given an array of substrings and a separator string, return a heap-allocated
 * string that has all substrings separated by sep in order. The caller of this
 * function is responsible for freeing the returned string.
 *
 * An assertion is raised if sep is NULL. sep can be an empty string.
 */
char *join(struct substring *subs, int length, const char *sep);

#endif
