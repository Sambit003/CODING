/**
 * @file find_pivots.c
 * @brief Implementation of Algorithm 1 (FINDPIVOTS) from the research paper
 * 
 * @author Sambit Chakraborty
 * @date 21-08-2025
 * @version 1.0
 */

#include "find_pivots.h"
#include "partitioning_heap.h"
#include "sssp_common.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 * Create a new pivot finder
 */
sssp_pivot_finder_t* sssp_pivot_finder_create(vertex_count_t max_vertices,
                                               const sssp_allocator_t* allocator) {
    SSSP_LOG_DEBUG("Creating pivot finder for %u vertices", max_vertices);
    
    if (max_vertices == 0) {
        SSSP_LOG_ERROR("Cannot create pivot finder with 0 vertices");
        return NULL;
    }
    
    if (allocator == NULL) {
        allocator = &SSSP_DEFAULT_ALLOCATOR;
    }
    
    sssp_pivot_finder_t* finder = sssp_alloc(allocator, sizeof(sssp_pivot_finder_t));
    if (!finder) {
        SSSP_LOG_ERROR("Failed to allocate memory for pivot finder");
        return NULL;
    }
    
    finder->max_vertices = max_vertices;
    finder->allocator = allocator;
    
    // Create vertex set for candidate pivots
    finder->candidates = sssp_vertex_set_create(max_vertices, allocator);
    if (!finder->candidates) {
        SSSP_LOG_ERROR("Failed to create candidate vertex set");
        sssp_free(allocator, finder);
        return NULL;
    }
    
    // Create result arrays
    finder->pivots = sssp_alloc(allocator, max_vertices * sizeof(vertex_id_t));
    if (!finder->pivots) {
        SSSP_LOG_ERROR("Failed to allocate pivots array");
        sssp_vertex_set_destroy(finder->candidates);
        sssp_free(allocator, finder);
        return NULL;
    }
    
    finder->distances = sssp_alloc(allocator, max_vertices * sizeof(distance_t));
    if (!finder->distances) {
        SSSP_LOG_ERROR("Failed to allocate distances array");
        sssp_free(allocator, finder->pivots);
        sssp_vertex_set_destroy(finder->candidates);
        sssp_free(allocator, finder);
        return NULL;
    }
    
    // Initialize working arrays
    finder->vertex_distances = sssp_alloc(allocator, max_vertices * sizeof(distance_t));
    if (!finder->vertex_distances) {
        SSSP_LOG_ERROR("Failed to allocate vertex distances array");
        sssp_free(allocator, finder->distances);
        sssp_free(allocator, finder->pivots);
        sssp_vertex_set_destroy(finder->candidates);
        sssp_free(allocator, finder);
        return NULL;
    }
    
    finder->visited = sssp_alloc(allocator, max_vertices * sizeof(bool));
    if (!finder->visited) {
        SSSP_LOG_ERROR("Failed to allocate visited array");
        sssp_free(allocator, finder->vertex_distances);
        sssp_free(allocator, finder->distances);
        sssp_free(allocator, finder->pivots);
        sssp_vertex_set_destroy(finder->candidates);
        sssp_free(allocator, finder);
        return NULL;
    }
    
    // Initialize arrays
    for (vertex_count_t i = 0; i < max_vertices; i++) {
        finder->vertex_distances[i] = SSSP_INFINITY;
        finder->visited[i] = false;
    }
    
    finder->num_pivots = 0;
    
    SSSP_LOG_DEBUG("Pivot finder created successfully");
    return finder;
}

/**
 * Destroy a pivot finder
 */
void sssp_pivot_finder_destroy(sssp_pivot_finder_t* finder) {
    if (!finder) return;
    
    SSSP_LOG_DEBUG("Destroying pivot finder");
    
    const sssp_allocator_t* allocator = finder->allocator;
    
    sssp_vertex_set_destroy(finder->candidates);
    sssp_free(allocator, finder->pivots);
    sssp_free(allocator, finder->distances);
    sssp_free(allocator, finder->vertex_distances);
    sssp_free(allocator, finder->visited);
    sssp_free(allocator, finder);
    
    SSSP_LOG_DEBUG("Pivot finder destroyed successfully");
}

/**
 * Helper function to run Dijkstra from a single source
 */
static distance_t run_single_source_dijkstra(const sssp_graph_t* graph, vertex_id_t source,
                                              distance_t* distances, bool* visited,
                                              distance_t max_distance) {
    // Reset arrays
    vertex_count_t num_vertices = sssp_graph_get_vertex_count(graph);
    for (vertex_count_t i = 0; i < num_vertices; i++) {
        distances[i] = SSSP_INFINITY;
        visited[i] = false;
    }
    
    // Create temporary heap for Dijkstra
    sssp_partitioning_heap_t* heap = sssp_partitioning_heap_create(num_vertices, NULL);
    if (!heap) {
        SSSP_LOG_ERROR("Failed to create heap for Dijkstra");
        return SSSP_INFINITY;
    }
    
    // Initialize source
    distances[source] = 0.0;
    sssp_partitioning_heap_insert(heap, source, 0.0);
    
    distance_t max_reached = 0.0;
    
    // Main Dijkstra loop
    while (!sssp_partitioning_heap_is_empty(heap)) {
        vertex_id_t u;
        distance_t dist_u;
        
        if (sssp_partitioning_heap_extract_min(heap, &u, &dist_u) != SSSP_SUCCESS) {
            break;
        }
        
        if (dist_u > max_distance) {
            break;
        }
        
        visited[u] = true;
        max_reached = dist_u;
        
        // Process all neighbors
        const sssp_adj_list_t* adj_list = sssp_graph_get_adj_list(graph, u);
        if (adj_list) {
            sssp_edge_node_t* edge = adj_list->head;
            while (edge) {
                vertex_id_t v = edge->to;
                distance_t new_dist = dist_u + edge->weight;
                
                if (new_dist < distances[v]) {
                    if (distances[v] == SSSP_INFINITY) {
                        // First time seeing this vertex
                        distances[v] = new_dist;
                        sssp_partitioning_heap_insert(heap, v, new_dist);
                    } else {
                        // Update existing distance
                        distances[v] = new_dist;
                        sssp_partitioning_heap_decrease_key(heap, v, new_dist);
                    }
                }
                
                edge = edge->next;
            }
        }
    }
    
    sssp_partitioning_heap_destroy(heap);
    return max_reached;
}

/**
 * Compute the bottleneck distance for a set of vertices
 * This is the maximum shortest path distance from any vertex in the set to any other vertex
 */
static distance_t compute_bottleneck_distance(const sssp_graph_t* graph,
                                               const sssp_vertex_set_t* vertex_set,
                                               distance_t* work_distances, bool* work_visited) {
    distance_t max_bottleneck = 0.0;
    
    // For each vertex in the set, run Dijkstra and find max distance to other vertices in set
    for (vertex_count_t i = 0; i < sssp_vertex_set_size(vertex_set); i++) {
        vertex_id_t source = sssp_vertex_set_get_vertex(vertex_set, i);
        
        distance_t max_dist = run_single_source_dijkstra(graph, source, work_distances, 
                                                          work_visited, SSSP_INFINITY);
        
        // Find maximum distance to other vertices in the set
        for (vertex_count_t j = 0; j < sssp_vertex_set_size(vertex_set); j++) {
            vertex_id_t target = sssp_vertex_set_get_vertex(vertex_set, j);
            if (source != target && work_distances[target] > max_bottleneck) {
                max_bottleneck = work_distances[target];
            }
        }
    }
    
    return max_bottleneck;
}

/**
 * Find the vertex that minimizes the maximum distance to all other vertices in the set
 */
static vertex_id_t find_best_pivot_candidate(const sssp_graph_t* graph,
                                              const sssp_vertex_set_t* vertex_set,
                                              distance_t* work_distances, bool* work_visited,
                                              distance_t* best_max_distance) {
    vertex_id_t best_pivot = SSSP_INVALID_VERTEX;
    *best_max_distance = SSSP_INFINITY;
    
    for (vertex_count_t i = 0; i < sssp_vertex_set_size(vertex_set); i++) {
        vertex_id_t candidate = sssp_vertex_set_get_vertex(vertex_set, i);
        
        run_single_source_dijkstra(graph, candidate, work_distances, work_visited, SSSP_INFINITY);
        
        // Find maximum distance to any vertex in the set
        distance_t max_dist = 0.0;
        for (vertex_count_t j = 0; j < sssp_vertex_set_size(vertex_set); j++) {
            vertex_id_t target = sssp_vertex_set_get_vertex(vertex_set, j);
            if (candidate != target && work_distances[target] > max_dist) {
                max_dist = work_distances[target];
            }
        }
        
        if (max_dist < *best_max_distance) {
            *best_max_distance = max_dist;
            best_pivot = candidate;
        }
    }
    
    return best_pivot;
}

/**
 * Implementation of Algorithm 1 (FINDPIVOTS) from the research paper
 * This is the correct signature matching the header file
 */
sssp_error_t sssp_find_pivots(const sssp_graph_t* graph,
                               weight_t threshold,
                               const sssp_vertex_set_t* source_set,
                               vertex_count_t k,
                               const sssp_find_pivots_config_t* config,
                               sssp_find_pivots_result_t* result) {
    if (!graph || !source_set || !result) {
        SSSP_LOG_ERROR("Invalid parameters");
        return SSSP_ERROR_INVALID_PARAMETER;
    }
    
    // Use default config if none provided
    sssp_find_pivots_config_t default_config;
    if (!config) {
        default_config = sssp_find_pivots_config_default(NULL);
        config = &default_config;
    }
    
    vertex_count_t set_size = sssp_vertex_set_size(source_set);
    if (set_size == 0) {
        SSSP_LOG_DEBUG("Empty vertex set, no pivots needed");
        sssp_vertex_set_clear(result->pivots);
        sssp_vertex_set_clear(result->witnesses);
        result->layers_processed = 0;
        result->relaxations_performed = 0;
        return SSSP_SUCCESS;
    }
    
    SSSP_LOG_DEBUG("Finding pivots for set of %u vertices, threshold: %.2f, k: %u", 
                   set_size, threshold, k);
    
    // Initialize result structure
    sssp_vertex_set_clear(result->pivots);
    sssp_vertex_set_clear(result->witnesses);
    result->layers_processed = 0;
    result->relaxations_performed = 0;
    
    // Create temporary working structures
    vertex_count_t num_vertices = sssp_graph_get_vertex_count(graph);
    distance_t* work_distances = sssp_alloc(config->allocator, num_vertices * sizeof(distance_t));
    bool* work_visited = sssp_alloc(config->allocator, num_vertices * sizeof(bool));
    sssp_vertex_set_t* candidates = sssp_vertex_set_create(num_vertices, config->allocator);
    
    if (!work_distances || !work_visited || !candidates) {
        SSSP_LOG_ERROR("Failed to allocate working memory");
        if (work_distances) sssp_free(config->allocator, work_distances);
        if (work_visited) sssp_free(config->allocator, work_visited);
        if (candidates) sssp_vertex_set_destroy(candidates);
        return SSSP_ERROR_OUT_OF_MEMORY;
    }
    
    // Initialize candidate set with all vertices from source set
    for (vertex_count_t i = 0; i < set_size; i++) {
        vertex_id_t v = sssp_vertex_set_get_vertex(source_set, i);
        sssp_vertex_set_add(candidates, v);
    }
    
    // Main algorithm loop
    while (sssp_vertex_set_size(candidates) > 0) {
        // Check if current diameter is acceptable
        distance_t current_diameter = compute_bottleneck_distance(graph, candidates,
                                                                  work_distances, work_visited);
        
        SSSP_LOG_TRACE("Current diameter: %.2f, threshold: %.2f", current_diameter, threshold);
        
        if (current_diameter <= threshold) {
            SSSP_LOG_DEBUG("Target threshold achieved");
            break;
        }
        
        // Find the best pivot (vertex that minimizes maximum distance to others)
        distance_t best_max_distance;
        vertex_id_t pivot = find_best_pivot_candidate(graph, candidates,
                                                      work_distances, work_visited,
                                                      &best_max_distance);
        
        if (pivot == SSSP_INVALID_VERTEX) {
            SSSP_LOG_ERROR("Failed to find valid pivot");
            sssp_free(config->allocator, work_distances);
            sssp_free(config->allocator, work_visited);
            sssp_vertex_set_destroy(candidates);
            return SSSP_ERROR_ALGORITHM;
        }
        
        // Add pivot to result
        sssp_vertex_set_add(result->pivots, pivot);
        
        SSSP_LOG_TRACE("Added pivot %u with max distance %.2f", pivot, best_max_distance);
        
        // Run Dijkstra from the pivot to determine which vertices to remove
        run_single_source_dijkstra(graph, pivot, work_distances, work_visited, threshold);
        
        // Remove vertices that are within threshold distance of the pivot
        sssp_vertex_set_t* to_remove = sssp_vertex_set_create(num_vertices, config->allocator);
        if (!to_remove) {
            SSSP_LOG_ERROR("Failed to create temporary vertex set");
            sssp_free(config->allocator, work_distances);
            sssp_free(config->allocator, work_visited);
            sssp_vertex_set_destroy(candidates);
            return SSSP_ERROR_OUT_OF_MEMORY;
        }
        
        for (vertex_count_t i = 0; i < sssp_vertex_set_size(candidates); i++) {
            vertex_id_t v = sssp_vertex_set_get_vertex(candidates, i);
            if (work_distances[v] <= threshold) {
                sssp_vertex_set_add(to_remove, v);
            }
        }
        
        // Remove the vertices from candidates
        for (vertex_count_t i = 0; i < sssp_vertex_set_size(to_remove); i++) {
            vertex_id_t v = sssp_vertex_set_get_vertex(to_remove, i);
            sssp_vertex_set_remove(candidates, v);
        }
        
        sssp_vertex_set_destroy(to_remove);
        
        SSSP_LOG_TRACE("Removed vertices within distance %.2f of pivot %u. Remaining: %u", 
                       threshold, pivot, sssp_vertex_set_size(candidates));
        
        // Safety check to prevent infinite loops
        if (sssp_vertex_set_size(result->pivots) > set_size) {
            SSSP_LOG_ERROR("Too many pivots generated (possible infinite loop)");
            sssp_free(config->allocator, work_distances);
            sssp_free(config->allocator, work_visited);
            sssp_vertex_set_destroy(candidates);
            return SSSP_ERROR_ALGORITHM;
        }
        
        // Early termination based on k parameter
        if (k > 0 && sssp_vertex_set_size(result->pivots) >= k) {
            SSSP_LOG_DEBUG("Reached maximum pivot count k=%u", k);
            break;
        }
        
        result->layers_processed++;
    }
    
    // Store remaining candidates as witnesses
    for (vertex_count_t i = 0; i < sssp_vertex_set_size(candidates); i++) {
        vertex_id_t v = sssp_vertex_set_get_vertex(candidates, i);
        sssp_vertex_set_add(result->witnesses, v);
    }
    
    // Clean up
    sssp_free(config->allocator, work_distances);
    sssp_free(config->allocator, work_visited);
    sssp_vertex_set_destroy(candidates);
    
    SSSP_LOG_INFO("FINDPIVOTS completed: %u pivots found, %u witnesses", 
                  sssp_vertex_set_size(result->pivots), sssp_vertex_set_size(result->witnesses));
    return SSSP_SUCCESS;
}

// Remove the old function with incorrect signature and add utility function for backward compatibility
/**
 * Utility function for backward compatibility with pivot_finder_t
 */
sssp_error_t sssp_find_pivots_simple(sssp_pivot_finder_t* finder, const sssp_graph_t* graph,
                                      const sssp_vertex_set_t* source_set,
                                      distance_t target_diameter) {
    // Create config and result structures
    sssp_find_pivots_config_t config = sssp_find_pivots_config_default(finder->allocator);
    sssp_find_pivots_result_t* result = sssp_find_pivots_result_create(finder->allocator);
    
    if (!result) {
        return SSSP_ERROR_OUT_OF_MEMORY;
    }
    
    // Compute k parameter
    vertex_count_t k = (vertex_count_t)log((double)(sssp_vertex_set_size(source_set) + 1)) + 1;
    if (k < 1) k = 1;
    
    // Call the main function
    sssp_error_t error = sssp_find_pivots(graph, target_diameter, source_set, k, &config, result);
    
    if (error == SSSP_SUCCESS) {
        // Copy results to finder structure
        sssp_pivot_finder_clear(finder);
        vertex_count_t num_pivots = sssp_vertex_set_size(result->pivots);
        
        for (vertex_count_t i = 0; i < num_pivots && i < finder->max_vertices; i++) {
            vertex_id_t pivot = sssp_vertex_set_get_vertex(result->pivots, i);
            finder->pivots[finder->num_pivots] = pivot;
            finder->distances[finder->num_pivots] = 0.0; // Distance not available in this context
            finder->num_pivots++;
        }
    }
    
    sssp_find_pivots_result_destroy(result);
    return error;
}

/**
 * Clear pivot finder state
 */
void sssp_pivot_finder_clear(sssp_pivot_finder_t* finder) {
    if (!finder) return;
    
    finder->num_pivots = 0;
    sssp_vertex_set_clear(finder->candidates);
    
    // Reset working arrays
    for (vertex_count_t i = 0; i < finder->max_vertices; i++) {
        finder->vertex_distances[i] = SSSP_INFINITY;
        finder->visited[i] = false;
    }
}

/**
 * Create default FINDPIVOTS configuration
 */
sssp_find_pivots_config_t sssp_find_pivots_config_default(const sssp_allocator_t* allocator) {
    sssp_find_pivots_config_t config;
    config.max_layers = 1000;
    config.use_early_termination = true;
    config.allocator = allocator ? allocator : sssp_default_allocator();
    return config;
}

/**
 * Create FINDPIVOTS result structure
 */
sssp_find_pivots_result_t* sssp_find_pivots_result_create(const sssp_allocator_t* allocator) {
    if (!allocator) allocator = sssp_default_allocator();
    
    sssp_find_pivots_result_t* result = sssp_alloc(allocator, sizeof(sssp_find_pivots_result_t));
    if (!result) {
        SSSP_LOG_ERROR("Failed to allocate memory for find_pivots result");
        return NULL;
    }
    
    result->pivots = sssp_vertex_set_create(0, allocator);
    result->witnesses = sssp_vertex_set_create(0, allocator);
    
    if (!result->pivots || !result->witnesses) {
        SSSP_LOG_ERROR("Failed to create vertex sets for find_pivots result");
        if (result->pivots) sssp_vertex_set_destroy(result->pivots);
        if (result->witnesses) sssp_vertex_set_destroy(result->witnesses);
        sssp_free(allocator, result);
        return NULL;
    }
    
    result->layers_processed = 0;
    result->relaxations_performed = 0;
    result->execution_time_ms = 0.0;
    
    return result;
}

/**
 * Destroy FINDPIVOTS result and free memory
 */
void sssp_find_pivots_result_destroy(sssp_find_pivots_result_t* result) {
    if (!result) return;
    
    const sssp_allocator_t* allocator = NULL;
    if (result->pivots) {
        allocator = result->pivots->allocator;
        sssp_vertex_set_destroy(result->pivots);
    }
    if (result->witnesses) {
        if (!allocator && result->witnesses) {
            allocator = result->witnesses->allocator;
        }
        sssp_vertex_set_destroy(result->witnesses);
    }
    
    if (!allocator) allocator = sssp_default_allocator();
    sssp_free(allocator, result);
}