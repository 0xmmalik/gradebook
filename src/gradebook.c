/**
 * Gradebook Handler
 * by Manav Malik (2020)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gradebook.h"
#include "stackmachine.h"

#define MAX_LINE 1000

gb *book = NULL;

int main(int argc, char **argv) {
    printf("Welcome to Gradebook Manager! By Manav Malik\n");
    printf("Enter your commands below:\n(e.g. LOAD relative/path/to/gradebook/file)\n\n");
    char command[MAX_LINE];
    //char word[100];
    //int wordlen;
    int running = 1;
    DoublyLinkedList stack = initDoublyLinkedList("stack");
    while (running) {
        printf(">>> ");
        fgets(command, MAX_LINE, stdin);
        stack_elem *se = execute(parseInput(command), stack);
        if (se->type == LIST) {
            printf("%s\n", ((DoublyLinkedList) se->data)->name);
            ITERATE(cur, ((DoublyLinkedList) se->data)) {
                student *s = cur->data;
                printf("%s, %s %.2f\n", s->lastname, s->firstname, s->grade);
            }
        }
        /*
        sscanf(command, "%s%n", word, &wordlen);
        if (!strcmp(word, "LOAD")) {
            sscanf(command + wordlen, "%s", word);
            if ((book = loadfile(word))) printf("File loaded: %s\n", word);
            else printf("Cannot load file: %s\n", word);
        } else if (!strcmp(word, "ALL")) {
            if (book) printfile(book);
            else printf("No file loaded.\n");
        } else if (!strcmp(word, "QUIT")) {
            running = 0;
        }*/
    }
    printf("\n\nThanks for using Gradebook!\n");
    return 0;
}

stack_elem *loadfile(void *path) {
    char *filepath = (char *) path;
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        printf("file not found\n");
        return NULL;
    }

    int lines = -1;

    char ch;

    while (!feof(fp)) {
        ch = fgetc(fp);
        if (ch == '\n') {
            lines++;
        }
    }

    rewind(fp);


    char first[30];
    char last[30];
    float grade;
    char title[MAX_LINE];
    fgets(title, MAX_LINE, fp);

    DoublyLinkedList gb_data = initDoublyLinkedList(title);

    int i;
    for (i = 0; fscanf(fp, "%s%s%f", last, first, &grade) && !feof(fp); i++) {
        // strip ',' off last name
        if (last[strlen(last) - 1] == ',')
            last[strlen(last) - 1] = 0;
        student *s = malloc(sizeof(student));
        s->lastname = malloc((strlen(last) + 1) * sizeof(char));
        strcpy(s->lastname, last);
        s->firstname = malloc((strlen(first) + 1) * sizeof(char));
        strcpy(s->firstname, first);
        s->grade = grade;
        appendTail(initEnqItem("student", s), gb_data);
    }

    if (i != lines) {
        printf("wrong format\ni=%d\n", i);
        return NULL;
    }

    book = malloc(sizeof(gb));
    book->title = malloc((strlen(title) + 1) * sizeof(char));
    strcpy(book->title, title);
    book->data = gb_data;
    book->num_students = lines;

    stack_elem *s = malloc(sizeof(stack_elem));
    s->data = gb_data;
    s->type = LIST;

    return s;
}


stack_elem *printfile(void *f) {
    stack_elem *file = (stack_elem *) f;
    printf("%s\n", ((DoublyLinkedList) (file->data))->name);
    printf("First\tLast\tGrade\n");
    for (EnqItem *cur = ((DoublyLinkedList) (file->data))->next;
         cur != ((DoublyLinkedList) (file->data)); cur = cur->next) {
        student *s = (student *) cur->data;
        printf("%s\t%s\t%f\n", s->firstname, s->lastname, s->grade);
    }
}

stack_elem *top(void *num, void *list) {
    int n = *(int *) num;
    DoublyLinkedList cpy = copy((DoublyLinkedList) list, sizeof(student));
    int len = getLength(cpy);
    sort(cpy, len);

    DoublyLinkedList cur = cpy->next;
    while (cur != cpy) {
        DoublyLinkedList next = cur->next;
        if (n-- <= 0)
            dequeue(cur);
        cur = next;
    }

    stack_elem *s = malloc(sizeof(stack_elem));
    s->data = cpy;
    s->type = LIST;

    return s;
}

stack_elem *all() {
    stack_elem *s = malloc(sizeof(stack_elem));
    s->data = book->data;
    s->type = LIST;
    return s;
}
