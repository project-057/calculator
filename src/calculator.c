#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "variable.h"

static void whitespace_cleaner(char* str)
{
    size_t j = 0;

    for (size_t i = 0; str[i]; i++) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
    }

    str[j] = '\0';
}

static void init_variable(Variable variables[128])
{
    for (size_t i = 0; i < 128; i++) {
        variables[i].name = calloc(128, sizeof(char*));
        variables[i].value = 0;
    }
}

int main(void)
{
    char *line = calloc(256, sizeof *line),
         *expression = calloc(256, sizeof *line);

    Variable variables[128];
    init_variable(variables);

    for (size_t counter = 0; fgets(line, 256, stdin); counter++) {
        if (counter == 0) {
            strcpy(expression, line);
        } else {
            whitespace_cleaner(line);
            char* token = strtok(line, "=");

            for (size_t i = 0; token; token = strtok(NULL, " ")) {
                if (i++) {
                    char* endptr;
                    variables[counter - 1].value = strtod(token, &endptr);
                } else {
                    strcpy(variables[counter - 1].name, token);
                }
            }
        }
    }

    return 0;
}
