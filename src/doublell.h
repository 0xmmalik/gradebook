/**
 * Doubly Linked List
 * by Manav Malik (2020)
 * Adapted by Manav Malik
 * for Stack Implementation (2020)
 */

#ifndef DOUBLELL_H
#define DOUBLELL_H

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct EnqItem {
    char name[20];
    int val;
    struct EnqItem * prev;
    struct EnqItem * next;
} EnqItem;

typedef EnqItem * DoublyLinkedList;

EnqItem * initEnqItem(char * name, int val);
void initEnqItemPointer(EnqItem * e, char * name, int val);
DoublyLinkedList initDoublyLinkedList(char * name);
bool isEnqueued(EnqItem *);
bool isEmpty(DoublyLinkedList);
void appendHead(EnqItem *, DoublyLinkedList);
void appendTail(EnqItem *, DoublyLinkedList);
void appendAfter(EnqItem *, EnqItem *);
void appendBefore(EnqItem *, EnqItem *);
EnqItem * dequeue(EnqItem *);
void dequeueHead(DoublyLinkedList);
void dequeueTail(DoublyLinkedList);
EnqItem * getHead(DoublyLinkedList);
EnqItem * getTail(DoublyLinkedList);
EnqItem * getPrevious(EnqItem *);
EnqItem * getNext(EnqItem *);
char * getName(DoublyLinkedList);
char * getItemName(EnqItem *);
void destroyItem(EnqItem *);
DoublyLinkedList emptyList(DoublyLinkedList);
DoublyLinkedList destroyList(DoublyLinkedList);
int getLength(DoublyLinkedList);
void swapVals(EnqItem *a, EnqItem *b);
EnqItem *getElement(DoublyLinkedList, int);

#endif
