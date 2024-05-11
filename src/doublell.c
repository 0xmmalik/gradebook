/**
 * Doubly Linked List
 * by Manav Malik (2020)
 */

#include "doublell.h"
#include "gradebook.h"

EnqItem *initEnqItem(char *name, void *data) {
    EnqItem *e = malloc(sizeof(EnqItem));
    initEnqItemPointer(e, name, data);
    return e;
}

void initEnqItemPointer(EnqItem *e, char *name, void *data) {
    strcpy(e->name, name);
    e->data = data;
    e->next = e;
    e->prev = e;
}

DoublyLinkedList initDoublyLinkedList(char *name) {
    return initEnqItem(name, NULL);
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
    anchor->next->prev = e;
    anchor->next = e;
    e->prev = anchor;
    if (anchor->prev == anchor)
        anchor->prev = e;
}

void appendTail(EnqItem *e, DoublyLinkedList anchor) {
    e->prev = anchor->prev;
    anchor->prev->next = e;
    anchor->prev = e;
    e->next = anchor;
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

EnqItem *dequeueHead(DoublyLinkedList anchor) {
    return dequeue(anchor->next);
}

EnqItem *dequeueTail(DoublyLinkedList anchor) {
    return dequeue(anchor->prev);
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
    free(e);
}

DoublyLinkedList emptyList(DoublyLinkedList anchor) {
    while (!isEmpty(anchor))
        destroyItem(anchor->next);

    return anchor;
}

DoublyLinkedList destroyList(DoublyLinkedList anchor) {
    emptyList(anchor);
    free(anchor);

    return NULL;
}

int getLength(DoublyLinkedList anchor) {
    int len = 0;
    ITERATE(cur, anchor) {
        len++;
    }
    return len;
}

void swapData(EnqItem *a, EnqItem *b) {
    void *temp = a->data;
    a->data = b->data;
    b->data = temp;
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

void reverse(DoublyLinkedList anchor) {
    EnqItem *cur = anchor->prev;
    EnqItem *temp;
    while (cur != anchor) {
        temp = cur->next;
        cur->next = cur->prev;
        cur->prev = temp;
        cur = cur->next;
    }
}

DoublyLinkedList filter(DoublyLinkedList anchor, bool (*function)(EnqItem *), size_t sz) {
    DoublyLinkedList newlist = copy(anchor, sz);
    ITERATE(cur, newlist) {
        if (!function(cur))
            dequeue(cur);
    }
    return newlist;
}

DoublyLinkedList copy(DoublyLinkedList anchor, size_t sz) {
    DoublyLinkedList newlist = initDoublyLinkedList(anchor->name);
    ITERATE(cur, anchor) {
        void *copy_buf = malloc(sz);
        memcpy(copy_buf, cur->data, sz);
        appendTail(initEnqItem(cur->name, copy_buf), newlist);
    }
    return newlist;
}

void sort(DoublyLinkedList anchor, int num_elements) {
    for (int i = 0; i < num_elements - 1; i++)
        for (int j = num_elements - 2; j != i - 1; j--)
            if (((student *) getElement(anchor, j)->data)->grade < ((student *) getElement(anchor, j + 1)->data)->grade)
                swapData(getElement(anchor, j), getElement(anchor, j + 1));
}