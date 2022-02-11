#pragma once

#include <stdbool.h>

#include "variable.h"

#define MAX_LENGTH 256
#define MAX_VARS_AMOUNT 128

typedef struct {
    char** array;
    int size;
} TokenArray;

// static TokenArray split_to_tokens(char* expression);
//
bool is_double(char*);
bool is_function(char*);
//
TokenArray to_rpn(TokenArray expression);
// char** to_rpn(char**);
//
// TokenArray variables_to_values(TokenArray expression);

void whitespace_cleaner(char* string);

bool is_double(char* value);
