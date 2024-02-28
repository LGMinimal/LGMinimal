#ifndef TYPES_H
#define TYPES_H
    #define CONSTANT_TO_CALC_SIZE 100000
    typedef void (*Func)();
    typedef void* dynamic;
    typedef char* string;
    typedef enum types { TString } types;
    long toInteger(string str);
#endif