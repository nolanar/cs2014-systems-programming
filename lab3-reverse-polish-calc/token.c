#include <ctype.h>
#include "token.h"

int tokenise(char *str, int start, char *result)
{
    char ch = str[start];
    while (ch != '\0' && isspace(ch))
    {
        start++;
        ch = str[start];
    }
    int i = 0;
    while (ch != '\0' && !isspace(ch))
    {
        result[i] = ch;
        i++;
        ch = str[start + i];
    }
    result[i] = '\0';
    return ch == '\0' ? -1 : start + i;
}
