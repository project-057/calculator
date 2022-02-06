#include <math.h>
#include <stdio.h>

#include "stack.h"
#include "utils.h"

double eval(char** rpn_expr)
{
    double result;
    stack_t* stack = create_stack();
    char* endptr; /* strtod stuff */

    for (size_t i = 0; **(rpn_expr + i) != '\0'; i++) {
        if (is_double(*(rpn_expr + i))) { /* check if double */
            push(stack, *(rpn_expr + i));
        } else {
            double b = strtod(pop(stack), &endptr);
            double a = strtod(pop(stack), &endptr);
            double tmp = 0;

            switch (**(rpn_expr + i)) {
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
