#include "generic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 4

void vector_init(GVector* vec, size_t element_size)
{
    vec->element_size = element_size;
    vec->size = 0;
    vec->capacity = INITIAL_CAPACITY;
    vec->data = malloc(element_size * vec->capacity);
}

void vector_push_back(GVector*vec, void* value)
{
    if (vec->size >= vec->capacity - 1)
    {
        vec->capacity *= 2;
        vec->data = realloc(vec->data, vec->element_size * vec->capacity);
    }
    void* target = 
}
