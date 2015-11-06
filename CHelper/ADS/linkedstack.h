#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include "linkedlist.h"

#define ADS_LinkedStack ADS_LinkedList
#define ADS_LinkedStack_allocate ADS_LinkedList_allocate
#define ADS_LinkedStack_destroy ADS_LinkedList_destroy
#define ADS_LinkedStack_destroy_deep ADS_LinkedList_destroy_deep
#define ADS_LinkedStack_push ADS_LinkedList_prepend_node
#define ADS_LinkedStack_pop ADS_LinkedList_remove_head
#define ADS_LinkedStack_pop_deep ADS_LinkedList_remove_head_deep

#endif // LINKEDSTACK_H
