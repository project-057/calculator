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

void push(stack_t* stack, String value)
{
    stack_entry* entry = malloc(sizeof *entry);
    if (entry) {
        StringCopy(value, &entry->data);
        entry->next = stack->head;
        stack->head = entry;
        stack->stackSize++;
    }
}

String top(stack_t* stack)
{
    if (stack && stack->head)
        return NewString(&stack->head->data);
    // else
    //     return NewString("");
}

String pop(stack_t* stack)
{
    String top_element = top(stack);
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
