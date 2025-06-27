#include <stdio.h>
#include "vector.h"

#define INITIAL_CAPACITY 4

void init_vector(IntVector* vec)
{
    vec->data = malloc(INITIAL_CAPACITY * sizeof(int));
    vec->size = 0;
    vec->capacity = INITIAL_CAPACITY;
}

void push_back(IntVector* vec, int value)
{
    if(vec->size >= vec->capacity)
    {
        vec->capacity *= 2;
        int* temp = realloc(vec->data, vec->capacity * sizeof(int));

        if(!temp)
        {
            fprintf(stderr, "Memory allocation failed\n");

            exit(EXIT_FAILURE);
        }
        vec->data = temp;
    }
    vec->data[vec->size++] = value;
}
