/** String utilies
 */
#ifndef STRUTIL_H
#define STRUTIL_H

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
