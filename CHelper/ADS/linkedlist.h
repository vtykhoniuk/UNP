#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

struct ADS_LinkedListNode;

typedef struct ADS_LinkedListNode {
    struct ADS_LinkedListNode *next;
    void *value;
} * ADS_LinkedListNode;

typedef struct ADS_LinkedList {
    ADS_LinkedListNode head;
    ADS_LinkedListNode tail;
    size_t size;
} * ADS_LinkedList;

typedef void (*ADS_LinkedNode_free)(void*);

ADS_LinkedList ADS_LinkedList_allocate();

void ADS_LinkedList_destroy(ADS_LinkedList);
void ADS_LinkedList_destroy_deep(ADS_LinkedList, ADS_LinkedNode_free);

void ADS_LinkedList_append_node(ADS_LinkedList, void*);
void ADS_LinkedList_prepend_node(ADS_LinkedList, void*);

void* ADS_LinkedList_remove_head(ADS_LinkedList);
void ADS_LinkedList_remove_head_deep(ADS_LinkedList, ADS_LinkedNode_free);

#endif // LINKED_LIST_H
