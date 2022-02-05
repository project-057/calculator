#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "variable.h"

int main(void)
{
    char *line = calloc(256, sizeof *line),
         *expression = calloc(256, sizeof *line);

    Variable variables[128];
    for (size_t i = 0; i < 128; i++) {
        variables[i].name = calloc(128, sizeof(char*));
        variables[i].value = 0;
    }

    for (size_t counter = 0; fgets(line, 256, stdin); counter++) {
        if (counter == 0) {
            strcpy(expression, line);
        } else {
            char* token = strtok(line, " ");
            for (size_t i = 0; token; i++) {
                if (i == 0)
                    strcpy(variables[counter - 1].name, token);
                else if (i == 2) {
                    char* endptr;
                    variables[counter - 1].value = strtod(token, &endptr);
                }
                token = strtok(NULL, " ");
            }
        }
    }

    return 0;
}
