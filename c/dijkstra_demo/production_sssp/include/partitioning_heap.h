/**
 * @file partitioning_heap.h
 * @brief Partitioning heap data structure (Lemma 3.3 from the paper)
 * 
 * This file implements the PartitioningHeap data structure as described in
 * Lemma 3.3 of the research paper. The heap supports efficient batch operations
 * and maintains elements in sorted order for the SSSP algorithm.
 * 
 * @author Sambit Chakraborty
 * @date 21-08-2025
 * @version 1.0
 */

#ifndef SSSP_PARTITIONING_HEAP_H
#define SSSP_PARTITIONING_HEAP_H

#include "sssp_common.h"
#include "vertex_set.h"

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct sssp_partitioning_heap sssp_partitioning_heap_t;
typedef struct sssp_heap_element sssp_heap_element_t;
typedef struct sssp_heap_config sssp_heap_config_t;
typedef struct sssp_heap_block sssp_heap_block_t;
typedef struct sssp_heap_item sssp_heap_item_t;

/**
 * @brief Heap configuration structure
 */
struct sssp_heap_config {
    vertex_count_t block_size;          ///< Size of each heap block
    weight_t threshold;                 ///< Partitioning threshold
    bool optimize_for_dense;            ///< Optimization flag for dense graphs
};

/**
 * @brief Heap block structure
 */
struct sssp_heap_block {
    sssp_heap_element_t* elements;      ///< Elements in this block
    vertex_count_t size;                ///< Current size
    vertex_count_t capacity;            ///< Maximum capacity
};

/**
 * @brief Heap item (alias for element)
 */
struct sssp_heap_item {
    vertex_id_t vertex;                 ///< Vertex identifier
    distance_t distance;                ///< Distance value
};

/**
 * @brief Individual heap element
 */
struct sssp_heap_element {
    vertex_id_t vertex;                 ///< Vertex identifier
    distance_t distance;                ///< Distance value
};

/**
 * @brief Main partitioning heap structure
 */
struct sssp_partitioning_heap {
    vertex_count_t max_vertices;        ///< Maximum number of vertices
    vertex_count_t size;                ///< Current number of elements in heap
    const sssp_allocator_t* allocator;  ///< Memory allocator
    
    sssp_heap_element_t* elements;      ///< Array of heap elements
    vertex_count_t* position;           ///< Position map for O(1) decrease-key
};

/**
 * @brief Heap creation and destruction
 */

/**
 * @brief Create a new partitioning heap
 * @param max_vertices Maximum number of vertices
 * @param allocator Memory allocator (can be NULL for default)
 * @return New heap instance or NULL on failure
 */
sssp_partitioning_heap_t* sssp_partitioning_heap_create(vertex_count_t max_vertices,
                                                         const sssp_allocator_t* allocator);
/**
 * @brief Destroy a partitioning heap
 * @param heap Heap to destroy
 */
void sssp_partitioning_heap_destroy(sssp_partitioning_heap_t* heap);

/**
 * @brief Insert a vertex with distance into the heap
 * @param heap Heap instance
 * @param vertex Vertex to insert
 * @param distance Distance value
 * @return Success or error code
 */
sssp_error_t sssp_partitioning_heap_insert(sssp_partitioning_heap_t* heap, 
                                            vertex_id_t vertex, distance_t distance);

/**
 * @brief Extract minimum element from the heap
 * @param heap Heap instance
 * @param vertex Output vertex
 * @param distance Output distance
 * @return Success or error code
 */
sssp_error_t sssp_partitioning_heap_extract_min(sssp_partitioning_heap_t* heap, 
                                                 vertex_id_t* vertex, distance_t* distance);

/**
 * @brief Decrease key of a vertex in the heap
 * @param heap Heap instance
 * @param vertex Vertex to update
 * @param new_distance New distance value
 * @return Success or error code
 */
sssp_error_t sssp_partitioning_heap_decrease_key(sssp_partitioning_heap_t* heap, 
                                                  vertex_id_t vertex, distance_t new_distance);

/**
 * @brief Check if heap is empty
 * @param heap Heap instance
 * @return True if empty
 */
bool sssp_partitioning_heap_is_empty(const sssp_partitioning_heap_t* heap);

/**
 * @brief Get current size of heap
 * @param heap Heap instance
 * @return Number of elements
 */
vertex_count_t sssp_partitioning_heap_size(const sssp_partitioning_heap_t* heap);

/**
 * @brief Check if vertex is in heap
 * @param heap Heap instance
 * @param vertex Vertex to check
 * @return True if vertex is in heap
 */
bool sssp_partitioning_heap_contains(const sssp_partitioning_heap_t* heap, vertex_id_t vertex);

/**
 * @brief Get distance of vertex in heap
 * @param heap Heap instance
 * @param vertex Vertex to query
 * @return Distance or INFINITY if not in heap
 */
distance_t sssp_partitioning_heap_get_distance(const sssp_partitioning_heap_t* heap, 
                                                vertex_id_t vertex);

/**
 * @brief Clear all elements from heap
 * @param heap Heap instance
 * @return Error code
 */
sssp_error_t sssp_partitioning_heap_clear(sssp_partitioning_heap_t* heap);

/**
 * @brief Validate heap properties
 * @param heap Heap instance
 * @return True if valid
 */
bool sssp_partitioning_heap_is_valid(const sssp_partitioning_heap_t* heap);

/**
 * @brief Partition vertices based on distance threshold (Lemma 3.3)
 * @param heap Heap instance
 * @param threshold Distance threshold
 * @param close_vertices Output set for vertices with distance <= threshold
 * @return Success or error code
 */
sssp_error_t sssp_partitioning_heap_partition(sssp_partitioning_heap_t* heap, 
                                               distance_t threshold,
                                               sssp_vertex_set_t* close_vertices);

/**
 * @brief Destroy a partitioning heap and free all memory
 * @param heap Heap to destroy
 */
void sssp_partitioning_heap_destroy(sssp_partitioning_heap_t* heap);

/**
 * @brief Heap operations (as defined in Lemma 3.3)
 */

/**
 * @brief Initialize heap with given parameters
 * @param block_size Maximum items per block (M parameter)
 * @param threshold Value threshold (B parameter)
 * @param allocator Memory allocator (NULL for default)
 * @return Pointer to initialized heap or NULL on failure
 */
sssp_partitioning_heap_t* sssp_heap_initialize(vertex_count_t block_size,
                                                weight_t threshold,
                                                const sssp_allocator_t* allocator);

/**
 * @brief Insert a single item into the heap
 * @param heap Target heap
 * @param vertex Vertex identifier
 * @param value Associated value
 * @return Error code
 */
sssp_error_t sssp_heap_insert(sssp_partitioning_heap_t* heap,
                               vertex_id_t vertex,
                               weight_t value);

/**
 * @brief Batch prepend operation for adding multiple items efficiently
 * @param heap Target heap
 * @param vertices Vertex set to add
 * @param values Array of values corresponding to vertices
 * @return Error code
 */
sssp_error_t sssp_heap_batch_prepend(sssp_partitioning_heap_t* heap,
                                      const sssp_vertex_set_t* vertices,
                                      const weight_t* values);

/**
 * @brief Pull the M smallest items from the heap
 * @param heap Target heap
 * @param output_set Vertex set to store pulled vertices
 * @param B_prime_out Pointer to store the new threshold value
 * @return Error code
 */
sssp_error_t sssp_heap_pull(sssp_partitioning_heap_t* heap,
                             sssp_vertex_set_t* output_set,
                             weight_t* B_prime_out);

/**
 * @brief Check if the heap is empty
 * @param heap Target heap
 * @return true if heap is empty
 */
bool sssp_heap_is_empty(const sssp_partitioning_heap_t* heap);

/**
 * @brief Get the number of items currently in the heap
 * @param heap Target heap
 * @return Number of items in heap
 */
vertex_count_t sssp_heap_size(const sssp_partitioning_heap_t* heap);

/**
 * @brief Advanced operations
 */

/**
 * @brief Update threshold value for the heap
 * @param heap Target heap
 * @param new_threshold New threshold value
 * @return Error code
 */
sssp_error_t sssp_heap_update_threshold(sssp_partitioning_heap_t* heap,
                                         weight_t new_threshold);

/**
 * @brief Get minimum value in the heap without removing it
 * @param heap Target heap
 * @param min_value_out Pointer to store minimum value
 * @return Error code
 */
sssp_error_t sssp_heap_peek_min(const sssp_partitioning_heap_t* heap,
                                 weight_t* min_value_out);

/**
 * @brief Remove all items with values >= threshold
 * @param heap Target heap
 * @param threshold Value threshold
 * @return Error code
 */
sssp_error_t sssp_heap_prune(sssp_partitioning_heap_t* heap,
                              weight_t threshold);

/**
 * @brief Memory management and optimization
 */

/**
 * @brief Compact heap memory by merging partially filled blocks
 * @param heap Target heap
 * @return Error code
 */
sssp_error_t sssp_heap_compact(sssp_partitioning_heap_t* heap);

/**
 * @brief Reserve memory for expected number of items
 * @param heap Target heap
 * @param expected_items Expected number of items
 * @return Error code
 */
sssp_error_t sssp_heap_reserve(sssp_partitioning_heap_t* heap,
                                vertex_count_t expected_items);

/**
 * @brief Get memory usage statistics for the heap
 * @param heap Target heap
 * @return Memory statistics
 */
sssp_memory_stats_t sssp_heap_memory_stats(const sssp_partitioning_heap_t* heap);

/**
 * @brief Debugging and validation
 */

/**
 * @brief Validate heap structure integrity
 * @param heap Target heap
 * @return true if heap is valid, false if corrupted
 */
bool sssp_heap_validate(const sssp_partitioning_heap_t* heap);

/**
 * @brief Print heap statistics to stdout
 * @param heap Target heap
 */
void sssp_heap_print_stats(const sssp_partitioning_heap_t* heap);

/**
 * @brief Print detailed heap structure for debugging
 * @param heap Target heap
 * @param max_items Maximum number of items to print per block
 */
void sssp_heap_print_structure(const sssp_partitioning_heap_t* heap,
                                vertex_count_t max_items);

/**
 * @brief Configuration helpers
 */

/**
 * @brief Create default heap configuration
 * @param block_size Block size (0 for default)
 * @param threshold Initial threshold (SSSP_INFINITY for no limit)
 * @return Default configuration structure
 */
sssp_heap_config_t sssp_heap_config_default(vertex_count_t block_size,
                                             weight_t threshold);

/**
 * @brief Create optimized configuration based on graph size
 * @param num_vertices Number of vertices in graph
 * @param expected_density Expected edge density
 * @return Optimized configuration structure
 */
sssp_heap_config_t sssp_heap_config_optimized(vertex_count_t num_vertices,
                                               double expected_density);

/**
 * @brief Iterator for heap items
 */
typedef struct sssp_heap_iterator {
    const sssp_partitioning_heap_t* heap;
    const sssp_heap_block_t* current_block;
    vertex_count_t current_index;
    bool iterating_d0;
} sssp_heap_iterator_t;

/**
 * @brief Initialize iterator for heap
 * @param heap Target heap
 * @param iter Iterator to initialize
 * @return Error code
 */
sssp_error_t sssp_heap_iterator_init(const sssp_partitioning_heap_t* heap,
                                      sssp_heap_iterator_t* iter);

/**
 * @brief Get next item from iterator
 * @param iter Heap iterator
 * @param item_out Pointer to store item
 * @return true if item was retrieved, false if no more items
 */
bool sssp_heap_iterator_next(sssp_heap_iterator_t* iter,
                              const sssp_heap_item_t** item_out);

#ifdef __cplusplus
}
#endif

#endif // SSSP_PARTITIONING_HEAP_H
