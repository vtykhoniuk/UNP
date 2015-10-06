#include "CHelper.h"

#include <string.h>

CLinkedList* strsplit(const char *str, const char *delim)
{
    assert(str != NULL);
    assert(strlen(str) > 0);

    CLinkedList *result = CLL_create(sizeof(char*));
    const char *token_begin = str;
    const char *token_end = str;
    char *tmp;
    size_t n;
    CLLNode *node;

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
        node = CLL_add_node(result, &tmp);
    }

    return result;
}
