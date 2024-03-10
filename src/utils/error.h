#include "types.h"
#ifndef ERROR_H
#define ERROR_H

    typedef enum {
        EXPECTED_IDENTIFIER,
        NEED_COLLON_BEFORE_TYPE,
        EXPECTED_TYPE
    } ITER_ERROS;

    typedef struct Error {
        Func lgcm;
        Func lexical;
        Func syntax;
    } Error;

    Error newError(void);
#endif