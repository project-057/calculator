#pragma once

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#include "string.h"
#include "variable.h"

#define MAX_LENGTH 256
#define MAX_VARS_AMOUNT 128

typedef struct {
    String* array_;
    int size;
} TokenArray;

TokenArray NewTokenArray();

void PushBackToken(TokenArray* ta, String token);

String TA_Pop(TokenArray* ta);

void FreeTokenArray(TokenArray* ta);

// static char** split_to_tokens(char*);
//
bool is_double(String value);
// char** to_rpn(char**);
//
// char** variables_to_values(char**);
