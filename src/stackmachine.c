/**
 * stackmachine.c
 * by Manav Malik (2020)
 */

#include "stackmachine.h"
#include "gradebook.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>

extern gb *book;

function *lookup(char *name) {
    function *f = malloc(sizeof(function));
    if (!strcmp(name, "LOAD")) {
        f->func0 = NULL;
        f->func1 = &loadfile;
        f->func2 = NULL;
        f->num_arguments = 1;
        f->signature[0] = STRING;
        f->signature[1] = NONE;
    } else if (!strcmp(name, "ALL")) {
        f->func0 = &all;
        f->func1 = NULL;
        f->func2 = NULL;
        f->num_arguments = 0;
        f->signature[0] = NONE;
        f->signature[1] = NONE;
    } else if (!strcmp(name, "TOP")) {
        f->func0 = NULL;
        f->func1 = NULL;
        f->func2 = &top;
        f->num_arguments = 2;
        f->signature[0] = INT;
        f->signature[1] = LIST;
    } else {
        free(f);
        f = NULL;
    }
    return f;
}

DoublyLinkedList parseInput(char *line) {
    line[strlen(line) - 1] = '\0';
    DoublyLinkedList tokens = initDoublyLinkedList("tokens");
    char *split_line;
    split_line = strtok(line, " ");
    while (split_line != NULL) {
        token *t = malloc(sizeof(token));
        int num;
        if ((num = atoi(split_line))) {
            int *data = malloc(sizeof(int));
            *data = num;
            t->data = data;
            t->type = INT;
            t->func = NULL;
        } else if ((t->func = lookup(split_line))) {
            t->data = NULL;
            t->type = NONE;
        } else {
            t->data = split_line;
            t->type = STRING;
            t->func = NULL;
        }
        appendHead(initEnqItem("token", t), tokens);
        split_line = strtok(NULL, " ");
    }

    return tokens;
}


stack_elem *execute(DoublyLinkedList tokens, DoublyLinkedList stack) {
    ITERATE(t, tokens) {
        stack_elem *s = malloc(sizeof(stack_elem));
        token *tok = (token *) (t->data);
        if (tok->data) {
            s->data = tok->data;
            s->type = tok->type;
        } else if (tok->func->func0) {
            s = tok->func->func0();
        } else if (tok->func->func1) {
            function *f = tok->func;
            stack_elem *arg = (stack_elem *) (dequeueHead(stack)->data);
            if (!(arg->type == f->signature[0])) {
                printf("ERROR: incorrect argument provided to function!");
                continue;
            }
            s = f->func1(arg->data);
        } else if (tok->func->func2) {
            function *f = tok->func;
            stack_elem *arg1 = (stack_elem *) (dequeueHead(stack)->data);
            stack_elem *arg2 = (stack_elem *) (dequeueHead(stack)->data);
            if (!((arg1->type == f->signature[0]) && (arg2->type == f->signature[1]))) {
                printf("ERROR: incorrect arguments provided to function!");
                continue;
            }
            s = f->func2(arg1->data, arg2->data);
        }
        appendHead(initEnqItem("stack item", s), stack);
    }

    return (stack_elem *) dequeueHead(stack)->data;
}
