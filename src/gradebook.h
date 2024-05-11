#ifndef GB_H
#define GB_H

#include "doublell.h"
#include "stackmachine.h"

typedef struct {
    char *lastname;
    char *firstname;

    float grade;
} student;

typedef struct {
    char *title;
    DoublyLinkedList data;
    int num_students;
} gb;

stack_elem *loadfile(void *);

//stack_elem *printfile(void *);
stack_elem *top(void *, void *);

stack_elem *all();

#endif
