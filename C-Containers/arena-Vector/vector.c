#include "vector.h"

// Arena management functions
Arena* arena_create(size_t size) {
    Arena* arena = malloc(sizeof(Arena));
    if (!arena) return NULL;
    
    arena->memory = malloc(size);
    if (!arena->memory) {
        free(arena);
        return NULL;
    }
    
    arena->size = size;
    arena->offset = 0;
    return arena;
}

void arena_destroy(Arena* arena) {
    if (arena) {
        free(arena->memory);
        free(arena);
    }
}

void arena_reset(Arena* arena) {
    if (arena) {
        arena->offset = 0;
    }
}

void* arena_alloc(Arena* arena, size_t size) {
    if (!arena || arena->offset + size > arena->size) {
        return NULL; // Not enough space
    }
    
    void* ptr = arena->memory + arena->offset;
    arena->offset += size;
    return ptr;
}

size_t arena_remaining(Arena* arena) {
    return arena ? arena->size - arena->offset : 0;
}

// Generic arena vector functions
void vector_init(ArenaVector* vec, Arena* arena, size_t element_size) {
    vec->start = NULL;
    vec->end = NULL;
    vec->element_size = element_size;
    vec->arena = arena;
}

bool vector_push_back(ArenaVector* vec, void* value) {
    if (!vec || !vec->arena || !value) return false;
    
    // Initialize with capacity of 4 if empty
    if (vec->start == NULL) {
        vec->start = arena_alloc(vec->arena, vec->element_size * 4);
        if (!vec->start) return false;
        vec->end = vec->start;
    }
    
    size_t current_size = ((char*)vec->end - (char*)vec->start) / vec->element_size;
    size_t bytes_from_start = (char*)vec->end - (char*)vec->start;
    
    // Check if we need to grow (this is a simplified check)
    // In a real implementation, you'd track capacity separately
    void* new_location = arena_alloc(vec->arena, vec->element_size);
    if (!new_location) {
        // Try to allocate a larger chunk and copy
        size_t new_capacity = current_size == 0 ? 4 : current_size * 2;
        void* new_start = arena_alloc(vec->arena, vec->element_size * new_capacity);
        if (!new_start) return false;
        
        if (vec->start && current_size > 0) {
            memcpy(new_start, vec->start, bytes_from_start);
        }
        vec->start = new_start;
        vec->end = (char*)vec->start + bytes_from_start;
    } else {
        // We can extend in place
        vec->end = new_location;
    }
    
    // Copy the new value
    memcpy(vec->end, value, vec->element_size);
    vec->end = (char*)vec->end + vec->element_size;
    
    return true;
}

void* vector_get(ArenaVector* vec, int index) {
    if (!vec || !vec->start || index < 0) return NULL;
    
    size_t current_size = ((char*)vec->end - (char*)vec->start) / vec->element_size;
    if (index >= current_size) return NULL;
    
    return (char*)vec->start + index * vec->element_size;
}

bool vector_set(ArenaVector* vec, int index, void* value) {
    if (!vec || !vec->start || !value || index < 0) return false;
    
    size_t current_size = ((char*)vec->end - (char*)vec->start) / vec->element_size;
    if (index >= current_size) return false;
    
    void* target = (char*)vec->start + index * vec->element_size;
    memcpy(target, value, vec->element_size);
    return true;
}

int vector_size(ArenaVector* vec) {
    if (!vec || !vec->start) return 0;
    return ((char*)vec->end - (char*)vec->start) / vec->element_size;
}

bool vector_reserve(ArenaVector* vec, int new_capacity) {
    if (!vec || !vec->arena) return false;
    
    size_t current_size = vector_size(vec);
    if (new_capacity <= current_size) return true; // Already have enough capacity
    
    void* new_start = arena_alloc(vec->arena, vec->element_size * new_capacity);
    if (!new_start) return false;
    
    if (vec->start && current_size > 0) {
        memcpy(new_start, vec->start, current_size * vec->element_size);
    }
    
    vec->start = new_start;
    vec->end = (char*)vec->start + current_size * vec->element_size;
    
    return true;
}

void vector_clear(ArenaVector* vec) {
    if (vec && vec->start) {
        vec->end = vec->start;
    }
}
