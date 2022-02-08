#include "string.h"
#include <stdlib.h>
#include <string.h>

typedef struct stack_entry {
    String data;
    struct stack_entry* next;
} stack_entry;

typedef struct stack_t {
    stack_entry* head;
    size_t stackSize;
} stack_t;

stack_t* create_stack(void);

void push(stack_t* stack, String str);

String top(stack_t*);

String pop(stack_t*);

void clear(stack_t*);

void delete_stack(stack_t**);
