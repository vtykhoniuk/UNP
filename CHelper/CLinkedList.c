#include "CLinkedList.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

CLinkedList* CLL_create(size_t sizeofval)
{
    CLinkedList *list;

    list = (CLinkedList*) malloc(sizeof(CLinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->sizeofval = sizeofval;

    return list;
}

CLLNode* CLL_add_node(CLinkedList *list, void *restrict value)
{
    CLLNode *n;

    assert(list != NULL);

    n = (CLLNode*) malloc(sizeof(CLLNode));
    n->next = NULL;
    n->value = (void*) malloc(list->sizeofval);
    memcpy(n->value, value, list->sizeofval);

    if (list->size == 0) {
        list->head = n;
        list->tail = n;
    } else {
        list->tail->next = n;
        list->tail = n;
    }

    list->size = list->size + 1;

    return n;
}

void CLL_destroy(CLinkedList *list, void (*destroy_node_value)(void*))
{
    CLLNode *node, *tmp;

    assert(list != NULL);

    if (list->size > 0) {
        node = list->head;

        while (node != NULL) {
            tmp = node->next;
            destroy_node_value(node->value);
            free(node);
            node = tmp;
        }
    }

    free(list);
}

void CLL_for_each(CLinkedList *list, void (*action)(CLLNode*))
{
    CLLNode *node;

    assert(list != NULL);

    if (list->size == 0)
        return;

    node = list->head;

    do {
        action(node);
        node = node->next;
    } while (node != NULL);
}

void destroy_int_value(void *val)
{
    free((int*) val);
}

void destroy_char_value(void *val)
{
    free((char*) val);
}

void print_int_node(CLLNode *node)
{
    printf("%3d", *((int*) node->value));
}
