#include <math.h>
#include <stdio.h>

#include "stack.h"
#include "utils.h"

double eval(TokenArray rpn_expr)
{
    double result;
    stack_t* stack = create_stack();
    char* endptr; /* strtod stuff */

    // for (size_t i = 0; **(rpn_expr + i) != '\0'; i++) {
    for (int i = 0; i < rpn_expr.size; i++) {
        if (is_double(rpn_expr.array_[i])) { /* check if double */
            push(stack, rpn_expr.array_[i]);
        } else {
            double b = strtod(pop(stack).string_, &endptr);
            double a = strtod(pop(stack).string_, &endptr);
            double tmp = 0;

            switch (At(rpn_expr.array_[i],0)) {
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
            sprintf(tmp_result, "%lf", tmp); /* double to str */

            String tmp_string = NewString(tmp_result);

            push(stack, tmp_string);
        }
    }

    result = strtod(pop(stack).string_, &endptr);

    delete_stack(&stack);

    return result;
}
