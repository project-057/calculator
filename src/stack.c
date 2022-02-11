#include <stdlib.h>
#include <string.h>

#include "stack.h"

stack_t* create_stack(void)
{
    stack_t* stack = malloc(sizeof *stack);
    if (stack) {
        stack->head = NULL;
        stack->stackSize = 0;
    }
    return stack;
}

char* copy_string_t(const char* str)
{
    char* tmp = malloc(strlen(str) + 1);
    if (tmp)
        strcpy(tmp, str);
    return tmp;
}

void push(stack_t* stack, char* value)
{
    stack_entry* entry = malloc(sizeof *entry);
    if (entry) {
        entry->data = copy_string_t(value);
        entry->next = stack->head;
        stack->head = entry;
        stack->stackSize++;
    }
}

char* top(stack_t* stack)
{
    if (stack && stack->head)
        return stack->head->data;
    else
        return NULL;
}

char* pop(stack_t* stack)
{
    char* top_element = top(stack);
    if (stack->head != NULL) {
        stack->head = stack->head->next;
        stack->stackSize--;
    }
    return top_element;
}

void clear(stack_t* stack)
{
    while (stack->head != NULL)
        pop(stack);
}

void delete_stack(stack_t** stack)
{
    clear(*stack);
    free(*stack);
    *stack = NULL;
}
