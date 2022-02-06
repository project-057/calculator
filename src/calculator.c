#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main(void)
{
    printf("Where is mistake?\n");
    char* string = "I have a string like + this";
    TokenArray splited = split_to_tokens(string);

    printf("Count splited: %d\n", splited.count);

    for (int i = 0; i < splited.count; ++i) {
        printf("%s\n",splited.token_array[i]);
        free(splited.token_array[i]);
    }

    free(splited.token_array);
}
