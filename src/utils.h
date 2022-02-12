#pragma once
#include <ctype.h>
#include <stdbool.h>

#include "variable.h"

#define MAX_LENGTH 256
#define MAX_VARS_AMOUNT 128
#define MAX_TOKEN_LENGTH 50

typedef struct {
    char** array;
    int size;
} TokenArray;

bool is_double(char*);
bool is_function(char*);

TokenArray to_rpn(TokenArray expression);

TokenArray variables_to_values(TokenArray tokens, Variable* vars_array, int var_size);

TokenArray create_token_array();

void free_token_array(TokenArray* ta);

TokenArray split_to_tokens(char* infix_expr);

void whitespace_cleaner(char* string);

bool is_double(char* value);
