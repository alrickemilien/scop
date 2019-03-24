/*
** Debug function used to print tokens
*/

#include "scop.h"

void print_token(const t_token *tokens)
{
    size_t i;

    i = 0;
    while (tokens[i].cursor) {
        printf("%s\n", tokens[i].cursor);
        i++;
    }
}