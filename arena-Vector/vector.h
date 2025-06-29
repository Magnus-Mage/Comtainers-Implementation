#ifndef ARENA_VECTOR
#define ARENA_VECTOR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>


typedef struct{
    char* memory;
    size_t size;
    size_t offset;
}Arena;

typedef struct
{
    void* start;
    void* end;
    size_t element_size;
    Arena * arena;
}ArenaVector;

// Arena management fncs

Arena* arena_create(size_t size);
void arena_destroy(Arena* arena);
void arena_reset(Arena* arena);
void* arena_alloc(Arena* arena, size_t size);
size_t arena_remaining(Arena* arena);

// Generic arena vector fncs

void vector_init(ArenaVector* vec, Arena* arena, size_t element_size);
bool vector_push_back(ArenaVector* vec, void* value);
void* vector_get(ArenaVector* vec, int index);
bool vector_set(ArenaVector* vec, int index, void* value);
int vector_size(ArenaVector* vec);
int vector_capacity(ArenaVector* vec);
bool vector_reserve(ArenaVector* vec, int new_capacity);
void vector_clear(ArenaVector* vec);

// Type-safe macro interface
#define ARENA_VECTOR_DEFINE(TYPE) \
    typedef struct { \
        TYPE* start; \
        TYPE* end; \
        Arena* arena; \
    } ArenaVector_##TYPE; \
    \
    static inline void vector_##TYPE##_init(ArenaVector_##TYPE* vec, Arena* arena) { \
        vec->start = NULL; \
        vec->end = NULL; \
        vec->arena = arena; \
    } \
    \
    static inline bool vector_##TYPE##_push(ArenaVector_##TYPE* vec, TYPE value) { \
        if (vec->start == NULL) { \
            vec->start = (TYPE*)arena_alloc(vec->arena, sizeof(TYPE) * 4); \
            if (!vec->start) return false; \
            vec->end = vec->start; \
        } \
        \
        size_t current_size = vec->end - vec->start; \
        size_t current_capacity = current_size; \
        \
        if (vec->end == vec->start + current_capacity) { \
            size_t new_capacity = current_capacity == 0 ? 4 : current_capacity * 2; \
            TYPE* new_start = (TYPE*)arena_alloc(vec->arena, sizeof(TYPE) * new_capacity); \
            if (!new_start) return false; \
            \
            if (vec->start) { \
                memcpy(new_start, vec->start, current_size * sizeof(TYPE)); \
            } \
            vec->start = new_start; \
            vec->end = vec->start + current_size; \
        } \
        \
        *vec->end = value; \
        vec->end++; \
        return true; \
    } \
    \
    static inline TYPE vector_##TYPE##_get(ArenaVector_##TYPE* vec, int index) { \
        if (index < 0 || index >= (vec->end - vec->start)) { \
            fprintf(stderr, "Index out of bounds\n"); \
            exit(EXIT_FAILURE); \
        } \
        return vec->start[index]; \
    } \
    \
    static inline bool vector_##TYPE##_set(ArenaVector_##TYPE* vec, int index, TYPE value) { \
        if (index < 0 || index >= (vec->end - vec->start)) { \
            return false; \
        } \
        vec->start[index] = value; \
        return true; \
    } \
    \
    static inline int vector_##TYPE##_size(ArenaVector_##TYPE* vec) { \
        return vec->end - vec->start; \
    } \
    \
    static inline void vector_##TYPE##_clear(ArenaVector_##TYPE* vec) { \
        vec->end = vec->start; \
    } \
    \
    static inline TYPE* vector_##TYPE##_data(ArenaVector_##TYPE* vec) { \
        return vec->start; \
    }

#endif
