#ifndef STACKMACHINE_H
#define STACKMACHINE_H

#include "doublell.h"

typedef enum {
    NONE, LIST, INT, STRING
} arg_type;

typedef struct {
    void *data;
    arg_type type;
} stack_elem;

typedef struct {
    stack_elem *(*func0)();

    stack_elem *(*func1)(void *);

    stack_elem *(*func2)(void *, void *);

    int num_arguments;
    arg_type signature[2];
} function;

typedef struct {
    function *func;
    void *data;
    arg_type type;
} token;

function *lookup(char *);

DoublyLinkedList parseInput(char *);

stack_elem *execute(DoublyLinkedList, DoublyLinkedList);

#endif
