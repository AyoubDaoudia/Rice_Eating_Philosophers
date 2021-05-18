#ifndef mylib_h
#define mylib_h

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Stack structure
typedef struct stack{
    int data;
    struct stack* next;
} stack;

// Singly linked list structure
typedef struct s_linked{
    int data;
    struct s_linked *next;
} s_linked;

//Queue structure
typedef struct queue{
    int data;
    struct queue* next;
} queue;

//Double linked list structure
typedef struct d_linked{
    int data;
    struct d_linked* start;
    struct d_linked* end;
} d_linked;

#endif

// Stack Prototypes

stack* new_stack(int);
bool is_empty(stack*);
void push(stack** , int);
void pop(stack**);


// Singly linked list Prototypes
s_linked* create_node(int);
void add_node(s_linked**, int);
s_linked* array_to_list(int*, int);
void print_list(s_linked*);
void remove_node(s_linked**, int);

// Queue Prototypes
queue* new_queue(int);
bool q_is_empty(queue **);
void q_pop(queue **);
void q_push(queue**,int);

// Double linked list Prototypes
d_linked* create_list(int);
void show_first(d_linked *);
void show_last(d_linked *);