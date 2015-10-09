#include <stdio.h>

const int MAX_STRING = 256;
const char DELIMITER = ' ';

/* Find next token starting at give index.
 *   str : string to read from
 *   start : starting index
 *   result : string to store token into
 * Returns index 1 after end of the token.
 */
int tokenise(char str[], int start, char result[]);

int main()
{
    char line[] = "Nothing but the rain   ";
    char result[256];
    int start;

    start = tokenise(line, 0, result);
    while ( start != -1 ) {
        printf("%s\n", result);
        start = tokenise(line, start, result);
    }
    printf("%s\n", result);    
    return 0;
}

int tokenise(char str[], int start, char result[])
{
    char ch = str[start];
    while (ch == DELIMITER && ch != '\0')
    {
        start++;
        ch = str[start];
    }
    int i = 0;
    while (ch != '\0' && ch != DELIMITER)
    {
        result[i] = ch;
        i++;
        ch = str[start + i];
    }
    result[i] = '\0';
    return ch == '\0' ? -1 : start + i;
}
