#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eval.h"
#include "utils.h"
#include "variable.h"

int main(void)
{
    Variable variables[MAX_VARS_AMOUNT];
    char* expression = calloc(MAX_LENGTH, sizeof *expression);

    get_variables(expression, variables);

    TokenArray infix_expr = split_to_tokens(expression);

    int var_size = 0;
    while (variables[var_size++].name[0]) { }

    TokenArray new_infix_expr = variables_to_values(infix_expr, variables, var_size - 1);
    free_token_array(&infix_expr);

    TokenArray postfix_expr = to_rpn(new_infix_expr);
    free_token_array(&new_infix_expr);

    double result = eval(postfix_expr);
    printf("Result: \e[1;32m%f\033[0m\n", result);

    free_token_array(&postfix_expr);
    return 0;
}
