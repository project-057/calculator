#pragma once

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#include "variable.h"

#define MAX_LENGTH 256
#define MAX_VARS_AMOUNT 128

typedef struct {
    char** array;
    int size;
} TokenArray;

// static TokenArray split_to_tokens(char* expression);
//
// TokenArray to_rpn(TokenArray expression);

void whitespace_cleaner(char* string);

bool is_double(char* value);

// static char** split_to_tokens(char*);

bool is_double(char*);

// char** to_rpn(char**);

TokenArray variables_to_values(TokenArray tokens, Variable* vars_array, int var_size);
