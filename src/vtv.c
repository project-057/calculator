#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

TokenArray variables_to_values(TokenArray tokens, Variable* vars_array, int var_size)
{
    char** out1 = (char**)malloc(sizeof(char*) * tokens.size);
    for (int i = 0; i < tokens.size; i++) {
        out1[i] = (char*)malloc(256);
        strcpy(out1[i], tokens.array[i]);
    }

    for (int i = 0; i < tokens.size; i++) {
        if ((tokens.array[i][0] >= 'a' && tokens.array[i][0] <= 'z') || (tokens.array[i][0] >= 'A' && tokens.array[i][0] <= 'Z')) {
            for (int j = 0; j < var_size; j++) {
                if (strcmp(tokens.array[i], vars_array[j].name) == 0) {
                    sprintf(out1[i], "%f", vars_array[j].value);
                    break;
                }
            }
        }
    }

    TokenArray result = {
        .array = out1,
        .size = tokens.size
    };
    return result;
}
