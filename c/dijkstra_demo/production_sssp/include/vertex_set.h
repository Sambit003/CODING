/**
 * @file vertex_set.h
 * @brief Dynamic vertex set data structure
 * 
 * This file defines a dynamic vertex set used throughout the SSSP algorithm
 * for managing collections of vertices efficiently.
 * 
 * @author Sambit Chakraborty
 * @date 21-08-2025
 * @version 1.0
 */

#ifndef SSSP_VERTEX_SET_H
#define SSSP_VERTEX_SET_H

#include "sssp_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Dynamic vertex set structure
 */
typedef struct sssp_vertex_set {
    vertex_id_t* vertices;          ///< Array of vertex IDs
    vertex_count_t size;            ///< Current number of vertices
    vertex_count_t capacity;        ///< Current capacity of the array
    const sssp_allocator_t* allocator; ///< Memory allocator
} sssp_vertex_set_t;

/**
 * @brief Vertex set creation and destruction
 */

/**
 * @brief Create a new vertex set with initial capacity
 * @param initial_capacity Initial capacity (0 for default)
 * @param allocator Memory allocator (NULL for default)
 * @return Pointer to new vertex set or NULL on failure
 */
sssp_vertex_set_t* sssp_vertex_set_create(vertex_count_t initial_capacity,
                                           const sssp_allocator_t* allocator);

/**
 * @brief Destroy a vertex set and free all memory
 * @param set Vertex set to destroy
 */
void sssp_vertex_set_destroy(sssp_vertex_set_t* set);

/**
 * @brief Clear all vertices from the set (but keep capacity)
 * @param set Vertex set to clear
 * @return Error code
 */
sssp_error_t sssp_vertex_set_clear(sssp_vertex_set_t* set);

/**
 * @brief Vertex set operations
 */

/**
 * @brief Add a vertex to the set
 * @param set Target vertex set
 * @param vertex Vertex ID to add
 * @return Error code
 */
sssp_error_t sssp_vertex_set_add(sssp_vertex_set_t* set, vertex_id_t vertex);

/**
 * @brief Add multiple vertices to the set
 * @param set Target vertex set
 * @param vertices Array of vertex IDs to add
 * @param count Number of vertices to add
 * @return Error code
 */
sssp_error_t sssp_vertex_set_add_array(sssp_vertex_set_t* set, 
                                        const vertex_id_t* vertices, 
                                        vertex_count_t count);

/**
 * @brief Remove a vertex from the set (maintains order)
 * @param set Target vertex set
 * @param vertex Vertex ID to remove
 * @return Error code (SSSP_SUCCESS if removed, other if not found)
 */
sssp_error_t sssp_vertex_set_remove(sssp_vertex_set_t* set, vertex_id_t vertex);

/**
 * @brief Remove vertex at specific index (fast, may change order)
 * @param set Target vertex set
 * @param index Index of vertex to remove
 * @return Error code
 */
sssp_error_t sssp_vertex_set_remove_at(sssp_vertex_set_t* set, vertex_count_t index);

/**
 * @brief Check if a vertex is in the set
 * @param set Target vertex set
 * @param vertex Vertex ID to check
 * @return true if vertex is in set, false otherwise
 */
bool sssp_vertex_set_contains(const sssp_vertex_set_t* set, vertex_id_t vertex);

/**
 * @brief Find index of a vertex in the set
 * @param set Target vertex set
 * @param vertex Vertex ID to find
 * @param index_out Pointer to store index (can be NULL)
 * @return true if vertex found, false otherwise
 */
bool sssp_vertex_set_find(const sssp_vertex_set_t* set, 
                          vertex_id_t vertex, 
                          vertex_count_t* index_out);

/**
 * @brief Get vertex at specific index
 * @param set Target vertex set
 * @param index Index of vertex
 * @param vertex_out Pointer to store vertex ID
 * @return Error code
 */
sssp_error_t sssp_vertex_set_get(const sssp_vertex_set_t* set, 
                                  vertex_count_t index, 
                                  vertex_id_t* vertex_out);

/**
 * @brief Get vertex ID at specified index (direct access)
 * @param set Vertex set instance
 * @param index Index in the set
 * @return Vertex ID or SSSP_INVALID_VERTEX if out of bounds
 */
vertex_id_t sssp_vertex_set_get_vertex(const sssp_vertex_set_t* set, 
                                        vertex_count_t index);

/**
 * @brief Set operations
 */

/**
 * @brief Union of two vertex sets (dest = dest ∪ src)
 * @param dest Destination vertex set
 * @param src Source vertex set
 * @return Error code
 */
sssp_error_t sssp_vertex_set_union(sssp_vertex_set_t* dest, 
                                    const sssp_vertex_set_t* src);

/**
 * @brief Intersection of two vertex sets (dest = dest ∩ src)
 * @param dest Destination vertex set
 * @param src Source vertex set
 * @return Error code
 */
sssp_error_t sssp_vertex_set_intersection(sssp_vertex_set_t* dest, 
                                           const sssp_vertex_set_t* src);

/**
 * @brief Difference of two vertex sets (dest = dest \ src)
 * @param dest Destination vertex set
 * @param src Source vertex set
 * @return Error code
 */
sssp_error_t sssp_vertex_set_difference(sssp_vertex_set_t* dest, 
                                         const sssp_vertex_set_t* src);

/**
 * @brief Copy vertex set
 * @param dest Destination vertex set
 * @param src Source vertex set
 * @return Error code
 */
sssp_error_t sssp_vertex_set_copy(sssp_vertex_set_t* dest, 
                                   const sssp_vertex_set_t* src);

/**
 * @brief Properties and utilities
 */

/**
 * @brief Get the number of vertices in the set
 * @param set Target vertex set
 * @return Number of vertices in the set
 */
SSSP_INLINE vertex_count_t sssp_vertex_set_size(const sssp_vertex_set_t* set) {
    return set ? set->size : 0;
}

/**
 * @brief Get the current capacity of the set
 * @param set Target vertex set
 * @return Current capacity
 */
SSSP_INLINE vertex_count_t sssp_vertex_set_capacity(const sssp_vertex_set_t* set) {
    return set ? set->capacity : 0;
}

/**
 * @brief Check if the set is empty
 * @param set Target vertex set
 * @return true if set is empty
 */
SSSP_INLINE bool sssp_vertex_set_is_empty(const sssp_vertex_set_t* set) {
    return !set || set->size == 0;
}

/**
 * @brief Get direct access to the vertex array (read-only)
 * @param set Target vertex set
 * @return Pointer to vertex array or NULL if set is invalid
 */
SSSP_INLINE const vertex_id_t* sssp_vertex_set_data(const sssp_vertex_set_t* set) {
    return set ? set->vertices : NULL;
}

/**
 * @brief Reserve capacity for the set
 * @param set Target vertex set
 * @param new_capacity New capacity to reserve
 * @return Error code
 */
sssp_error_t sssp_vertex_set_reserve(sssp_vertex_set_t* set, vertex_count_t new_capacity);

/**
 * @brief Shrink capacity to match current size
 * @param set Target vertex set
 * @return Error code
 */
sssp_error_t sssp_vertex_set_shrink_to_fit(sssp_vertex_set_t* set);

/**
 * @brief Sorting and ordering
 */

/**
 * @brief Sort vertices in the set in ascending order
 * @param set Target vertex set
 * @return Error code
 */
sssp_error_t sssp_vertex_set_sort(sssp_vertex_set_t* set);

/**
 * @brief Sort vertices using custom comparison function
 * @param set Target vertex set
 * @param compare Comparison function
 * @param context Context for comparison function
 * @return Error code
 */
sssp_error_t sssp_vertex_set_sort_custom(sssp_vertex_set_t* set,
                                          int (*compare)(const void* a, const void* b, void* context),
                                          void* context);

/**
 * @brief Remove duplicate vertices from the set
 * @param set Target vertex set
 * @return Error code
 */
sssp_error_t sssp_vertex_set_unique(sssp_vertex_set_t* set);

/**
 * @brief Iterator for vertex sets
 */
typedef struct sssp_vertex_set_iterator {
    const sssp_vertex_set_t* set;
    vertex_count_t index;
} sssp_vertex_set_iterator_t;

/**
 * @brief Initialize iterator for vertex set
 * @param set Target vertex set
 * @param iter Iterator to initialize
 * @return Error code
 */
sssp_error_t sssp_vertex_set_iterator_init(const sssp_vertex_set_t* set,
                                            sssp_vertex_set_iterator_t* iter);

/**
 * @brief Get next vertex from iterator
 * @param iter Vertex set iterator
 * @param vertex_out Pointer to store vertex ID
 * @return true if vertex was retrieved, false if no more vertices
 */
bool sssp_vertex_set_iterator_next(sssp_vertex_set_iterator_t* iter,
                                   vertex_id_t* vertex_out);

/**
 * @brief Reset iterator to beginning
 * @param iter Vertex set iterator
 */
void sssp_vertex_set_iterator_reset(sssp_vertex_set_iterator_t* iter);

/**
 * @brief Debugging and visualization
 */

/**
 * @brief Print vertex set to stdout
 * @param set Target vertex set
 * @param max_vertices Maximum number of vertices to print (0 for all)
 */
void sssp_vertex_set_print(const sssp_vertex_set_t* set, vertex_count_t max_vertices);

/**
 * @brief Print vertex set statistics
 * @param set Target vertex set
 */
void sssp_vertex_set_print_stats(const sssp_vertex_set_t* set);

/**
 * @brief Validate vertex set integrity
 * @param set Target vertex set
 * @return true if set is valid, false if corrupted
 */
bool sssp_vertex_set_validate(const sssp_vertex_set_t* set);

/**
 * @brief Check if vertex set is in valid state
 * @param set Target vertex set
 * @return true if set is valid for operations
 */
bool sssp_vertex_set_is_valid(const sssp_vertex_set_t* set);

#ifdef __cplusplus
}
#endif

#endif // SSSP_VERTEX_SET_H
