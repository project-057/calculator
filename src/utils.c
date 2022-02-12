#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "utils.h"
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    SM_NONE,
    SM_WORD,
    SM_OPERATOR,
    SM_VALUE
} SplitMode;

static bool in(char* array, char value)
{
    int n = strlen(array);
    for (int i = 0; i < n; ++i) {
        if (array[i] == value)
            return true;
    }
    return false;
}

static void parse_character(char character, bool* changed)
{
    static SplitMode split_mode = SM_NONE;
    char operators[] = "+-/*^()";

    if (isalpha(character)) {
        *changed = split_mode != SM_WORD;
        split_mode = SM_WORD;
    } else if (isdigit(character) || character == '.') {
        *changed = split_mode != SM_VALUE;
        split_mode = SM_VALUE;
    } else if (in(operators, character)) {
        *changed = true;
        split_mode = SM_OPERATOR;
    } else {
        *changed = split_mode != SM_NONE;
        split_mode = SM_NONE;
    }
}

TokenArray split_to_tokens(char* infix_expr)
{
    whitespace_cleaner(infix_expr);

    int len = strlen(infix_expr);

    TokenArray stack = create_token_array();

    int current_token_size = 0;
    bool changed = false;

    for (int i = 0; i < len; ++i) {
        parse_character(infix_expr[i], &changed);
        if (changed && current_token_size != 0) {
            stack.size++;
            current_token_size = 0;
        }
        assert(current_token_size + 1 < MAX_TOKEN_LENGTH);

        stack.array[stack.size - 1][current_token_size++] = infix_expr[i];
    }

    return stack;
}

static bool is_operator(char character)
{
    return (character == '+' || character == '-' || character == '*' || character == '/' || character == '^');
}

static bool is_left_associative(char character)
{
    return character != '^';
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

TokenArray create_token_array()
{
    TokenArray out = {
        .array = calloc(MAX_LENGTH, sizeof(char*)),
        .size = 1
    };

    for (int i = 0; i < MAX_LENGTH; i++) {
        out.array[i] = calloc(MAX_TOKEN_LENGTH, sizeof(char));
    }

    return out;
}

void free_token_array(TokenArray* ta)
{
    for (int i = 0; i < MAX_LENGTH; i++) {
        free(ta->array[i]);
    }
    free(ta->array);
    ta->size = 0;
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
        char first_char = infix_expr.array[i][0];

        if (is_double(infix_expr.array[i]) || is_function(infix_expr.array[i])) {
            strcpy(postfix_expr.array[j++], infix_expr.array[i]);
        } else if (is_operator(first_char)) {
            int priority = operations_priority(*top(stack), first_char);
            bool left_associative = is_left_associative(first_char);

            while (top(stack) != NULL && *top(stack) != '(' && (priority == 1 || (priority == 0 && left_associative))) {
                strcpy(postfix_expr.array[j++], pop(stack));
                priority = operations_priority(*top(stack), first_char);
                left_associative = is_left_associative(first_char);
            }
            push(stack, infix_expr.array[i]);
        } else if (first_char == '(') {
            push(stack, "(");
        } else if (first_char == ')') {
            char* tmp = calloc(MAX_LENGTH, sizeof *tmp);
            while (*strcpy(tmp, pop(stack)) != '(') {
                strcpy(postfix_expr.array[j++], tmp);
            }
        }
    }

    while (top(stack) != NULL) {
        strcpy(postfix_expr.array[j++], pop(stack));
    }
    delete_stack(&stack);

    return postfix_expr;
}
