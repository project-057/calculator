#include <stdlib.h>

#include "utils.h"
#include "variable.h"
#include "utils.h"

void init_variable(Variable* variables)
{
    for (int i = 0; i < MAX_VARS_AMOUNT; i++) {
        variables[i].name = calloc(MAX_VARS_AMOUNT, sizeof(char*));
        variables[i].value = 0;
    }
}
