#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

char** variables_to_values(char** tokens, Variable* vars_array, int token_size, int var_size)
{
    char** out = malloc(sizeof(**out) * token_size);
    for (size_t i = 0; i < token_size; i++) {
        out[i] = malloc(MAX_LENGTH);
        strcpy(out[i], tokens[i]);
    }
    for (size_t i = 0; i < token_size; i++) {
        if ((tokens[i][0] >= 'a' && tokens[i][0] <= 'z') || (tokens[i][0] >= 'A' && tokens[i][0] <= 'Z')) {
            for (size_t j = 0; j < var_size; j++) {
                if (strcmp(tokens[i], vars_array[j].name) == 0) {
                    sprintf(out[i], "%.9f", vars_array[j].value);
                    break;
                }
            }
        }
    }
    return out;
}