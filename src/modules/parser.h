#include "../utils/types.h"
#include "lexical.h"
#ifndef PARSER_H
#define PARSER_H
    typedef struct {
        Token token;
    } pExpr;
    
    typedef enum {
        DEFINITION
    } NodeType;

    typedef struct {
        memory_slc* expression;
        types        expr_type;
        NodeType          type;
    } pNode;
    string parser(memory_slc *tokens);
#endif