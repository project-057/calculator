#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

TokenArray variables_to_values(TokenArray tokens, Variable* vars_array, int var_size)
{
    TokenArray result = create_token_array();
    for (int i = 0; i < tokens.size; i++) {
        strcpy(result.array[i], tokens.array[i]);
    }

    for (int i = 0; i < tokens.size; i++) {
        if (isalpha(tokens.array[i][0])) {
            for (int j = 0; j < var_size; j++) {
                if (strcmp(tokens.array[i], vars_array[j].name) == 0) {
                    sprintf(result.array[i], "%f", vars_array[j].value);
                    break;
                }
            }
        }
    }

    return result;
}
