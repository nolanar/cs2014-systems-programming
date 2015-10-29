#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "postfix.h"

const int MAX_STRING = 256;

const char HELP_TEXT[] =
    "\nEnter an expression to be evaluated.\n"
    "Operators:\n"
    "  +  Add\n"
    "  -  Subtract\n"
    "  *  Multiply\n"
    "  /  Divide\n"
    "Use parens to control order of operation.\n"
    "Enter 'quit' to exit program.\n\n";

int main()
{
    printf(HELP_TEXT);
    char infix[MAX_STRING];
    do {
        printf(">>> ");
        fgets(infix, MAX_STRING, stdin);
        /* Exit input loop if user enters 'quit' */
        if (strcmp(infix, "quit\n") == 0) {
            break;
        }

        char postfix[2 * MAX_STRING];
        infix_to_postfix(infix, postfix);

        double result = evaluate(postfix);

        if (isnan(result)) {
            printf("ERROR: expression is not well formed\n");
        } else {
            printf("postfix: %s\n", postfix);
            if (!isfinite(result)) {
                printf("division by 0 occured\n");
            }
            else {
                printf("%lg\n", result);
            }
        }
    } while (1);

    return 0;
}
