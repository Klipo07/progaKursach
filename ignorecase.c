#include <ctype.h>

#include "ignorecase.h"

int strcasecmp_custom(const char* str1, const char* str2) {
    while (*str1 && *str2) {
        int diff = tolower(*str1) - tolower(*str2);
        if (diff != 0) {
            return diff;
        }
        str1++;
        str2++;
    }
    return tolower(*str1) - tolower(*str2);
}