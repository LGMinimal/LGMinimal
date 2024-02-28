#include "types.h"
#ifndef COLORS_H
#define COLORS_H
    typedef struct Colorize {
        Func setColor;
    } Colorize;
    typedef struct Colorizer {
        Colorize out;
    } Colorizer;
    Colorize newColorize(void);
    typedef enum colors { Purple, Cyan, Yellow, Red, Blue, White, Green, Reset } colors;
#endif