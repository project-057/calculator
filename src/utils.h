#pragma once

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "variable.h"

#define MAX_LENGTH 256
#define MAX_VARS_AMOUNT 128

typedef struct {
    char** array;
    int size;
} TokenArray;

// static char** split_to_tokens(char*);
void whitespace_cleaner(char*);
//
bool is_double(char*);
// char** to_rpn(char**);
//
// char** variables_to_values(char**);
