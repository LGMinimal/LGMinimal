#include "utils/types.h"
#include <stdio.h>
#ifndef MAKE_H
#define MAKE_H
    typedef struct assembly {
        string linux;
        string windows;
    } assembly;
    assembly make(FILE *file);
#endif