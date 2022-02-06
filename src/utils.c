#include "utils.h"

bool is_double(char* str)
{
    for (size_t i = 0; *(str + i) != '\0'; i++) {
        if (!isdigit(str[i]) && str[i] != '-' && str[i] != '.')
            return false;
    }
    return true;
}
