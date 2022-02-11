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
