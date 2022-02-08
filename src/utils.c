#include "utils.h"

void whitespace_cleaner(char* str)
{
    size_t j = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

bool is_double(char* str)
{
    for (size_t i = 0; *(str + i) != '\0'; i++) {
        if (!isdigit(str[i]) && str[i] != '-' && str[i] != '.')
            return false;
    }
    return true;
}

bool is_function(char* str)
{
    char functions[16][MAX_LENGTH];
    strcpy(functions[0], "cos");
    strcpy(functions[1], "sin");
    strcpy(functions[2], "tg");
    strcpy(functions[3], "log");
    strcpy(functions[4], "ln");
    strcpy(functions[5], "sqrt");
    strcpy(functions[6], "pow");
    strcpy(functions[7], "abs");
    strcpy(functions[8], "exp");
    strcpy(functions[9], "exp");
    strcpy(functions[10], "real");
    strcpy(functions[11], "imag");
    strcpy(functions[12], "mag");
    strcpy(functions[13], "phase");

    for (size_t i = 0; i < 14; i++) {
        if (!strcmp(functions[i], str))
            return true; /* strcmp(..., ...) == 0
                          * if strings are equal
                          */
    }

    return false;
}
