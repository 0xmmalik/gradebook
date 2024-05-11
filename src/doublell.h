/**
 * Doubly Linked List
 * by Manav Malik (2020)
 */

#ifndef DOUBLELL_H
#define DOUBLELL_H

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct EnqItem {
    char name[64];
    void *data;
    struct EnqItem *prev;
    struct EnqItem *next;
} EnqItem;

typedef EnqItem *DoublyLinkedList;

EnqItem *initEnqItem(char *name, void *data);

void initEnqItemPointer(EnqItem *e, char *name, void *data);

DoublyLinkedList initDoublyLinkedList(char *name);

bool isEnqueued(EnqItem *);

bool isEmpty(DoublyLinkedList);

void appendHead(EnqItem *, DoublyLinkedList);

void appendTail(EnqItem *, DoublyLinkedList);

void appendAfter(EnqItem *, EnqItem *);

void appendBefore(EnqItem *, EnqItem *);

EnqItem *dequeue(EnqItem *);

EnqItem *dequeueHead(DoublyLinkedList);

EnqItem *dequeueTail(DoublyLinkedList);

EnqItem *getHead(DoublyLinkedList);

EnqItem *getTail(DoublyLinkedList);

EnqItem *getPrevious(EnqItem *);

EnqItem *getNext(EnqItem *);

char *getName(DoublyLinkedList);

char *getItemName(EnqItem *);

void destroyItem(EnqItem *);

DoublyLinkedList emptyList(DoublyLinkedList);

DoublyLinkedList destroyList(DoublyLinkedList);

int getLength(DoublyLinkedList);

void swapData(EnqItem *a, EnqItem *b);

EnqItem *getElement(DoublyLinkedList, int);

DoublyLinkedList copy(DoublyLinkedList, size_t);

void sort(DoublyLinkedList, int);

#define ITERATE(cur, list) for(EnqItem * cur = (list)->next; cur != (list); cur = cur->next)
#define ITERATE_REV(cur, list) for(EnqItem * cur = (list)->prev; cur != (list); cur = cur->prev)

#endif
