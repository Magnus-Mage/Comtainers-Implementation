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
int get(IntVector* vec, int index);
void set(IntVector* vec, int index, int value);
void free_vector(IntVector* vec);

#endif
