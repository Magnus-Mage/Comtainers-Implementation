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

// Type-safe macro interface
#define VECTOR_DEFINE(TYPE) \
    typedef struct { \
        TYPE* data; \
        int size; \
        int capacity; \
    } Vector_##TYPE; \
    \
    static inline void vector_##TYPE##_init(Vector_##TYPE* vec) { \
        vec->size = 0; \
        vec->capacity = 4; \
        vec->data = malloc(sizeof(TYPE) * vec->capacity); \
    } \
    \
    static inline void vector_##TYPE##_push(Vector_##TYPE* vec, TYPE value) { \
        if (vec->size >= vec->capacity) { \
            vec->capacity *= 2; \
            vec->data = realloc(vec->data, sizeof(TYPE) * vec->capacity); \
        } \
        vec->data[vec->size] = value; \
        vec->size++; \
    } \
    \
    static inline TYPE vector_##TYPE##_get(Vector_##TYPE* vec, int index) { \
        if (index < 0 || index >= vec->size) { \
            fprintf(stderr, "Index out of bounds\n"); \
            exit(EXIT_FAILURE); \
        } \
        return vec->data[index]; \
    } \
    \
    static inline void vector_##TYPE##_set(Vector_##TYPE* vec, int index, TYPE value) { \
        if (index < 0 || index >= vec->size) { \
            fprintf(stderr, "Index out of bounds\n"); \
            exit(EXIT_FAILURE); \
        } \
        vec->data[index] = value; \
    } \
    \
    static inline void vector_##TYPE##_free(Vector_##TYPE* vec) { \
        free(vec->data); \
        vec->data = NULL; \
        vec->size = 0; \
        vec->capacity = 0; \
    }

#endif
