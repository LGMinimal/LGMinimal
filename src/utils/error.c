#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../modules/lexical.h"
#include "error.h"
#include "types.h"
#include "colors.h"

void lgcm(string msg);
void lexical(string msg, int col, int line);
void syntax(Token tk, ITER_ERROS error);

Error 
newError() 
{
    return (Error) { lgcm, lexical, syntax };
}

void 
showFinalMessage() 
{
    Colorizer drawer = (Colorizer) { newColorize() };
    drawer.out.setColor(Red);
    printf(" x ");
    drawer.out.setColor(Reset);
    printf("compilation terminated.\n");
    exit(0);
}

void 
lgcm(string msg) 
{
    Colorizer drawer = (Colorizer) { newColorize() };
    drawer.out.setColor (Purple);
    printf ("LGCM");
    drawer.out.setColor (Reset);
    printf (": ");
    drawer.out.setColor (Red);
    printf ("fatal error");
    drawer.out.setColor (Reset);
    printf (": %s\n", msg);
    showFinalMessage ();
}

void
lexical(string msg, int col, int line) 
{
    Colorizer drawer = (Colorizer) { newColorize() };
    drawer.out.setColor (Yellow);
    printf ("LEXICAL ERROR");
    drawer.out.setColor (Reset);
    printf (": [");
    drawer.out.setColor (Red);
    printf ("%d:%d", line + 1, col);
    drawer.out.setColor (Reset);
    printf ("] %s\n", msg);
    free (msg);
    showFinalMessage ();
}

void
syntax(Token tk, ITER_ERROS error) 
{
    Colorizer drawer = (Colorizer) { newColorize() };
    drawer.out.setColor (Red);
    printf ("SYNTAX ERROR");
    drawer.out.setColor (Reset);
    printf (": [");
    drawer.out.setColor (Green);
    printf ("%d:%d", tk.line + 1, tk.col);
    drawer.out.setColor (Reset);
    string msg;
    switch( error )
        {
            case EXPECTED_IDENTIFIER: 
                msg = "Expected Identifier";
                break;
            case NEED_COLLON_BEFORE_TYPE: 
                msg = "before the type, you need a: `:`";
                break;
            case EXPECTED_TYPE: 
                msg = "Expected Type";
                break;
            default:
                msg = "Unrecognized error";
                break;
        }
    printf ("] - %s\n", msg);
    free (msg);
    showFinalMessage ();
}