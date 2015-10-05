#ifndef CLINKEDLIST_H
#define CLINKEDLIST_H

#include <stddef.h>

typedef struct _CLLNode {
    struct _CLLNode *next;
    void *value;
} CLLNode;

typedef struct {
    CLLNode *head;
    CLLNode *tail;
    size_t size;
    size_t sizeofval;
} CLinkedList;

CLinkedList* CLL_create(size_t sizeofval);
CLLNode* CLL_add_node(CLinkedList *list, void *restrict value);
void CLL_destroy(CLinkedList *list, void (*destroy_node_value)(void*));
void CLL_for_each(CLinkedList *list, void (*action)(CLLNode*));
void destroy_int_value(void *val);
void destroy_char_value(void *val);
void print_int_node(CLLNode *node);
void print_char_node(CLLNode *node);

#endif // CLINKEDLIST_H
