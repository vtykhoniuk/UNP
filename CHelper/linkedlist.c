#include "ADS/linkedlist.h"

#include <stdlib.h>

ADS_LinkedList ADS_LinkedList_allocate()
{
    ADS_LinkedList list = malloc(sizeof(struct ADS_LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

void ADS_LinkedList_destroy(ADS_LinkedList list)
{
    ADS_LinkedListNode node = list->head;

    while (node) {
        ADS_LinkedListNode tmp = node->next;
        free(node);
        node = tmp;
    }

    free(list);
}

void ADS_LinkedList_destroy_deep(ADS_LinkedList list, ADS_LinkedNode_free destructor)
{
    ADS_LinkedListNode current = list->head;

    while (current) {
        ADS_LinkedListNode next = current->next;
        destructor(current->value);
        free(current);
        current = next;
    }

    free(list);
}

void ADS_LinkedList_append_node(ADS_LinkedList list, void *value)
{
    ADS_LinkedListNode node = malloc(sizeof(struct ADS_LinkedListNode));
    node->next = NULL;
    node->value = value;

    if (list->tail) {
        list->tail->next = node;
        list->tail = node;
    } else
        list->head = list->tail = node;

    list->size++;
}

void ADS_LinkedList_prepend_node(ADS_LinkedList list, void *value)
{
    ADS_LinkedListNode node = malloc(sizeof(struct ADS_LinkedListNode));
    node->next = NULL;
    node->value = value;

    if (list->size) {
        node->next = list->head;
        list->head = node;
    } else
        list->head = list->tail = node;

    list->size++;
}

void* ADS_LinkedList_remove_head(ADS_LinkedList list)
{
    if (list->size == 0)
        return NULL;

    void *val = list->head->value;

    if (list->size == 1) {
        free(list->head);
        list->head = list->tail = NULL;
    } else {
        ADS_LinkedListNode next = list->head->next;
        free(list->head);
        list->head = next;
    }

    list->size--;

    return val;
}

void ADS_LinkedList_remove_head_deep(ADS_LinkedList list, ADS_LinkedNode_free destructor)
{
    void *v = ADS_LinkedList_remove_head(list);
    destructor(v);
}
