#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../utils/output.h"
#include "../../utils/error.h"
#include "../../utils/types.h"
#include "../lexical.h"
#include "../parser.h"

unsigned int IIndex = 0;

#define Eql(str, str2) (strcmp (str, str2) == 0)
#define GetTk() (Token)((Token *)tokens->items)[IIndex++];

#define GetID()                                                  \
    Token var_name = GetTk ();                                    \
    if( var_name.type != IDENTIFIER )                              \
        /*->*/ prompt.errors.syntax(var_name, EXPECTED_IDENTIFIER); \

#define GetType(need_collon)                                               \
    if( need_collon )                                                       \
        {                                                                    \
            Token collon = GetTk ();                                          \
            if( collon.type != COLLON )                                        \
                /*->*/ prompt.errors.syntax(var_name, NEED_COLLON_BEFORE_TYPE); \
        }                                                                        \
    Token typement = GetTk ();                                                    \
    if( typement.type != TYPEMENT )                                                \
        /*->*/ prompt.errors.syntax(var_name, EXPECTED_TYPE);                       \

void
parseSyntax (memory_slc *tokens, memory_slc *pTree) 
{

    Output prompt = (Output) { newError () };

    while( 1 )
        {
            Token tk = GetTk ();

            if( tk.type == END )
                /*->*/ break;

            printf ("content: %s\n", tk.content);

            if( Eql (tk.content, "local") || Eql (tk.content, "silky") )
                {
                    char mutable   = Eql (tk.content, "silky");
                    GetID ();
                    GetType (1);
                }
        }

    sdestroy(tokens);

}