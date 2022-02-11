#pragma once
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#include "utils.h"

typedef struct {
    char* name;
    double value;
} Variable;

void init_variable(Variable* variables);
