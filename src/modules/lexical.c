#include "../utils/types.h"
#include "../utils/error.h"
#include "../utils/output.h"
#include "lexical.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DEBUG_MODE 1
#define MAX_BUFFER_SIZE 128

#define UNDER_SCORE 0x5f  // ' _ '

char buffer[MAX_BUFFER_SIZE];
int bufferIndex = 0;
int col, line = 0;

char 
isSymbol(char c)
{
    return (!isalnum (c));
}

char 
isBinaryOperator(string buffer)
{
    if(
        strcmp (buffer, "<<") == 0 ||
        strcmp (buffer, ">>") == 0
    ) /*->*/ return 1;
    return 0;
}

char 
isOperator(string buffer)
{
    if( isBinaryOperator (buffer) ) 
        /*->*/ return 1;

    if(
        strcmp (buffer, "++") == 0 ||
        strcmp (buffer, "--") == 0 ||
        strcmp (buffer, "*=") == 0 ||
        strcmp (buffer, "/=") == 0 ||
        strcmp (buffer, "^=") == 0 ||
        strcmp (buffer, "-=") == 0 ||
        strcmp (buffer, "+=") == 0 ||
        strcmp (buffer, "/") == 0  ||
        strcmp (buffer, "*") == 0  ||
        strcmp (buffer, "=") == 0  ||
        strcmp (buffer, "+") == 0  ||
        strcmp (buffer, "-") == 0  ||
        strcmp (buffer, "^") == 0 
    ) /*->*/ return 1;
    return 0;
}

#define EQUALS(str) (strcmp (buffer, str) == 0)
#define KEYWORD_LENGTH 16
char
isKeyword(string buffer)
{
    char keywords[KEYWORD_LENGTH][9] = {
        "local",     "silky",  "function", 
        "FFunction", "FFSub",  "end",
        "FProc",     "sizeof", "typeof",
        "type",      "do",     "then",
        "extern",    "asm",    "volatile",
        "type"
    };

    for( short i = 0; i < KEYWORD_LENGTH; i++ )
        {
            if( EQUALS(keywords[i]) )
                /*->*/ return 1;
        }
    return 0;
}

#define TYPES_LENGTH 12
char
isType(string buffer)
{
    char types[TYPES_LENGTH][9] = {
        "void", "string", "i8",  "i16", "i32",   "i64",
        "u8",   "u16",    "u32", "u64", "float", "double"
    };

    for( short i = 0; i < TYPES_LENGTH; i++ )
        {
            if( EQUALS(types[i]) )
                /*->*/ return 1;
        }
    return 0;
}

char
isIdentifier (string buffer)
{
    if (isalpha (buffer[0]) || buffer[0] == UNDER_SCORE)
        {
            for (unsigned char i = 1; i < strlen (buffer); i++)
                {
                    if (!(isalnum (buffer[i]) || buffer[i] == UNDER_SCORE))
                        /*->*/ return 0;
                };
            return 1;
        }
    else
        /*->*/ return 0;
}

void 
lexicalError(memory_slc *tokens, int local[2])
{
    sdestroy (tokens);
    Output output = (Output) { newError () };
    string message = (string)malloc (sizeof(char) * 300);
    sprintf (message, "The symbol '%s' can't be parsed", buffer);
    output.errors.lexical (message, local[0], local[1]);
}

void
validate(memory_slc *tokens, char s)
{
    dynamic token = (Token *)malloc (sizeof (Token));

    char t = 0;
    if( s )
        {
            *(Token *)token = (Token) {
                .content =  "END TOKEN",
                .type = END,
                .parse = 0, 
                col, line
            };
            buffer[0] = 0;
        }
    else
    if( isKeyword (buffer) ) 
        {
            *(Token *)token = (Token) {
                .content =  strdup (buffer),
                .type = KEYWORD,
                .parse = 0, 
                col, line
            };
            buffer[0] = 0;
        }
    else
    if( isType (buffer) ) 
        {
            *(Token *)token = (Token) {
                .content =  strdup (buffer),
                .type = TYPEMENT,
                .parse = 0, 
                col, line
            };
            buffer[0] = 0;
        }
    else if( isIdentifier (buffer) )
        {
            *(Token *)token = (Token) {
                .content =  strdup (buffer),
                .type = IDENTIFIER,
                .parse = 0, 
                col, line
            };
            buffer[0] = '\0';
        }
    else if( isOperator (buffer) )
        {
            *(Token *)token = (Token) {
                .content =  strdup (buffer),
                .type = isBinaryOperator (buffer) ? BINARY_OPERATOR : OPERATOR,
                .parse = 0, 
                col, line
            };
            buffer[0] = 0;
        }
    else 
        { t = 1; }

    bufferIndex = 0;

    if(! t ) 
        /*->*/ spush (tokens, token);
    if( t ) 
        /*->*/ free(token);
}

memory_slc*
lexer(FILE *file)
{
    memory_slc *tokens = slloc (sizeof (Token));

    while(1)
        {
            col++;
            if( feof (file) )
                /*->*/ break;
            
            char c = getc (file);

            if( c == 10 || c == 32 )
                {
                    if( bufferIndex > 0 ) 
                        /*->*/ validate (tokens, 0);

                    if( c == 0xa )
                        {
                            line++;
                            col = 0;
                        }
                    continue;
                }
            
            if( 
                c == '{' || c == '}' ||
                c == '(' || c == ')' ||
                c == '[' || c == ']' 
            ) {
                if( bufferIndex > 0 ) 
                    /*->*/ validate (tokens, 0);

                buffer[0] = c;
                buffer[1] = 0;

                dynamic token = (Token *)malloc (sizeof (Token));
                *(Token *)token = (Token) {
                    .content =  strdup (buffer),
                    .type = BRACKET,
                    .parse = 0, 
                    col, line
                };
                spush (tokens, token);
                buffer[0]   = '\0';
                bufferIndex = 0;
                continue;
            }

            if( 
                c == ':' || c == ';' 
            ) {
                if( bufferIndex > 0 ) 
                    /*->*/ validate (tokens, 0);
                    
                buffer[0] = c;
                buffer[1] = 0;

                dynamic token = (Token *)malloc (sizeof (Token));
                *(Token *)token = (Token) {
                    .content =  strdup (buffer),
                    .type = c == ':' ? COLLON : SEMI,
                    .parse = 0, 
                    col, line
                };
                spush (tokens, token);
                buffer[0]   = '\0';
                bufferIndex = 0;
                continue;
            }
            
            if( isSymbol (c) )
                {
                    if( bufferIndex > 0 ) 
                        /*->*/ validate (tokens, 0);

                    buffer[bufferIndex++] = c;
                    buffer[bufferIndex] = 0;

                    char _c = getc (file);
                    if( _c == '=' || _c == c )
                        {
                            buffer[bufferIndex++] = _c;
                            buffer[bufferIndex] = 0;
                        }
                    else 
                        /*->*/ ungetc (_c, file);

                    validate (tokens, 0);
                    continue;
                }
            
            buffer[bufferIndex++] = c;
            buffer[bufferIndex] = 0;
        }

    validate(tokens, 1);

    return tokens;
}