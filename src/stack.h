#pragma once

typedef struct stack_entry {
    char* data;
    struct stack_entry* next;
} stack_entry;

typedef struct stack_t {
    stack_entry* head;
    size_t stackSize;
} stack_t;

typedef char* string_t;

stack_t* create_stack(void);

void push(stack_t*, string_t);

string_t top(stack_t*);

string_t pop(stack_t*);

void clear(stack_t*);

void delete_stack(stack_t**);
