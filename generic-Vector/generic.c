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
    void* target = (char* )vec->data + vec->size * vec->element_size;
    memcpy(target, value, vec->element_size);
    vec->size++;
}

void *vector_get(GVector* vec, int index)
{
    if (index <0 || index >= vec->size)
    {
        return NULL;
    }

    return (char* )vec->data + index * vec->element_size;
}


void vector_set(GVector* vec, int index, void* value)
{
    if (index < 0 || index >= vec->size)
    {
        fprintf(stderr, "Out of Bounds.\n");
        exit(EXIT_FAILURE);
    }

    void *target = (char* )vec->data + index * vec->element_size;
    memcpy(target, value, vec->element_size);
}

void vector_free(GVector* vec)
{
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->element_size = 0;
    vec->capacity = 0;
}
