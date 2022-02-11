#include "utils.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    static SplitMode sm = SM_NONE;
    char operators[] = "+-/*^()";

    if ((character <= 'Z' && character >= 'A') || (character <= 'z' && character >= 'a')) {
        *changed = sm != SM_WORD;
        sm = SM_WORD;
    } else if (character <= '9' && character >= '0') {
        *changed = sm != SM_VALUE;
        sm = SM_VALUE;
    } else if (in(operators, character)) {
        *changed = true;
        sm = SM_OPERATOR;
    } else {
        *changed = sm != SM_NONE;
        sm = SM_NONE;
    }
}

TokenArray split_to_tokens(char* infix_expr)
{
    whitespace_cleaner(infix_expr);

    int len = strlen(infix_expr);

    TokenArray stack = NewTokenArray();
    stack.size++;

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

void whitespace_cleaner(char* str)
{
    size_t j = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

bool is_double(char* str)
{
    for (size_t i = 0; *(str + i) != '\0'; i++) {
        if (!isdigit(str[i]) && str[i] != '-' && str[i] != '.')
            return false;
    }
    return true;
}

TokenArray NewTokenArray()
{
    TokenArray out = { .array = calloc(MAX_LENGTH, sizeof(char*)), .size = 0 };
    for (int i = 0; i < MAX_LENGTH; i++) {
        out.array[i] = calloc(MAX_TOKEN_LENGTH, sizeof(char));
    }

    return out;
}

void FreeTokenArray(TokenArray* ta)
{
    for (int i = 0; i < MAX_LENGTH; i++) {
        free(ta->array[i]);
    }
    free(ta->array);
    ta->size = 0;
}
