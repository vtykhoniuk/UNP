#include "CHelper.h"

void checker(CLinkedList*);
CLLNode *CLL_find_circle(CLinkedList*);

CLinkedList *list_no_circle();
CLinkedList *list_with_circle();
CLinkedList *list_with_circle_to_head();

int main()
{
    CLinkedList *list;

    list = list_no_circle();
    checker(list);

    list = list_with_circle();
    checker(list);

    list = list_with_circle_to_head();
    checker(list);

    exit(EXIT_SUCCESS);
}

void checker(CLinkedList *list)
{
    CLLNode *node, *n;

    node = CLL_find_circle(list);
    if (node) {
        printf("Linked List circle found at node with value [%d]\n", *((int *) node->value));

        n = node;
        while (n->next != node)
            n = n->next;

        printf("Removing circle link at node with value [%d]\n", *((int *) n->value));
        n->next = NULL;
    } else {
        printf("Linked List doesn't contain a circle\n");
    }

    printf("Destroying Linked List");
    CLL_destroy(list, destroy_int_value);
}

CLLNode *CLL_find_circle(CLinkedList* list)
{
    CLLNode *slow, *fast;

    assert(list != NULL);

    if (list->size == 0)
        return NULL;

    slow = fast = list->head;

    do {
        slow = slow->next;
        fast = fast->next;
        if (fast)
            fast = fast->next;
    } while (fast && slow != fast);

    if (fast) {
        slow = list->head;
        while (slow && fast && slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }

        if (slow && fast && slow == fast)
            return slow;
    }

    return NULL;
}

CLinkedList *list_no_circle()
{
    CLinkedList *list;
    unsigned int i;

    list = CLL_create(sizeof(int));
    for (i = 0; i < 20; ++i)
        CLL_add_node(list, (void *) &i);

    printf("Linked List of size [%ld] with no circle has been created\n", list->size);

    return list;
}

CLinkedList *list_with_circle()
{
    CLinkedList *list;
    CLLNode *node;
    unsigned int i = 0;

    list = list_no_circle();

    node = list->head;
    i = 0;
    while (node && i < 6) {
        node = node->next;
        ++i;
    }

    if (node) {
        printf("Creating a circle to the node with value [%d]\n", *((int *) node->value));
        list->tail->next = node;
    }

    return list;
}

CLinkedList *list_with_circle_to_head()
{
    CLinkedList *list;

    list = list_no_circle();

    printf("Creating a circle to head\n");
    list->tail->next = list->head;

    return list;
}
