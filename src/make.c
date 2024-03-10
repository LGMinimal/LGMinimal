#include <stdio.h>
#include "utils/types.h"
#include "modules/lexical.h"
#include "modules/parser.h"
#include "make.h"

#define DEBUG_MODE 1

assembly 
make(FILE *file) 
{
    memory_slc *tokens = lexer (file);
    #if DEBUG_MODE
        printf ("DEBUG MODE IS ACTIVE\n");
        printf ("LEXICAL PHASE OBTAINS: %d TOKENS\n", tokens->size);
        for( int i = 0; i < tokens->size; i++ )
            {
                printf ("Token<%d> {\n", i);
                Token tk = (Token)((Token *)tokens->items)[i];
                printf ("\tcontent: \"%s\"\n", tk.content);
                printf ("\ttype:    %d\n", tk.type);
                printf ("}\n");
            }
    #endif

    string code = parser (tokens);
    printf ("content: \n----------\n%s\n", code);
}