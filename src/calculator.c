#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main(void)
{
    char* string = "I have a string like + this";
    fputs("Where is mistake?", stdin);
    TokenArray splited = split_to_tokens(string);

    fprintf(stdin, "Count splited: %d\n", splited.count);

    for (int i = 0; i < splited.count; ++i) {
        fputs(splited.token_array[i], stdin);
        free(splited.token_array[i]);
    }

    free(splited.token_array);
}
