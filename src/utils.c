#include "utils.h"
#include "stack.h"

bool is_double(char* str)
{
    for (size_t i = 0; *(str + i) != '\0'; i++) {
        if (!isdigit(str[i]) && str[i] != '-' && str[i] != '.')
            return false;
    }
    return true;
}

static bool is_binary(char character)
{
    return (character == '+' || character == '-' || character == '*' || character == '/' || character == '^');
}

static int operations_priority(char first_opr, char second_opr)
{
    if (first_opr == second_opr)
        return 0; /* have the same priority */
    if (second_opr == '^' || (second_opr == '*' || second_opr == '/') && (first_opr == '-' || first_opr == '+'))
        return 2; /* second operand has the higher priority */
    return 1; /* else first_opr has the higher priority */
}

char** to_rpn(char** infix_expr)
{
    stack_t* stack = create_stack();
    char** postfix_expr = calloc(MAX_LENGTH, sizeof **postfix_expr);
    for (size_t i = 0; i < MAX_LENGTH; i++) {
        *(postfix_expr + i) = calloc(MAX_LENGTH, sizeof *postfix_expr);
    }

    size_t j = 0;

    for (size_t i = 0; **(infix_expr + i) != '\0'; i++) {
        if (is_double(*(infix_expr + i))) {
            strcpy(*(postfix_expr + j++), *(infix_expr + i));
            continue;
        }
        if (is_binary(**(infix_expr + i))) {
            char* tmp = calloc(MAX_LENGTH, sizeof *tmp);
            while (operations_priority(*strcpy(tmp, *(infix_expr + i)), *top(stack)) != 1) {
                strcpy(*(postfix_expr + j++), pop(stack));
            }
            push(stack, *(infix_expr + i));
            continue;
        }
        if (**(infix_expr + i) == '(') {
            push(stack, *(infix_expr + i));
            continue;
        }
        if (**(infix_expr + i) == ')') {
            char* tmp = calloc(MAX_LENGTH, sizeof *tmp);
            while (*strcpy(tmp, pop(stack)) != '(') {
                strcpy(*(postfix_expr + j++), tmp);
            }
            continue;
        }
    }

    while (top(stack) != NULL) {
        strcpy(*(postfix_expr + j++), pop(stack));
    }

    return postfix_expr;
}
