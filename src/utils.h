#pragma once

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "variable.h"

#define MAX_LENGTH 256
#define MAX_VARS_AMOUNT 128

// static char** split_to_tokens(char*);
//
bool is_double(char*);
bool is_funciton(char*);
//
char** to_rpn(char**);
//
// char** variables_to_values(char**);
