#include <stdio.h>
#include <stdbool.h>

const int MAX_STRING = 256;

/* Find next token starting at give index.
 *   str : string to read from
 *   start : starting index
 *   result : string to store token into
 * Returns index 1 after end of the token.
 */
int tokenise(char *str, int start, char *result);

/* True if one of the following whitespace characters:
 * (' ', '\n', '\t')
 * False otherwise.
 */
bool isWhitespace(char ch);

int main() {
    printf("Enter string to be tokenised:\n");
    char buffer[MAX_STRING];
    fgets(buffer, MAX_STRING, stdin);

    char result[MAX_STRING];
    int start;
    start = tokenise(buffer, 0, result);
    while ( start != -1 ) {
        printf("%s\n", result);
        start = tokenise(buffer, start, result);
    }
    if (result[0] != '\0') {
        printf("%s\n", result);
    }
    return 0;
}

int tokenise(char *str, int start, char *result)
{
    char ch = str[start];
    while (ch != '\0' && isWhitespace(ch))
    {
        start++;
        ch = str[start];
    }
    int i = 0;
    while (ch != '\0' && !isWhitespace(ch))
    {
        result[i] = ch;
        i++;
        ch = str[start + i];
    }
    result[i] = '\0';
    return ch == '\0' ? -1 : start + i;
}

bool isWhitespace(char ch)
{
    return ch == ' ' || ch == '\n' || ch == '\t';
}
