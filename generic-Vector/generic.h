#ifndef GVECTOR_H
#define GVECTOR_H

#include <stddef.h>

typedef struct{
    void* data;
    size_t element_size;
    int size;
    int capacity;
}GVector;

void vector_init(GVector* vec, size_t element_size);
void vector_push_back(GVector* vec, void* value);
void *vector_get(GVector* vec, int index);
void vector_set(GVector* vec, int index, void* value);
void vector_free(GVector* vec);

#endif
