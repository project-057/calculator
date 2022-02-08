#include "utils.h"
#include "stack.h"

static bool is_operator(char character)
{
    return (character == '+' || character == '-' || character == '*' || character == '/' || character == '^');
}

static bool is_left_associative(char character)
{
    return character == '^' ? false : true;
}

static int operations_priority(char first_opr, char second_opr)
{
    if (first_opr == second_opr)
        return 0; /* have the same priority */
    if (second_opr == '^' || ((second_opr == '*' || second_opr == '/') && (first_opr == '-' || first_opr == '+')))
        return 2; /* second operand has the higher priority */
    return 1; /* else first_opr has the higher priority */
}

bool is_double(char* str)
{
    if (strlen(str) == 1 && str[0] == '-')
        return false;
    for (size_t i = 0; *(str + i) != '\0'; i++) {
        if (!isdigit(str[i]) && str[i] != '-' && str[i] != '.')
            return false;
    }
    return true;
}

bool is_function(char* str)
{
    return str[0] == '$'; /* just for future 5th mark task*/
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
        if (is_double(*(infix_expr + i)) || is_function(*(infix_expr + i))) {
            strcpy(*(postfix_expr + j++), *(infix_expr + i));
            continue;
        }
        if (is_operator(**(infix_expr + i))) {
            int priority = operations_priority(*top(stack), **(infix_expr + i));
            bool left_associative = is_left_associative(**(infix_expr + i));
            for (;
                 top(stack) != NULL && *top(stack) != '(' && (priority == 1 || (priority == 0 && left_associative));
                 priority = operations_priority(*top(stack), **(infix_expr + i)),
                 left_associative = is_left_associative(**(infix_expr + i))) {
                strcpy(*(postfix_expr + j++), pop(stack));
            }
            push(stack, *(infix_expr + i));
            continue;
        }
        if (**(infix_expr + i) == '(') {
            push(stack, "(");
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
    delete_stack(&stack);

    return postfix_expr;
}
