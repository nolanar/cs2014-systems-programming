#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include "strutil.h"

_Bool is_double(char *str)
{
    double value;
    char has_extra_chars = '\0';
    int has_double = sscanf(str, "%lf %c", &value, &has_extra_chars);
    return has_double && isfinite(value) && !has_extra_chars;
}

double get_double(char *str)
{
    assert(is_double(str));

    double value;
    sscanf(str, "%lf", &value);
    return value;
}
