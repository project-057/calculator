#include <stdio.h>

#include "eval.h"
#include "utils.h"
#include "variable.h"

const char* variable_request = "Write a variable with its value \033[0;33m(or press <C-d> to stop)\
                              \n\033[0;31muse format -> 'x = 1.0' :\033[0m";

int main(void)
{
    char* line = calloc(MAX_LENGTH, sizeof *line);
    char* expression = calloc(MAX_LENGTH, sizeof *line);

    Variable variables[MAX_VARS_AMOUNT];
    init_variable(variables);

    puts("Write a math expression: ");
    fgets(expression, MAX_LENGTH, stdin);

    puts(variable_request);

    /* TODO: Using get_variable instead */
    for (size_t counter = 0; fgets(line, MAX_LENGTH, stdin); counter++) {
        puts(variable_request);
        whitespace_cleaner(line);

        char* token = strtok(line, "="); /* divide line by '=' symbol */
        char* endptr; /* for strtod stuff */

        strcpy(variables[counter].name, token); /* add variable name to the Varibale structure */

        token = strtok(NULL, " "); /* go to the next part of our devided string */

        variables[counter].value = strtod(token, &endptr); /* add value to the Variable structure */
    }

    /* Use TokenArray instead char** */
    // char **tokens = calloc(MAX_LENGTH, sizeof(char*));
    // for(size_t i = 0 ; i < 11 ; i++)
    // {
    //    *(tokens + i) = calloc(1, sizeof(char) * MAX_LENGTH);
    // }

    // tokens = to_rpn(&expression);

    // tokens = variable_to_values(tokens);

    return 0;
}
