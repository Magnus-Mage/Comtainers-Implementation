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

Arena*
