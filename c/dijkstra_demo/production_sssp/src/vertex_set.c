/**
 * @file vertex_set.c
 * @brief Implementation of dynamic vertex set data structure
 * 
 * @author Sambit Chakraborty
 * @date 21-08-2025
 * @version 1.0
 */

#include "vertex_set.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Internal functions
static sssp_error_t ensure_capacity(sssp_vertex_set_t* set, vertex_count_t required_capacity);
static int vertex_compare(const void* a, const void* b);

// Creation and destruction
sssp_vertex_set_t* sssp_vertex_set_create(vertex_count_t initial_capacity,
                                           const sssp_allocator_t* allocator) {
    if (!allocator) allocator = sssp_default_allocator();
    
    sssp_vertex_set_t* set = (sssp_vertex_set_t*)allocator->alloc(sizeof(sssp_vertex_set_t), allocator->context);
    if (!set) {
        SSSP_LOG_ERROR("Failed to allocate vertex set");
        return NULL;
    }
    
    if (initial_capacity == 0) {
        initial_capacity = SSSP_INITIAL_CAPACITY;
    }
    
    set->vertices = (vertex_id_t*)allocator->alloc(initial_capacity * sizeof(vertex_id_t), allocator->context);
    if (!set->vertices) {
        allocator->free(set, allocator->context);
        SSSP_LOG_ERROR("Failed to allocate vertex array");
        return NULL;
    }
    
    set->size = 0;
    set->capacity = initial_capacity;
    set->allocator = allocator;
    
    SSSP_LOG_TRACE("Created vertex set with capacity %u", initial_capacity);
    return set;
}

void sssp_vertex_set_destroy(sssp_vertex_set_t* set) {
    if (!set) return;
    
    if (set->vertices) {
        set->allocator->free(set->vertices, set->allocator->context);
    }
    set->allocator->free(set, set->allocator->context);
    
    SSSP_LOG_TRACE("Destroyed vertex set");
}

sssp_error_t sssp_vertex_set_clear(sssp_vertex_set_t* set) {
    if (!set) return SSSP_ERROR_NULL_POINTER;
    
    set->size = 0;
    return SSSP_SUCCESS;
}

// Basic operations
sssp_error_t sssp_vertex_set_add(sssp_vertex_set_t* set, vertex_id_t vertex) {
    if (!set) return SSSP_ERROR_NULL_POINTER;
    
    // Check if vertex already exists
    if (sssp_vertex_set_contains(set, vertex)) {
        return SSSP_ERROR_INVALID_PARAMETER;
    }
    
    sssp_error_t err = ensure_capacity(set, set->size + 1);
    if (err != SSSP_SUCCESS) return err;
    
    set->vertices[set->size++] = vertex;
    return SSSP_SUCCESS;
}

sssp_error_t sssp_vertex_set_add_array(sssp_vertex_set_t* set, 
                                        const vertex_id_t* vertices, 
                                        vertex_count_t count) {
    if (!set || (!vertices && count > 0)) return SSSP_ERROR_NULL_POINTER;
    if (count == 0) return SSSP_SUCCESS;
    
    vertex_count_t new_size;
    if (!sssp_safe_add_vertex_count(set->size, count, &new_size)) {
        return SSSP_ERROR_OVERFLOW;
    }
    
    sssp_error_t err = ensure_capacity(set, new_size);
    if (err != SSSP_SUCCESS) return err;
    
    memcpy(set->vertices + set->size, vertices, count * sizeof(vertex_id_t));
    set->size = new_size;
    
    return SSSP_SUCCESS;
}

sssp_error_t sssp_vertex_set_remove(sssp_vertex_set_t* set, vertex_id_t vertex) {
    if (!set) return SSSP_ERROR_NULL_POINTER;
    
    vertex_count_t index;
    if (!sssp_vertex_set_find(set, vertex, &index)) {
        return SSSP_ERROR_INVALID_ARGUMENT; // Vertex not found
    }
    
    // Shift remaining elements
    if (index < set->size - 1) {
        memmove(set->vertices + index, 
                set->vertices + index + 1, 
                (set->size - index - 1) * sizeof(vertex_id_t));
    }
    set->size--;
    
    return SSSP_SUCCESS;
}

sssp_error_t sssp_vertex_set_remove_at(sssp_vertex_set_t* set, vertex_count_t index) {
    if (!set) return SSSP_ERROR_NULL_POINTER;
    if (index >= set->size) return SSSP_ERROR_INVALID_ARGUMENT;
    
    // Fast removal: swap with last element
    if (index < set->size - 1) {
        set->vertices[index] = set->vertices[set->size - 1];
    }
    set->size--;
    
    return SSSP_SUCCESS;
}

bool sssp_vertex_set_contains(const sssp_vertex_set_t* set, vertex_id_t vertex) {
    return sssp_vertex_set_find(set, vertex, NULL);
}

bool sssp_vertex_set_find(const sssp_vertex_set_t* set, 
                          vertex_id_t vertex, 
                          vertex_count_t* index_out) {
    if (!set) return false;
    
    for (vertex_count_t i = 0; i < set->size; i++) {
        if (set->vertices[i] == vertex) {
            if (index_out) *index_out = i;
            return true;
        }
    }
    return false;
}

sssp_error_t sssp_vertex_set_get(const sssp_vertex_set_t* set, 
                                  vertex_count_t index, 
                                  vertex_id_t* vertex_out) {
    if (!set || !vertex_out) return SSSP_ERROR_NULL_POINTER;
    if (index >= set->size) return SSSP_ERROR_INVALID_ARGUMENT;
    
    *vertex_out = set->vertices[index];
    return SSSP_SUCCESS;
}

vertex_id_t sssp_vertex_set_get_vertex(const sssp_vertex_set_t* set, 
                                        vertex_count_t index) {
    if (!set || index >= set->size) {
        return SSSP_INVALID_VERTEX;
    }
    return set->vertices[index];
}

// Set operations
sssp_error_t sssp_vertex_set_union(sssp_vertex_set_t* dest, 
                                    const sssp_vertex_set_t* src) {
    if (!dest || !src) return SSSP_ERROR_NULL_POINTER;
    
    for (vertex_count_t i = 0; i < src->size; i++) {
        if (!sssp_vertex_set_contains(dest, src->vertices[i])) {
            sssp_error_t err = sssp_vertex_set_add(dest, src->vertices[i]);
            if (err != SSSP_SUCCESS) return err;
        }
    }
    
    return SSSP_SUCCESS;
}

sssp_error_t sssp_vertex_set_intersection(sssp_vertex_set_t* dest, 
                                           const sssp_vertex_set_t* src) {
    if (!dest || !src) return SSSP_ERROR_NULL_POINTER;
    
    vertex_count_t write_pos = 0;
    for (vertex_count_t i = 0; i < dest->size; i++) {
        if (sssp_vertex_set_contains(src, dest->vertices[i])) {
            dest->vertices[write_pos++] = dest->vertices[i];
        }
    }
    dest->size = write_pos;
    
    return SSSP_SUCCESS;
}

sssp_error_t sssp_vertex_set_difference(sssp_vertex_set_t* dest, 
                                         const sssp_vertex_set_t* src) {
    if (!dest || !src) return SSSP_ERROR_NULL_POINTER;
    
    vertex_count_t write_pos = 0;
    for (vertex_count_t i = 0; i < dest->size; i++) {
        if (!sssp_vertex_set_contains(src, dest->vertices[i])) {
            dest->vertices[write_pos++] = dest->vertices[i];
        }
    }
    dest->size = write_pos;
    
    return SSSP_SUCCESS;
}

sssp_error_t sssp_vertex_set_copy(sssp_vertex_set_t* dest, 
                                   const sssp_vertex_set_t* src) {
    if (!dest || !src) return SSSP_ERROR_NULL_POINTER;
    
    sssp_error_t err = ensure_capacity(dest, src->size);
    if (err != SSSP_SUCCESS) return err;
    
    memcpy(dest->vertices, src->vertices, src->size * sizeof(vertex_id_t));
    dest->size = src->size;
    
    return SSSP_SUCCESS;
}

// Memory management
sssp_error_t sssp_vertex_set_reserve(sssp_vertex_set_t* set, vertex_count_t new_capacity) {
    if (!set) return SSSP_ERROR_NULL_POINTER;
    
    return ensure_capacity(set, new_capacity);
}

sssp_error_t sssp_vertex_set_shrink_to_fit(sssp_vertex_set_t* set) {
    if (!set) return SSSP_ERROR_NULL_POINTER;
    if (set->size == set->capacity) return SSSP_SUCCESS;
    
    vertex_count_t new_capacity = SSSP_MAX(set->size, 1);
    vertex_id_t* new_vertices = (vertex_id_t*)set->allocator->realloc(
        set->vertices, 
        new_capacity * sizeof(vertex_id_t), 
        set->allocator->context);
    
    if (!new_vertices) {
        SSSP_LOG_WARN("Failed to shrink vertex set");
        return SSSP_ERROR_OUT_OF_MEMORY;
    }
    
    set->vertices = new_vertices;
    set->capacity = new_capacity;
    
    return SSSP_SUCCESS;
}

// Sorting and ordering
sssp_error_t sssp_vertex_set_sort(sssp_vertex_set_t* set) {
    if (!set) return SSSP_ERROR_NULL_POINTER;
    if (set->size <= 1) return SSSP_SUCCESS;
    
    qsort(set->vertices, set->size, sizeof(vertex_id_t), vertex_compare);
    return SSSP_SUCCESS;
}

sssp_error_t sssp_vertex_set_sort_custom(sssp_vertex_set_t* set,
                                          int (*compare)(const void* a, const void* b, void* context),
                                          void* context) {
    if (!set || !compare) return SSSP_ERROR_NULL_POINTER;
    if (set->size <= 1) return SSSP_SUCCESS;
    
    // Note: Standard qsort doesn't support context, so we'd need a custom sort
    // For now, fall back to regular sort
    return sssp_vertex_set_sort(set);
}

sssp_error_t sssp_vertex_set_unique(sssp_vertex_set_t* set) {
    if (!set) return SSSP_ERROR_NULL_POINTER;
    if (set->size <= 1) return SSSP_SUCCESS;
    
    // First sort the set
    sssp_error_t err = sssp_vertex_set_sort(set);
    if (err != SSSP_SUCCESS) return err;
    
    // Remove duplicates
    vertex_count_t write_pos = 0;
    for (vertex_count_t i = 0; i < set->size; i++) {
        if (i == 0 || set->vertices[i] != set->vertices[write_pos - 1]) {
            set->vertices[write_pos++] = set->vertices[i];
        }
    }
    set->size = write_pos;
    
    return SSSP_SUCCESS;
}

// Iterator functions
sssp_error_t sssp_vertex_set_iterator_init(const sssp_vertex_set_t* set,
                                            sssp_vertex_set_iterator_t* iter) {
    if (!set || !iter) return SSSP_ERROR_NULL_POINTER;
    
    iter->set = set;
    iter->index = 0;
    return SSSP_SUCCESS;
}

bool sssp_vertex_set_iterator_next(sssp_vertex_set_iterator_t* iter,
                                   vertex_id_t* vertex_out) {
    if (!iter || !iter->set || !vertex_out) return false;
    
    if (iter->index >= iter->set->size) return false;
    
    *vertex_out = iter->set->vertices[iter->index++];
    return true;
}

void sssp_vertex_set_iterator_reset(sssp_vertex_set_iterator_t* iter) {
    if (iter) {
        iter->index = 0;
    }
}

// Debugging and validation
void sssp_vertex_set_print(const sssp_vertex_set_t* set, vertex_count_t max_vertices) {
    if (!set) {
        printf("NULL vertex set\n");
        return;
    }
    
    vertex_count_t count = (max_vertices == 0 || max_vertices > set->size) ? 
                          set->size : max_vertices;
    
    printf("Vertex set (size=%u, capacity=%u): [", set->size, set->capacity);
    for (vertex_count_t i = 0; i < count; i++) {
        if (i > 0) printf(", ");
        printf("%d", set->vertices[i]);
    }
    if (count < set->size) {
        printf(", ... (%u more)", set->size - count);
    }
    printf("]\n");
}

void sssp_vertex_set_print_stats(const sssp_vertex_set_t* set) {
    if (!set) {
        printf("NULL vertex set\n");
        return;
    }
    
    printf("Vertex Set Statistics:\n");
    printf("  Size: %u vertices\n", set->size);
    printf("  Capacity: %u vertices\n", set->capacity);
    printf("  Memory usage: %zu bytes\n", set->capacity * sizeof(vertex_id_t) + sizeof(sssp_vertex_set_t));
    printf("  Load factor: %.2f%%\n", set->capacity > 0 ? (100.0 * set->size / set->capacity) : 0.0);
}

bool sssp_vertex_set_validate(const sssp_vertex_set_t* set) {
    if (!set) return false;
    if (!set->vertices && set->capacity > 0) return false;
    if (set->size > set->capacity) return false;
    if (!set->allocator) return false;
    
    return true;
}

bool sssp_vertex_set_is_valid(const sssp_vertex_set_t* set) {
    return sssp_vertex_set_validate(set);
}

// Internal helper functions
static sssp_error_t ensure_capacity(sssp_vertex_set_t* set, vertex_count_t required_capacity) {
    if (set->capacity >= required_capacity) return SSSP_SUCCESS;
    
    vertex_count_t new_capacity = set->capacity;
    if (new_capacity == 0) {
        new_capacity = SSSP_INITIAL_CAPACITY;
    }
    
    while (new_capacity < required_capacity) {
        vertex_count_t doubled;
        if (!sssp_safe_mul_vertex_count(new_capacity, 2, &doubled)) {
            // Overflow protection
            new_capacity = required_capacity;
            break;
        }
        new_capacity = doubled;
    }
    
    vertex_id_t* new_vertices = (vertex_id_t*)set->allocator->realloc(
        set->vertices, 
        new_capacity * sizeof(vertex_id_t), 
        set->allocator->context);
    
    if (!new_vertices) {
        SSSP_LOG_ERROR("Failed to expand vertex set capacity to %u", new_capacity);
        return SSSP_ERROR_OUT_OF_MEMORY;
    }
    
    set->vertices = new_vertices;
    set->capacity = new_capacity;
    
    SSSP_LOG_TRACE("Expanded vertex set capacity to %u", new_capacity);
    return SSSP_SUCCESS;
}

static int vertex_compare(const void* a, const void* b) {
    vertex_id_t va = *(const vertex_id_t*)a;
    vertex_id_t vb = *(const vertex_id_t*)b;
    
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}
