#pragma once
#include "variable.h"

static char** split_to_tokens(char* infix_expr);
char** to_rpn(char** infix_expr);
char** variables_to_values(char** tokens);