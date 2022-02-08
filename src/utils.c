#include "utils.h"

bool is_double(String str)
{
    for (int i = 0; i < str.size; i++) {
        if (!isdigit(At(str, i)) && At(str, i) != '-' && At(str, i) != '.')
            return false;
    }
    return true;
}
