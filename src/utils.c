#include "utils.h"
#include <stdlib.h>

bool is_double(String str)
{
    for (int i = 0; i < str.size; i++) {
        if (!isdigit(At(str, i)) && At(str, i) != '-' && At(str, i) != '.')
            return false;
    }
    return true;
}

TokenArray NewTokenArray()
{
    TokenArray ta;
    ta.array_ = malloc(sizeof(String) * MAX_LENGTH);

    /* Calling String constructor */
    for (int i = 0; i < MAX_LENGTH; i++) {
        ta.array_[i] = NewString("");
    }

    ta.size = 0;
    return ta;
}

void PushBackToken(TokenArray* ta, String token)
{
    ta->array_[ta->size++] = token;
}

String TA_Pop(TokenArray* ta)
{
    return ta->array_[ta->size--];
}

void FreeTokenArray(TokenArray* ta)
{
    for (int i = 0; i < ta->size; i++) {
        FreeString(&ta->array_[i]);
    }

    free(ta->array_);
    ta->size = 0;
}
