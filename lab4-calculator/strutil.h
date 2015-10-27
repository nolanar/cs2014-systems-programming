/** String utilies
 */
#ifndef STRUTIL_H
#define STRUTIL_H

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

/** Returns:
 *  true        if str matches a finite double
 *  false       otherwise
 */
_Bool is_double(char *str);

/** Returns: double that matches str
 *
 *  Precondition: str must match a finite double
 */
double get_double(char *str);

#endif
