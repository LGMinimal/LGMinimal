#include <stdio.h>
#ifndef TYPES_H
#define TYPES_H
    // conversions
    #define CONSTANT_TO_CALC_SIZE 100000
    // types
    typedef void (*Func)();
    typedef char* string;
    typedef enum { TString, TByte, TShort, TInt, TLong, TVoid } types;
    typedef void* dynamic;
    typedef struct {
        dynamic   *data;
        size_t   length;
        size_t capacity;
    } vec;
    long toInteger(string str);
    char endsWith(string content, string end);
    void push(vec *self, void *element);
    dynamic pull(vec *self, int index);
    void destroy(vec *self);
    vec *Vec();
    typedef struct QueueNode {
        struct QueueNode *next;
        struct QueueNode *before;
        void *data;
    } QueueNode;
    typedef struct {
        struct QueueNode *head;
        struct QueueNode *back;
    } queue;
    queue *queueCreate();
    void queueInsert(queue *queue, void *data, size_t __size);
    void *queueRead(queue *queue, size_t __size);
    
    // struct vectors
    #define SALLOC(self, type)                        \
        type *x = (type *)malloc(sizeof(type) * size); \
        x[i] = self;                                    \
        x                                                \

    typedef struct {
        size_t item_size;
        size_t  capacity;
        dynamic    items;
        size_t      size;
    } memory_slc;
    dynamic *sget(memory_slc *self, int index);
    void spush(memory_slc *self, dynamic item);
    memory_slc *slloc(size_t item_size);
    void sdestroy(memory_slc *self);
#endif