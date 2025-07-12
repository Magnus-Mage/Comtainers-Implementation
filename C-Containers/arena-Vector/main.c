#include "vector.h"
#include <stdio.h>

// Generate type-safe vector for int and double
ARENA_VECTOR_DEFINE(int)
ARENA_VECTOR_DEFINE(double)

int main() {
    // Create an arena with 1KB of memory
    Arena* arena = arena_create(1024);
    if (!arena) {
        fprintf(stderr, "Failed to create arena\n");
        return 1;
    }
    
    printf("Arena created with %zu bytes\n", arena->size);
    
    // Example 1: Type-safe int vector
    printf("\n=== Type-safe int vector ===\n");
    ArenaVector_int int_vec;
    vector_int_init(&int_vec, arena);
    
    // Push some integers
    for (int i = 0; i < 10; i++) {
        if (!vector_int_push(&int_vec, i * 10)) {
            printf("Failed to push %d\n", i * 10);
            break;
        }
    }
    
    printf("Int vector size: %d\n", vector_int_size(&int_vec));
    printf("Int vector contents: ");
    for (int i = 0; i < vector_int_size(&int_vec); i++) {
        printf("%d ", vector_int_get(&int_vec, i));
    }
    printf("\n");
    
    // Show pointer arithmetic
    printf("Start pointer: %p\n", (void*)int_vec.start);
    printf("End pointer: %p\n", (void*)int_vec.end);
    printf("Pointer difference: %ld elements\n", int_vec.end - int_vec.start);
    
    // Example 2: Type-safe double vector (sharing same arena)
    printf("\n=== Type-safe double vector (same arena) ===\n");
    ArenaVector_double double_vec;
    vector_double_init(&double_vec, arena);
    
    double values[] = {3.14, 2.71, 1.41, 1.73};
    for (int i = 0; i < 4; i++) {
        if (!vector_double_push(&double_vec, values[i])) {
            printf("Failed to push %f\n", values[i]);
            break;
        }
    }
    
    printf("Double vector size: %d\n", vector_double_size(&double_vec));
    printf("Double vector contents: ");
    for (int i = 0; i < vector_double_size(&double_vec); i++) {
        printf("%.2f ", vector_double_get(&double_vec, i));
    }
    printf("\n");
    
    printf("Start pointer: %p\n", (void*)double_vec.start);
    printf("End pointer: %p\n", (void*)double_vec.end);
    printf("Pointer difference: %ld elements\n", double_vec.end - double_vec.start);
    
    // Example 3: Generic vector interface
    printf("\n=== Generic vector interface ===\n");
    ArenaVector generic_vec;
    vector_init(&generic_vec, arena, sizeof(int));
    
    for (int i = 100; i < 105; i++) {
        if (!vector_push_back(&generic_vec, &i)) {
            printf("Failed to push %d\n", i);
            break;
        }
    }
    
    printf("Generic vector size: %d\n", vector_size(&generic_vec));
    printf("Generic vector contents: ");
    for (int i = 0; i < vector_size(&generic_vec); i++) {
        int* value = (int*)vector_get(&generic_vec, i);
        if (value) {
            printf("%d ", *value);
        }
    }
    printf("\n");
    
    // Show arena usage
    printf("\n=== Arena Statistics ===\n");
    printf("Arena size: %zu bytes\n", arena->size);
    printf("Arena used: %zu bytes\n", arena->offset);
    printf("Arena remaining: %zu bytes\n", arena_remaining(arena));
    
    // Memory layout visualization
    printf("\n=== Memory Layout ===\n");
    printf("Arena base: %p\n", (void*)arena->memory);
    printf("Int vector start: %p (offset: %ld)\n", 
           (void*)int_vec.start, 
           (char*)int_vec.start - arena->memory);
    printf("Double vector start: %p (offset: %ld)\n", 
           (void*)double_vec.start, 
           (char*)double_vec.start - arena->memory);
    printf("Generic vector start: %p (offset: %ld)\n", 
           generic_vec.start, 
           (char*)generic_vec.start - arena->memory);
    
    // Cleanup
    arena_destroy(arena);
    printf("\nArena destroyed\n");
    
    return 0;
}
