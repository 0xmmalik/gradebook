#ifndef GB_H
#define GB_H

#include "doublell.h"

typedef struct student {
	char * lastname;
	char * firstname;

	float grade;
} student;

typedef struct gb_file {
	char *title;
	DoublyLinkedList data;
	int num_students;
} gb;

gb *loadfile(char *);
void printfile(gb *);

#endif
