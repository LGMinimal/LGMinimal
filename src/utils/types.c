#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define INITIAL_CAPACITY 10

long
toInteger (string value)
{
    long result = 0;
    size_t length = strlen (value);
    for(int i = 0; i < length; i++)
        {
            result += ((string)value)[i];
        }
    result += length * CONSTANT_TO_CALC_SIZE;
    return result;
}

vec* 
Vec() 
{
    vec *vector = (vec*)malloc (sizeof(vec));
    if (vector == NULL) 
        {
            perror ("Memory allocation failed");
            exit (EXIT_FAILURE);
        }
    vector->data = NULL; 
    vector->length = 0;
    vector->capacity = 0; 
    return vector;
} 

void 
push(vec *self, void *element) 
{
    self->capacity++;
    self->data = (dynamic*)realloc (self->data, self->capacity * sizeof (dynamic));
    if( self->data == NULL ) 
        {
            perror ("Memory allocation failed");
            exit (EXIT_FAILURE);
        }

    self->data[self->length++] = element;
}

dynamic
pull(vec *self, int index) 
{
    if( index < self->length )
        /*->*/ return self->data[index];
    else 
        {
            fprintf (stderr, "Index out of range\n");
            return NULL;
        }
}

void 
destroy(vec *self)
{
    free (self->data);
    free (self);
}

char
endsWith(string content, string end) 
{
    int i = strlen (end) - 1;
    int j = strlen (content) - 1;
    for( ; i >= 0; i--)
        {
            if( content[j] != end[i] ) 
                /*->*/ break;
            j--;
        }
    return i < 0;
}

queue*
queueCreate()
{
    queue *rt = (queue *)malloc(sizeof(queue));

    rt->back = NULL;
    rt->head = NULL;
    return rt;
}
void 
queueInsert(queue *self, dynamic data, size_t __size)
{
    QueueNode *newNode = (QueueNode *)malloc(sizeof(queue));
    newNode->next = NULL;
    newNode->data = malloc(__size);
    memcpy(newNode->data, data, __size);
    if (self->head == NULL)
    {
        self->head = newNode;
        self->back = self->head;
        self->head->before = self->back;
        self->head->next = NULL;
        self->back->next = self->head;
        self->back->before = NULL;
    }
    else
    {
        self->back->before = newNode;
        newNode->before = NULL;
        newNode->next = self->back;
        self->back = newNode;
    }
}

dynamic 
queueRead(queue *self, size_t __size)
{
    dynamic rt = malloc(__size);
    if (self->head == NULL)
        /*->*/ return NULL;
    memcpy(rt, self->head->data, __size);
    QueueNode *ant = self->head;
    self->head = self->head->before;
    free(ant->data);
    free(ant);
    return rt;
}

dynamic
memdup(dynamic src, size_t size) {
    dynamic dest = malloc(size);
    if (dest != NULL) {
        memcpy(dest, src, size);
    }
    return dest;
}

memory_slc* 
slloc(size_t item_size) {
    memory_slc* array = malloc(sizeof(memory_slc));
    if (array == NULL) {
        perror("Error to alloc a vector to StructVectir");
        exit(EXIT_FAILURE);
    }

    array->items = malloc(item_size * INITIAL_CAPACITY);
    if (array->items == NULL) {
        perror("Fail to alloc new StructVectors");
        exit(EXIT_FAILURE);
    }

    array->capacity = INITIAL_CAPACITY;
    array->size = 0;
    array->item_size = item_size;

    return array;
}

void 
spush(memory_slc* self, dynamic item) {
    if (self->size >= self->capacity) 
        {
            self->capacity *= 2;
            self->items = realloc(self->items,self->item_size * self->capacity);
            if (self->items == NULL) 
                {
                    perror("Erro ao realocar memória para os itens do vetor dinâmico");
                    exit(EXIT_FAILURE);
                }
        }

    dynamic dest = (dynamic)self->items + (self->size * self->item_size);
    memcpy(dest, item, self->item_size);

    self->size++;
}

dynamic* 
sget(memory_slc* self, int index) 
{
    if (index >= self->size) 
        {
            fprintf(stderr, "INVALID INDEX\n");
            exit(EXIT_FAILURE);
        }

    return (dynamic)self->items + (index * self->item_size);
}

void 
sdestroy(memory_slc* self) 
{
    free(self->items);
    free(self);
}