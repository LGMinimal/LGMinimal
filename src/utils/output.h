#include "error.h"
#include "types.h"
#ifndef OUTPUT_H
#define OUTPUT_H
    typedef struct Output {
        Error errors;
    } Output;
    Func evoke(string str);
#endif