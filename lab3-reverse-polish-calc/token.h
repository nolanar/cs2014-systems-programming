#ifndef TOKEN_H
#define TOKEN_H

#include <stdbool.h>

/** Find next token starting at give index.
 *
 *  Parameters:
 *  *str : string to read from
 *  start : starting index
 *  *result : string to store token into
 *
 *  Return:
 *  index 1 after end of the token.
 */
int tokenise(char *str, int start, char *result);

/** Check if whitespace character.
 *
 *  Return:
 *  true : if ch in {' ', '\n', '\t'}
 *  false : otherwise
 */
bool isWhitespace(char ch);

#endif
