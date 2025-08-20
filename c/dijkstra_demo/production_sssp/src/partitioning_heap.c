/**
 * @file partitioning_heap.c
 * @brief Implementation of partitioning heap as described in Lemma 3.3
 * 
 * @author Sambit Chakraborty
 * @date 21-08-2025
 * @version 1.0
 */

#include "partitioning_heap.h"
#include "sssp_common.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 * Create a new partitioning heap
 */
sssp_partitioning_heap_t* sssp_partitioning_heap_create(vertex_count_t max_vertices,
                                                         const sssp_allocator_t* allocator) {
    SSSP_LOG_DEBUG("Creating partitioning heap for %u vertices", max_vertices);
    
    if (max_vertices == 0) {
        SSSP_LOG_ERROR("Cannot create heap with 0 vertices");
        return NULL;
    }
    
    if (allocator == NULL) {
        allocator = &SSSP_DEFAULT_ALLOCATOR;
    }
    
    sssp_partitioning_heap_t* heap = sssp_alloc(allocator, sizeof(sssp_partitioning_heap_t));
    if (!heap) {
        SSSP_LOG_ERROR("Failed to allocate memory for partitioning heap");
        return NULL;
    }
    
    heap->max_vertices = max_vertices;
    heap->size = 0;
    heap->allocator = allocator;
    
    // Allocate heap array
    heap->elements = sssp_alloc(allocator, max_vertices * sizeof(sssp_heap_element_t));
    if (!heap->elements) {
        SSSP_LOG_ERROR("Failed to allocate heap elements array");
        sssp_free(allocator, heap);
        return NULL;
    }
    
    // Allocate position map for O(1) decrease-key operations
    heap->position = sssp_alloc(allocator, max_vertices * sizeof(vertex_count_t));
    if (!heap->position) {
        SSSP_LOG_ERROR("Failed to allocate position array");
        sssp_free(allocator, heap->elements);
        sssp_free(allocator, heap);
        return NULL;
    }
    
    // Initialize position map (INVALID_POSITION means not in heap)
    for (vertex_count_t i = 0; i < max_vertices; i++) {
        heap->position[i] = SSSP_INVALID_POSITION;
    }
    
    SSSP_LOG_DEBUG("Partitioning heap created successfully");
    return heap;
}

/**
 * Destroy a partitioning heap
 */
void sssp_partitioning_heap_destroy(sssp_partitioning_heap_t* heap) {
    if (!heap) return;
    
    SSSP_LOG_DEBUG("Destroying partitioning heap");
    
    const sssp_allocator_t* allocator = heap->allocator;
    
    sssp_free(allocator, heap->elements);
    sssp_free(allocator, heap->position);
    sssp_free(allocator, heap);
    
    SSSP_LOG_DEBUG("Partitioning heap destroyed successfully");
}

/**
 * Helper function to maintain heap property (min-heap)
 */
static void heapify_up(sssp_partitioning_heap_t* heap, vertex_count_t index) {
    while (index > 0) {
        vertex_count_t parent = (index - 1) / 2;
        
        if (heap->elements[index].distance >= heap->elements[parent].distance) {
            break;
        }
        
        // Swap with parent
        sssp_heap_element_t temp = heap->elements[index];
        heap->elements[index] = heap->elements[parent];
        heap->elements[parent] = temp;
        
        // Update position map
        heap->position[heap->elements[index].vertex] = index;
        heap->position[heap->elements[parent].vertex] = parent;
        
        index = parent;
    }
}

/**
 * Helper function to maintain heap property (min-heap)
 */
static void heapify_down(sssp_partitioning_heap_t* heap, vertex_count_t index) {
    while (true) {
        vertex_count_t smallest = index;
        vertex_count_t left = 2 * index + 1;
        vertex_count_t right = 2 * index + 2;
        
        if (left < heap->size && 
            heap->elements[left].distance < heap->elements[smallest].distance) {
            smallest = left;
        }
        
        if (right < heap->size && 
            heap->elements[right].distance < heap->elements[smallest].distance) {
            smallest = right;
        }
        
        if (smallest == index) {
            break;
        }
        
        // Swap with smallest child
        sssp_heap_element_t temp = heap->elements[index];
        heap->elements[index] = heap->elements[smallest];
        heap->elements[smallest] = temp;
        
        // Update position map
        heap->position[heap->elements[index].vertex] = index;
        heap->position[heap->elements[smallest].vertex] = smallest;
        
        index = smallest;
    }
}

/**
 * Insert a vertex with distance into the heap
 */
sssp_error_t sssp_partitioning_heap_insert(sssp_partitioning_heap_t* heap, 
                                            vertex_id_t vertex, distance_t distance) {
    if (!heap) {
        SSSP_LOG_ERROR("Heap is NULL");
        return SSSP_ERROR_INVALID_PARAMETER;
    }
    
    if (vertex >= heap->max_vertices) {
        SSSP_LOG_ERROR("Invalid vertex ID: %u (max=%u)", vertex, heap->max_vertices - 1);
        return SSSP_ERROR_INVALID_PARAMETER;
    }
    
    if (heap->size >= heap->max_vertices) {
        SSSP_LOG_ERROR("Heap is full");
        return SSSP_ERROR_OUT_OF_MEMORY;
    }
    
    if (heap->position[vertex] != SSSP_INVALID_POSITION) {
        SSSP_LOG_ERROR("Vertex %u is already in heap", vertex);
        return SSSP_ERROR_INVALID_PARAMETER;
    }
    
    SSSP_LOG_TRACE("Inserting vertex %u with distance %.2f", vertex, distance);
    
    // Insert at end of heap
    vertex_count_t index = heap->size;
    heap->elements[index].vertex = vertex;
    heap->elements[index].distance = distance;
    heap->position[vertex] = index;
    heap->size++;
    
    // Restore heap property
    heapify_up(heap, index);
    
    SSSP_LOG_TRACE("Vertex inserted successfully. Heap size: %u", heap->size);
    return SSSP_SUCCESS;
}

/**
 * Extract the minimum element from the heap
 */
sssp_error_t sssp_partitioning_heap_extract_min(sssp_partitioning_heap_t* heap, 
                                                 vertex_id_t* vertex, distance_t* distance) {
    if (!heap || !vertex || !distance) {
        SSSP_LOG_ERROR("Invalid parameters");
        return SSSP_ERROR_INVALID_PARAMETER;
    }
    
    if (heap->size == 0) {
        SSSP_LOG_ERROR("Heap is empty");
        return SSSP_ERROR_INVALID_PARAMETER;
    }
    
    // Extract minimum (root)
    *vertex = heap->elements[0].vertex;
    *distance = heap->elements[0].distance;
    
    SSSP_LOG_TRACE("Extracting min: vertex %u, distance %.2f", *vertex, *distance);
    
    // Mark as not in heap
    heap->position[*vertex] = SSSP_INVALID_POSITION;
    
    // Move last element to root
    heap->size--;
    if (heap->size > 0) {
        heap->elements[0] = heap->elements[heap->size];
        heap->position[heap->elements[0].vertex] = 0;
        
        // Restore heap property
        heapify_down(heap, 0);
    }
    
    SSSP_LOG_TRACE("Min extracted successfully. Heap size: %u", heap->size);
    return SSSP_SUCCESS;
}

/**
 * Decrease the key (distance) of a vertex in the heap
 */
sssp_error_t sssp_partitioning_heap_decrease_key(sssp_partitioning_heap_t* heap, 
                                                  vertex_id_t vertex, distance_t new_distance) {
    if (!heap) {
        SSSP_LOG_ERROR("Heap is NULL");
        return SSSP_ERROR_INVALID_PARAMETER;
    }
    
    if (vertex >= heap->max_vertices) {
        SSSP_LOG_ERROR("Invalid vertex ID: %u", vertex);
        return SSSP_ERROR_INVALID_PARAMETER;
    }
    
    vertex_count_t index = heap->position[vertex];
    if (index == SSSP_INVALID_POSITION) {
        SSSP_LOG_ERROR("Vertex %u is not in heap", vertex);
        return SSSP_ERROR_INVALID_PARAMETER;
    }
    
    if (new_distance >= heap->elements[index].distance) {
        SSSP_LOG_ERROR("New distance %.2f is not less than current distance %.2f", 
                       new_distance, heap->elements[index].distance);
        return SSSP_ERROR_INVALID_PARAMETER;
    }
    
    SSSP_LOG_TRACE("Decreasing key for vertex %u: %.2f -> %.2f", 
                   vertex, heap->elements[index].distance, new_distance);
    
    // Update distance
    heap->elements[index].distance = new_distance;
    
    // Restore heap property
    heapify_up(heap, index);
    
    SSSP_LOG_TRACE("Key decreased successfully");
    return SSSP_SUCCESS;
}

/**
 * Check if heap is empty
 */
bool sssp_partitioning_heap_is_empty(const sssp_partitioning_heap_t* heap) {
    return heap ? (heap->size == 0) : true;
}

/**
 * Get the size of the heap
 */
vertex_count_t sssp_partitioning_heap_size(const sssp_partitioning_heap_t* heap) {
    return heap ? heap->size : 0;
}

/**
 * Check if a vertex is in the heap
 */
bool sssp_partitioning_heap_contains(const sssp_partitioning_heap_t* heap, vertex_id_t vertex) {
    if (!heap || vertex >= heap->max_vertices) {
        return false;
    }
    
    return heap->position[vertex] != SSSP_INVALID_POSITION;
}

/**
 * Get the distance of a vertex in the heap
 */
distance_t sssp_partitioning_heap_get_distance(const sssp_partitioning_heap_t* heap, 
                                                vertex_id_t vertex) {
    if (!heap || vertex >= heap->max_vertices) {
        return SSSP_INFINITY;
    }
    
    vertex_count_t index = heap->position[vertex];
    if (index == SSSP_INVALID_POSITION) {
        return SSSP_INFINITY;
    }
    
    return heap->elements[index].distance;
}

/**
 * Clear the heap (remove all elements)
 */
sssp_error_t sssp_partitioning_heap_clear(sssp_partitioning_heap_t* heap) {
    if (!heap) return SSSP_ERROR_INVALID_ARGUMENT;
    
    SSSP_LOG_DEBUG("Clearing partitioning heap");
    
    // Reset position map
    for (vertex_count_t i = 0; i < heap->size; i++) {
        heap->position[heap->elements[i].vertex] = SSSP_INVALID_POSITION;
    }
    
    heap->size = 0;
    
    SSSP_LOG_DEBUG("Partitioning heap cleared");
    
    return SSSP_SUCCESS;
}

/**
 * Validate heap properties
 */
bool sssp_partitioning_heap_is_valid(const sssp_partitioning_heap_t* heap) {
    if (!heap) {
        SSSP_LOG_ERROR("Heap is NULL");
        return false;
    }
    
    if (heap->size > heap->max_vertices) {
        SSSP_LOG_ERROR("Heap size %u exceeds maximum %u", heap->size, heap->max_vertices);
        return false;
    }
    
    // Check heap property
    for (vertex_count_t i = 0; i < heap->size; i++) {
        vertex_count_t left = 2 * i + 1;
        vertex_count_t right = 2 * i + 2;
        
        if (left < heap->size && 
            heap->elements[i].distance > heap->elements[left].distance) {
            SSSP_LOG_ERROR("Heap property violated at index %u (left child)", i);
            return false;
        }
        
        if (right < heap->size && 
            heap->elements[i].distance > heap->elements[right].distance) {
            SSSP_LOG_ERROR("Heap property violated at index %u (right child)", i);
            return false;
        }
        
        // Check position map consistency
        vertex_id_t vertex = heap->elements[i].vertex;
        if (vertex >= heap->max_vertices) {
            SSSP_LOG_ERROR("Invalid vertex ID %u at index %u", vertex, i);
            return false;
        }
        
        if (heap->position[vertex] != i) {
            SSSP_LOG_ERROR("Position map inconsistency: vertex %u at index %u, but position[%u]=%u", 
                           vertex, i, vertex, heap->position[vertex]);
            return false;
        }
    }
    
    // Check that vertices not in heap have INVALID_POSITION
    for (vertex_count_t v = 0; v < heap->max_vertices; v++) {
        vertex_count_t pos = heap->position[v];
        if (pos != SSSP_INVALID_POSITION) {
            if (pos >= heap->size) {
                SSSP_LOG_ERROR("Vertex %u has invalid position %u (heap size=%u)", 
                               v, pos, heap->size);
                return false;
            }
            if (heap->elements[pos].vertex != v) {
                SSSP_LOG_ERROR("Position map inconsistency: position[%u]=%u, but elements[%u].vertex=%u", 
                               v, pos, pos, heap->elements[pos].vertex);
                return false;
            }
        }
    }
    
    return true;
}

/**
 * Partition vertices based on distance threshold (Lemma 3.3)
 * Returns vertices with distance <= threshold
 */
sssp_error_t sssp_partitioning_heap_partition(sssp_partitioning_heap_t* heap, 
                                               distance_t threshold,
                                               sssp_vertex_set_t* close_vertices) {
    if (!heap || !close_vertices) {
        SSSP_LOG_ERROR("Invalid parameters");
        return SSSP_ERROR_INVALID_PARAMETER;
    }
    
    SSSP_LOG_DEBUG("Partitioning heap with threshold %.2f", threshold);
    
    sssp_vertex_set_clear(close_vertices);
    
    // Extract all vertices with distance <= threshold
    vertex_count_t extracted = 0;
    while (!sssp_partitioning_heap_is_empty(heap)) {
        // Peek at minimum
        if (heap->elements[0].distance > threshold) {
            break;
        }
        
        // Extract minimum
        vertex_id_t vertex;
        distance_t distance;
        sssp_error_t result = sssp_partitioning_heap_extract_min(heap, &vertex, &distance);
        if (result != SSSP_SUCCESS) {
            SSSP_LOG_ERROR("Failed to extract minimum from heap");
            return result;
        }
        
        // Add to close vertices set
        result = sssp_vertex_set_add(close_vertices, vertex);
        if (result != SSSP_SUCCESS) {
            SSSP_LOG_ERROR("Failed to add vertex %u to close set", vertex);
            return result;
        }
        
        extracted++;
    }
    
    SSSP_LOG_DEBUG("Partitioning complete: extracted %u vertices", extracted);
    return SSSP_SUCCESS;
}
