#pragma once

#include "utils.h"

typedef struct {
    char* name;
    double value;
} Variable;

void init_variable(Variable* variables);
