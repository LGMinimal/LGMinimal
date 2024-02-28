#include "types.h"
#ifndef ERROR_H
#define ERROR_H
    typedef struct Error {
        Func lgcm;
    } Error;
    Error newError(void);
#endif