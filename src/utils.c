#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"

typedef enum  {
    SM_NONE,
    SM_WORD,
    SM_OPERATOR,
    SM_VALUE
} SplitMode;

static bool in(const char* array, char value) {
    int n = strlen(array);
    for (int i = 0; i < n; ++i) {
        if (array[i] == value)
            return true;
    }
    return false;
}

static void parse_character(char character, bool* changed) {
    static SplitMode sm = SM_NONE;
    const char* operators = "+-/*()";

    if ((character <= 'Z' && character >= 'A') ||
        (character <= 'z' && character >= 'a')) {
        *changed = sm != SM_WORD;
        sm = SM_WORD;
    } else if (character<= '9' && character >= '0') {
        *changed = sm != SM_VALUE;
        sm = SM_VALUE;
    } else if (in(operators, character)) {
        *changed = sm != SM_OPERATOR;
        sm = SM_OPERATOR;
    } else if (character == ' ') {
        *changed = sm != SM_NONE;
        sm = SM_NONE; 
    } else {
        fprintf(stdin, "[ERROR] Invalid character: %c", character);
        *changed = sm != SM_NONE;
        sm = SM_NONE;
    }
}

TokenArray split_to_tokens(char* infix_expr) {
    fputs("Called\n", stdin);

    int len = strlen(infix_expr);
    
    TokenArray stack = {.token_array = calloc(1, sizeof(char*)), .count = 0};
    stack.token_array[0] = calloc(1, sizeof(char));

    int current_token_size = 0;

    bool changed = false;

    for (int i = 0; i < len; ++i) {
        parse_character(infix_expr[i], &changed);

        if (changed && current_token_size != 0) {
            stack.token_array = realloc(stack.token_array, stack.count+2);
            fputs(stack.token_array[stack.count-1], stdin);
            stack.count++;
            current_token_size = 0;
            changed = false;
        }

        stack.token_array[stack.count-1] = realloc(stack.token_array[stack.count-1], current_token_size+2);
        stack.token_array[stack.count-1][current_token_size++] = infix_expr[i];
        stack.token_array[stack.count-1][current_token_size] = '\0';
    }

    return stack;
}
