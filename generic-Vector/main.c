#include "vector.h"
#include <stdio.h>

int main() {
    // Create vector for int
    GVector int_vec;
    vector_init(&int_vec, sizeof(int));
    
    for (int i = 0; i < 10; ++i) {
        int value = i * 10;
        vector_push_back(&int_vec, &value);
    }
    
    for (int i = 0; i < int_vec.size; ++i) {
        int* value = (int*)vector_get(&int_vec, i);
        printf("int_vec[%d] = %d\n", i, *value);
    }
    
    vector_free(&int_vec);
    
    // Create vector for double
    GVector double_vec;
    vector_init(&double_vec, sizeof(double));
    
    double d = 3.14;
    vector_push_back(&double_vec, &d);
    
    double* value = (double*)vector_get(&double_vec, 0);
    printf("double_vec[0] = %f\n", *value);
    
    vector_free(&double_vec);
    
    return 0;
}
