#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gradebook.h"

#define MAX_LINE 1000

int main(int argc, char ** argv) {
	printf("Welcome to Gradebook Manager! By Manav Malik\n");
	printf("Enter your commands below:\n(e.g. LOAD relative/path/to/gradebook/file)\n\n");
	char command[MAX_LINE];
	char word[100];
	int wordlen;
	int running = 1;
	gb *book = NULL;
	DoublyLinkedList stack = initDoublyLinkedList("stack");
	while (running) {
		printf(">>> ");
		fgets(command, MAX_LINE, stdin);
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
		}
		//printf(function(command));
	}
	printf("\n\nThanks for using Gradebook!\n");
	return 0;
}

gb *loadfile(char * filepath) {
	FILE *fp = fopen(filepath, "r");
	if(fp == NULL) {printf("file not found\n"); return NULL;}

	int lines = -1;

	char ch;

	while(!feof(fp)) {
  		ch = fgetc(fp);
  		if(ch == '\n') {
  			lines++;
  		}
	}

	rewind(fp);

	DoublyLinkedList gb_data = initDoublyLinkedList("gb_data");

	char first[30];
	char last[30];
	float grade;
	char title[MAX_LINE];
	fgets(title, MAX_LINE, fp);
	int i;
	for(i = 0; fscanf(fp, "%s%s%f", last, first, &grade) && !feof(fp); i++) {
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

	if (i != lines) {printf("wrong format\ni=%d\n", i); return NULL;}

	gb *g = malloc(sizeof(gb));
	g->title = malloc((strlen(title) + 1) * sizeof(char));
	strcpy(g->title, title);
	g->data = gb_data;
	g->num_students = lines;

	return g;
}


void printfile(gb *file) {
	printf("%s\n", file->title);
	printf("First\tLast\tGrade\n");
	for (EnqItem * cur = file->data->next; cur != file->data; cur = cur->next) {
		student * s = (student *)cur->data;
		printf("%s\t%s\t%f\n", s->firstname, s->lastname, s->grade);
	}
}
