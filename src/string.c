#include "string.h"

void *_memset(void *s, int c, size_t n) {
    char *start = (char *)s;
    char *end = (char *)s + n;
    char value = (char)c;
    for (char *ptr = start; ptr != end; ++ptr)
        *ptr = value;
    return s;
}
