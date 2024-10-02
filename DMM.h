#ifndef DMM_H
#define DMM_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int minutes;
    int seconds;
} Duration;

typedef struct {
    char artist[100];
    char album[100];
    char title[100];
    char genre[100];
    Duration duration;
    int playnum;
    int rating;
} record;

typedef struct node {
    record data;
    struct node* next;
    struct node* prev;
} node;


void menu();
void load(const char* filename, node** head);
void store(const char* filename, node* head);
void display(node* head);
void insert(node** head);
void delete(node** head);
void sort(node** head);
void edit(node* head);
void rate(node* head);
void play(node* head);
void shuffle(node* head);
void freeList(node* head);
void exitProgram(node* head);

#endif 
