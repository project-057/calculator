#include <stdio.h>
#include <stdlib.h>

#include "eval.h"
#include "stack.h"
#include "utils.h"

double eval(TokenArray rpn_expr)
{
    double result;
    Stack* stack = create_stack();
    char* endptr; /* strtod stuff */

    for (int i = 0; i < rpn_expr.size; i++) {
        if (is_double(rpn_expr.array[i])) { /* check if double */
            push(stack, rpn_expr.array[i]);
        } else {
            double b = strtod(pop(stack), &endptr);
            double a = strtod(pop(stack), &endptr);
            double tmp = 0;

            switch (rpn_expr.array[i][0]) {
            case '+':
                tmp = a + b;
                break;
            case '-':
                tmp = a - b;
                break;
            case '*':
                tmp = a * b;
                break;
            case '/':
                tmp = a / b;
                break;
            case '^':
                tmp = pow(a, b);
                break;
            }
            char tmp_result[MAX_LENGTH];
            sprintf(tmp_result, "%lf", tmp);

            push(stack, tmp_result);
        }
    }
    result = strtod(pop(stack), &endptr);

    delete_stack(&stack);

    return result;
}
