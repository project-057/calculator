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

TokenArray create_token_array();
TokenArray to_rpn(TokenArray expression);
TokenArray variables_to_values(TokenArray tokens, Variable* vars_array, int var_size);
TokenArray split_to_tokens(char* infix_expr);

void whitespace_cleaner(char* string);
void free_token_array(TokenArray* ta);
void get_variables(char *str, Variable *variables);

bool is_function(char* str);
bool is_double(char* value);
