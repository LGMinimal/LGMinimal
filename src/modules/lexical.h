#include "../utils/types.h"
#include <stdio.h>
#ifndef LEXICAL_H
#define LEXICAL_H
    typedef enum TokenType {
        STRING,
        LITERAL,
        KEYWORD,
        OPERATOR,
        BINARY_OPERATOR,
        IDENTIFIER,
        TYPEMENT,
        UNKNOWN,
        BRACKET,
        COLLON,
        SEMI,
        END
    } TokenType;
    typedef struct Token {
        string content;
        TokenType type;
        int parse;
        int col;
        int line;
    } Token;
    memory_slc *lexer(FILE *file);
#endif