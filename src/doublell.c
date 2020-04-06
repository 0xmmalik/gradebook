/**
 * Doubly Linked List
 * by Manav Malik (2020)
 * Adapted by Manav Malik
 * for Stack Implementation (2020)
 */

#include "doublell.h"

EnqItem *initEnqItem(char *name, int val) {
    EnqItem *e = malloc(sizeof(EnqItem));
    initEnqItemPointer(e, name, val);
    return e;
}

void initEnqItemPointer(EnqItem *e, char *name, int val) {
    strcpy(e->name, name);
    e->val = val;
    e->next = e;
    e->prev = e;
}

DoublyLinkedList initDoublyLinkedList(char *name) {
    return initEnqItem(name, -1);;
}

bool isEnqueued(EnqItem *e) {
    if (e->next == e && e->prev == e)
        return false;
    return true;
}

bool isEmpty(DoublyLinkedList anchor) {
    return !isEnqueued(anchor);
}

void appendHead(EnqItem *e, DoublyLinkedList anchor) {
    e->next = anchor->next;
    anchor->next = e;
    if (anchor->prev == anchor)
        anchor->prev = e;
}

void appendTail(EnqItem *e, DoublyLinkedList anchor) {
    e->prev = anchor->prev;
    e->next = anchor;
    anchor->prev->next = e;
    anchor->prev = e;
    if (anchor->next == anchor)
        anchor->next = e;
}

void appendAfter(EnqItem *toAppend, EnqItem *inList) {
    dequeue(toAppend);
    inList->next->prev = toAppend;
    inList->next = toAppend;
}

void appendBefore(EnqItem *toAppend, EnqItem *inList) {
    dequeue(toAppend);
    inList->prev->next = toAppend;
    inList->prev = toAppend;
}

EnqItem *dequeue(EnqItem *e) {
    e->prev->next = e->next;
    e->next->prev = e->prev;
    e->next = e;
    e->prev = e;
    return e;
}

void dequeueHead(DoublyLinkedList anchor) {
    dequeue(anchor->next);
}

void dequeueTail(DoublyLinkedList anchor) {
    dequeue(anchor->prev);
}

EnqItem *getHead(DoublyLinkedList anchor) {
    return anchor->next;
}

EnqItem *getTail(DoublyLinkedList anchor) {
    return anchor->prev;
}

EnqItem *getPrevious(EnqItem *e) {
    return e->prev;
}

EnqItem *getNext(EnqItem *e) {
    return e->next;
}

char *getListName(DoublyLinkedList anchor) {
    return anchor->name;
}

char *getItemName(EnqItem *e) {
    return e->name;
}

void destroyItem(EnqItem *e) {
    dequeue(e);
    free(e->name);
    free(e);
}

DoublyLinkedList emptyList(DoublyLinkedList anchor) {
    while (!isEmpty(anchor))
        destroyItem(anchor->next);

    return anchor;
}

DoublyLinkedList destroyList(DoublyLinkedList anchor) {
    emptyList(anchor);
    free(anchor->name);
    free(anchor);

    return NULL;
}

int getLength(DoublyLinkedList anchor) {
    int len = 0;
    while (anchor != NULL) {
        len++;
        anchor = anchor->next;
    }
    return len;
}

void swapVals(EnqItem *a, EnqItem *b) {
    int temp = a->val;
    a->val = b->val;
    b->val = temp;
}

EnqItem *getElement(DoublyLinkedList anchor, int index) {
    EnqItem *current = anchor->next;

    int count = 0;
    while (current != anchor) {
        if (count == index)
            return current;
        count++;
        current = current->next;
    }

    return NULL;
}
