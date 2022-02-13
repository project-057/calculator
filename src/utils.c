#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "utils.h"

typedef enum {
    TT_NONE,
    TT_WORD,
    TT_OPERATOR,
    TT_VALUE
} TokenType;

static bool in(char* array, char value)
{
    int n = strlen(array);
    for (int i = 0; i < n; ++i) {
        if (array[i] == value)
            return true;
    }
    return false;
}

/* To reset statics inside put to the argument -1 or call reset_statics() function  */
static bool is_token_type_changed(char character, int index)
{
    static char previous_character = '\0';
    static TokenType token_type = TT_NONE;

    if (index == -1) {
        previous_character = '\0';
        token_type = TT_NONE;
    }

    TokenType previous = token_type;
    char operators[] = "+-/*^()";

    if (isalpha(character) || (previous == TT_WORD && isdigit(character))) {
        token_type = TT_WORD;
    } else if (isdigit(character) || character == '.') {
        token_type = TT_VALUE;
    } else if (in(operators, character)) {
        token_type = TT_OPERATOR;
        previous_character = character;
        return true;
    } else {
        token_type = TT_NONE;
    }

    previous_character = character;

    return token_type != previous;
}

static void reset_statics()
{
    is_token_type_changed('\0', -1);
}

TokenArray split_to_tokens(char* infix_expr)
{
    whitespace_cleaner(infix_expr);
    TokenArray stack = create_token_array();
    int len = strlen(infix_expr);
    int current_token_size = 0;
    bool changed = false;

    for (int i = 0; i < len; ++i) {
        if (is_token_type_changed(infix_expr[i], i) && current_token_size != 0) {
            stack.size++;
            current_token_size = 0;
        }

        stack.array[stack.size - 1][current_token_size++] = infix_expr[i];
    }

    /* Checking to unary minus */
    TokenArray out = create_token_array();
    bool is_unary_minus = false;

    for (int i = 0; i < stack.size; i++) {
        if (strcmp(stack.array[i], "-") == 0) {
            if (i == 0) {
                is_unary_minus = true;
            } else if (strcmp(stack.array[i - 1], "(") == 0) {
                for (int j = i + 1; j < stack.size; j++) {
                    if (strcmp(stack.array[i], "^") == 0) {
                        is_unary_minus = false;
                        break;
                    } else if (strcmp(stack.array[i], ")") == 0) {
                        is_unary_minus = true;
                        break;
                    } else if (j == stack.size - 1) {
                        is_unary_minus = true;
                    }
                }
            }
        }

        strcpy(out.array[out.size - 1], stack.array[i]);
        if (is_unary_minus) {
            strcat(out.array[out.size - 1], stack.array[i + 1]);
        }
        out.size++;
        i++;
    }

    free_token_array(&stack);
    return out;
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
    int len = strlen(str);
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

bool is_double(char* str)
{
    unsigned i = 0;
    unsigned length = strlen(str);
    int dec_count = 0;

    if (length == 0)
        return false;

    if (*str == '-') {
        if (length == 1)
            return false;
        i++;
    }

    if (str[i] == '.')
        return false;

    for (; i < length; i++) {
        if (str[i] == '.') {
            if (dec_count > 0 || !isdigit(str[i + 1]))
                return false;
            dec_count++;
        } else if (!isdigit(str[i]))
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
    Stack* stack = create_stack();
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
            int priority = -1;

            if (top(stack) != NULL)
                priority = operations_priority(*top(stack), first_char);

            bool left_associative = is_left_associative(first_char);

            while (top(stack) != NULL && *top(stack) != '(' && (priority == 1 || (priority == 0 && left_associative))) {
                strcpy(postfix_expr.array[j++], pop(stack));
                priority = operations_priority(*top(stack), first_char);
                printf("%c\n", first_char);
                printf("%d", priority);
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
            free(tmp);
        }
    }

    while (top(stack) != NULL) {
        strcpy(postfix_expr.array[j++], pop(stack));
    }
    delete_stack(&stack);

    return postfix_expr;
}
