#pragma once

typedef struct stack_entry {
    char* data;
    struct stack_entry* next;
} stack_entry;

typedef struct Stack {
    stack_entry* head;
    int stackSize;
} Stack;

Stack* create_stack(void);

void push(Stack*, char* value);

char* top(Stack*);

char* pop(Stack*);

void clear(Stack*);

void delete_stack(Stack**);
