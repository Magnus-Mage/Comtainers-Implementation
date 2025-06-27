#ifndef VECTOR_H
#define VECTOR_H

typedef struct
{
    int* data;
    int size;
    int capacity;

}IntVector;

void init_vector(IntVector* vec);
void push_back(IntVector* vec, int value);
void pop_back(IntVector* vec);
void get(IntVector* vec, int value);
void free_vector(IntVector* vec);

#endif
