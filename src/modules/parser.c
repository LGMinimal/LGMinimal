#include <stdio.h>
#include <stdlib.h>
#include "../utils/types.h"
#include "parser.h"
#include "parser/syntax.h"
#include "parser/generate.h"

string
parser(memory_slc *tokens)
{
    memory_slc *pTree = slloc (sizeof (pNode));
    parseSyntax (tokens, pTree);
    string code = genCode (pTree);
    sdestroy (pTree);
    return code;
}