#include "CHelper.h"

size_t strsplit(const char *str, const char *delim, ADS_LinkedList list)
{
    assert(str != NULL);
    assert(strlen(str) > 0);
    assert(list != NULL);

    const char *token_begin = str;
    const char *token_end = str;
    char *tmp;
    size_t n;

    // While not end of the string
    while (*token_begin != '\0') {
        // Looking for a non-delimiter character
        for (token_begin = token_end; *token_begin != '\0' && strchr(delim, *token_begin) != NULL; ++token_begin);

        // If we reach end of string
        if (*token_begin == '\0')
            break;

        // Looking for delimiter
        for (token_end = token_begin; *token_end != '\0' && strchr(delim, *token_end) == NULL; ++token_end);

        // Dedicate new memory and copy token
        n = token_end-token_begin+1;
        tmp = malloc(n);
        memcpy(tmp, token_begin, n-1);
        tmp[n-1] = '\0';

        // Create new list node
        ADS_LinkedList_append_node(list, &tmp);
    }

    return list->size;
}
