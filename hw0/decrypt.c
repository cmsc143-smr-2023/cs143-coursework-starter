/*
 * Decrypting text using Caesar Encryption.
 * Author: Byron Zhong (byronzhong@uchicago.edu)
 *
 * Description: DECRYPTION SOLUTION.
 */

#include <stdio.h>
#include <stdlib.h>

/* the number of letters we are shifting */
const char KEY = 15;

/* the number of letters in the alphabet */
const int N_LETTERS_IN_ALPHABET = 26;

/*
 * Given any character c, return a non-zero value if c is between 'A' and 'Z'
 * and zero otherwise.
 */
int is_upper_letter(char c);

/*
 * Given any character c, return a non-zero value if c is between 'a' and 'z'
 * and zero otherwise.
 */
int is_lower_letter(char c);

/*
 * Given any character c, the first letter in the alphabet, and a shift amount,
 * return the character shifted toward the first letter, wrapping to the back if
 * needed
 */
char shift_down_by(char c, char first, char shift_amount);

int main(void)
{
        int c;
        while ((c = getchar()) != EOF) {
                char result;
                if (is_upper_letter(c)) {
                        result = shift_down_by(c, 'A', KEY);
                } else if (is_lower_letter(c)) {
                        result = shift_down_by(c, 'a', KEY);
                } else {
                        result = c;
                }
                putchar(result);
        }

        return EXIT_SUCCESS;
}

/******************************************************************************/
/*                        Helper Function Definitions                         */
/******************************************************************************/

int is_upper_letter(char c)
{
        return 'A' <= c && c <= 'Z';
}

int is_lower_letter(char c)
{
        return 'a' <= c && c <= 'z';
}

char shift_down_by(char c, char first, char shift_amount)
{
        int n_alpha = c - first;
        if (n_alpha - shift_amount < 0) {
                n_alpha = n_alpha - shift_amount + N_LETTERS_IN_ALPHABET;
        } else {
                n_alpha = n_alpha - shift_amount;
        }
        return first + n_alpha;
}

