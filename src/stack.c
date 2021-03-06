#include <stdlib.h>
#include <string.h>

#include "stack.h"

Stack* create_stack(void)
{
    Stack* stack = malloc(sizeof *stack);
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

void push(Stack* stack, char* value)
{
    stack_entry* entry = malloc(sizeof *entry);
    if (entry) {
        entry->data = copy_string_t(value);
        entry->next = stack->head;
        stack->head = entry;
        stack->stackSize++;
    }
}

char* top(Stack* stack)
{
    if (stack && stack->head)
        return stack->head->data;
    else
        return NULL;
}

char* pop(Stack* stack)
{
    char* top_element = top(stack);
    if (stack->head != NULL) {
        stack->head = stack->head->next;
        stack->stackSize--;
    }
    return top_element;
}

void clear(Stack* stack)
{
    while (stack->head != NULL)
        pop(stack);
}

void delete_stack(Stack** stack)
{
    clear(*stack);
    free(*stack);
    *stack = NULL;
}
