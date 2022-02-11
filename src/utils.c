#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "utils.h"

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

void whitespace_cleaner(char* str)
{
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

bool is_double(char* str)
{
    if (strlen(str) == 1 && str[0] == '-')
        return false;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]) && str[i] != '-' && str[i] != '.')
            return false;
    }
    return true;
}

bool is_function(char* str)
{
    return str[0] == '$'; /* just for future 5th mark task*/
}

TokenArray to_rpn(TokenArray infix_expr)
{
    stack_t* stack = create_stack();
    TokenArray postfix_expr = {
        .array = calloc(MAX_LENGTH, sizeof postfix_expr),
        .size = 0
    };

    for (int i = 0; i < MAX_LENGTH; i++) {
        postfix_expr.array[i] = calloc(MAX_LENGTH, sizeof(char*));
    }

    int j = 0;

    for (int i = 0; i < infix_expr.size; i++) {
        if (is_double(infix_expr.array[i]) || is_function(infix_expr.array[i])) {
            strcpy(postfix_expr.array[j++], infix_expr.array[i]);
            continue;
        }
        if (is_operator(infix_expr.array[i][0])) {
            int priority = operations_priority(*top(stack), infix_expr.array[i][0]);
            bool left_associative = is_left_associative(infix_expr.array[i][0]);

            while (top(stack) != NULL && *top(stack) != '(' && (priority == 1 || (priority == 0 && left_associative))) {
                strcpy(postfix_expr.array[j++], pop(stack));
                priority = operations_priority(*top(stack), infix_expr.array[i][0]);
                left_associative = is_left_associative(infix_expr.array[i][0]);
            }
            push(stack, infix_expr.array[i]);
            continue;
        }
        if (infix_expr.array[i][0] == '(') {
            push(stack, "(");
            continue;
        }
        if (infix_expr.array[i][0] == ')') {
            char* tmp = calloc(MAX_LENGTH, sizeof *tmp);
            while (*strcpy(tmp, pop(stack)) != '(') {
                strcpy(postfix_expr.array[j++], tmp);
            }
            continue;
        }
    }

    while (top(stack) != NULL) {
        strcpy(postfix_expr.array[j++], pop(stack));
    }
    delete_stack(&stack);

    return postfix_expr;
}
