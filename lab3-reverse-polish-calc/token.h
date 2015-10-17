#ifndef TOKEN_H
#define TOKEN_H

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

#endif
