#include "hls.h"

/**
 * is_char_in_str - fonction principale
 * @str: string to check
 * @c: char to compare
 *
 * Return: true if contained, false if not
 */

bool is_char_in_str(const char *str, char c)
{
    if (str == NULL) {
        return false;
    }

    while (*str != '\0') {
        if (*str == c) {
            return true;
        }
        str++;
    }

    return false;
}
