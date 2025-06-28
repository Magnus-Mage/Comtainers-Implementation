#include <stdio.h>
#include <stdlib.h>
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


void pop_back(IntVector* vec)
{
    if (vec->size > 0)
    {
        vec->size--;
    }
}

void set(IntVector* vec, int index, int value)
{
    if(index < 0 || index >= vec->size)
    {
        fprintf(stderr, "Index out of memory.\n");
        exit(EXIT_FAILURE);
    }
    vec->data[index] = value;
}

int get(IntVector* vec, int index)
{
    if(index < 0 || index >= vec->size)
    {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    return vec->data[index];
}


void free_vector(IntVector* vec)
{
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;

}
