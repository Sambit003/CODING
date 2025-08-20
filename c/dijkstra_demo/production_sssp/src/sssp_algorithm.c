/**
 * @file sssp_algorithm.c
 * @brief Implementation of Algorithm 3 (bounded multi-source shortest paths) from the research paper
 * 
 * @author Sambit Chakraborty
 * @date 21-08-2025
 * @version 1.0
 */

#include "sssp_algorithm.h"
#include "sssp_common.h"
#include "partitioning_heap.h"
#include "find_pivots.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// Forward declarations for internal functions
static sssp_solver_t* sssp_solver_create(vertex_count_t max_vertices, const sssp_allocator_t* allocator);
static void sssp_solver_destroy(sssp_solver_t* solver);
static sssp_error_t initialize_sources(sssp_solver_t* solver, const vertex_id_t* sources, vertex_count_t num_sources);
static sssp_error_t run_standard_dijkstra(sssp_solver_t* solver, const sssp_graph_t* graph, distance_t max_distance);

/**
 * Create a new SSSP solver
 */
sssp_solver_t* sssp_solver_create(vertex_count_t max_vertices, const sssp_allocator_t* allocator) {
    SSSP_LOG_DEBUG("Creating SSSP solver for %u vertices", max_vertices);
    
    if (max_vertices == 0) {
        SSSP_LOG_ERROR("Cannot create solver with 0 vertices");
        return NULL;
    }
    
    if (allocator == NULL) {
        allocator = &SSSP_DEFAULT_ALLOCATOR;
    }
    
    sssp_solver_t* solver = sssp_alloc(allocator, sizeof(sssp_solver_t));
    if (!solver) {
        SSSP_LOG_ERROR("Failed to allocate memory for SSSP solver");
        return NULL;
    }
    
    solver->max_vertices = max_vertices;
    solver->allocator = allocator;
    
    // Create distance array
    solver->distances = sssp_alloc(allocator, max_vertices * sizeof(distance_t));
    if (!solver->distances) {
        SSSP_LOG_ERROR("Failed to allocate distances array");
        sssp_free(allocator, solver);
        return NULL;
    }
    
    // Create predecessor array
    solver->predecessors = sssp_alloc(allocator, max_vertices * sizeof(vertex_id_t));
    if (!solver->predecessors) {
        SSSP_LOG_ERROR("Failed to allocate predecessors array");
        sssp_free(allocator, solver->distances);
        sssp_free(allocator, solver);
        return NULL;
    }
    
    // Create visited array
    solver->visited = sssp_alloc(allocator, max_vertices * sizeof(bool));
    if (!solver->visited) {
        SSSP_LOG_ERROR("Failed to allocate visited array");
        sssp_free(allocator, solver->predecessors);
        sssp_free(allocator, solver->distances);
        sssp_free(allocator, solver);
        return NULL;
    }
    
    // Create partitioning heap
    solver->heap = sssp_partitioning_heap_create(max_vertices, allocator);
    if (!solver->heap) {
        SSSP_LOG_ERROR("Failed to create partitioning heap");
        sssp_free(allocator, solver->visited);
        sssp_free(allocator, solver->predecessors);
        sssp_free(allocator, solver->distances);
        sssp_free(allocator, solver);
        return NULL;
    }
    
    // Create pivot finder
    solver->pivot_finder = sssp_pivot_finder_create(max_vertices, allocator);
    if (!solver->pivot_finder) {
        SSSP_LOG_ERROR("Failed to create pivot finder");
        sssp_partitioning_heap_destroy(solver->heap);
        sssp_free(allocator, solver->visited);
        sssp_free(allocator, solver->predecessors);
        sssp_free(allocator, solver->distances);
        sssp_free(allocator, solver);
        return NULL;
    }
    
    // Create vertex sets for algorithm
    solver->sources = sssp_vertex_set_create(max_vertices, allocator);
    solver->close_vertices = sssp_vertex_set_create(max_vertices, allocator);
    solver->far_vertices = sssp_vertex_set_create(max_vertices, allocator);
    
    if (!solver->sources || !solver->close_vertices || !solver->far_vertices) {
        SSSP_LOG_ERROR("Failed to create vertex sets");
        if (solver->sources) sssp_vertex_set_destroy(solver->sources);
        if (solver->close_vertices) sssp_vertex_set_destroy(solver->close_vertices);
        if (solver->far_vertices) sssp_vertex_set_destroy(solver->far_vertices);
        sssp_pivot_finder_destroy(solver->pivot_finder);
        sssp_partitioning_heap_destroy(solver->heap);
        sssp_free(allocator, solver->visited);
        sssp_free(allocator, solver->predecessors);
        sssp_free(allocator, solver->distances);
        sssp_free(allocator, solver);
        return NULL;
    }
    
    // Initialize arrays
    for (vertex_count_t i = 0; i < max_vertices; i++) {
        solver->distances[i] = SSSP_INFINITY;
        solver->predecessors[i] = SSSP_INVALID_VERTEX;
        solver->visited[i] = false;
    }
    
    // Initialize statistics
    solver->stats.total_vertices_processed = 0;
    solver->stats.total_edges_relaxed = 0;
    solver->stats.pivots_used = 0;
    solver->stats.heap_operations = 0;
    solver->stats.algorithm_calls = 0;
    
    SSSP_LOG_DEBUG("SSSP solver created successfully");
    return solver;
}

/**
 * Destroy an SSSP solver
 */
void sssp_solver_destroy(sssp_solver_t* solver) {
    if (!solver) return;
    
    SSSP_LOG_DEBUG("Destroying SSSP solver");
    
    const sssp_allocator_t* allocator = solver->allocator;
    
    sssp_vertex_set_destroy(solver->sources);
    sssp_vertex_set_destroy(solver->close_vertices);
    sssp_vertex_set_destroy(solver->far_vertices);
    sssp_pivot_finder_destroy(solver->pivot_finder);
    sssp_partitioning_heap_destroy(solver->heap);
    sssp_free(allocator, solver->visited);
    sssp_free(allocator, solver->predecessors);
    sssp_free(allocator, solver->distances);
    sssp_free(allocator, solver);
    
    SSSP_LOG_DEBUG("SSSP solver destroyed successfully");
}

/**
 * Initialize distances and heap for given sources
 */
static sssp_error_t initialize_sources(sssp_solver_t* solver, const vertex_id_t* sources, 
                                       vertex_count_t num_sources) {
    // Clear heap and reset distances
    sssp_partitioning_heap_clear(solver->heap);
    
    for (vertex_count_t i = 0; i < solver->max_vertices; i++) {
        solver->distances[i] = SSSP_INFINITY;
        solver->predecessors[i] = SSSP_INVALID_VERTEX;
        solver->visited[i] = false;
    }
    
    // Initialize source vertices
    for (vertex_count_t i = 0; i < num_sources; i++) {
        vertex_id_t source = sources[i];
        if (source >= solver->max_vertices) {
            SSSP_LOG_ERROR("Invalid source vertex: %u", source);
            return SSSP_ERROR_INVALID_PARAMETER;
        }
        
        solver->distances[source] = 0.0;
        sssp_error_t result = sssp_partitioning_heap_insert(solver->heap, source, 0.0);
        if (result != SSSP_SUCCESS) {
            SSSP_LOG_ERROR("Failed to insert source vertex %u into heap", source);
            return result;
        }
        
        solver->stats.heap_operations++;
    }
    
    SSSP_LOG_DEBUG("Initialized %u source vertices", num_sources);
    return SSSP_SUCCESS;
}

/**
 * Standard Dijkstra's algorithm for small sets
 */
static sssp_error_t run_standard_dijkstra(sssp_solver_t* solver, const sssp_graph_t* graph,
                                           distance_t max_distance) {
    SSSP_LOG_TRACE("Running standard Dijkstra with max distance %.2f", max_distance);
    
    while (!sssp_partitioning_heap_is_empty(solver->heap)) {
        vertex_id_t u;
        distance_t dist_u;
        
        sssp_error_t result = sssp_partitioning_heap_extract_min(solver->heap, &u, &dist_u);
        if (result != SSSP_SUCCESS) {
            SSSP_LOG_ERROR("Failed to extract minimum from heap");
            return result;
        }
        
        solver->stats.heap_operations++;
        
        // Stop if we exceed maximum distance
        if (dist_u > max_distance) {
            SSSP_LOG_TRACE("Reached maximum distance %.2f, stopping", max_distance);
            break;
        }
        
        solver->visited[u] = true;
        solver->stats.total_vertices_processed++;
        
        SSSP_LOG_TRACE("Processing vertex %u with distance %.2f", u, dist_u);
        
        // Process all neighbors
        const sssp_adj_list_t* adj_list = sssp_graph_get_adj_list(graph, u);
        if (adj_list) {
            sssp_edge_node_t* edge = adj_list->head;
            while (edge) {
                vertex_id_t v = edge->to;
                distance_t new_dist = dist_u + edge->weight;
                
                solver->stats.total_edges_relaxed++;
                
                if (new_dist < solver->distances[v]) {
                    SSSP_LOG_TRACE("Relaxing edge %u -> %u: %.2f -> %.2f", 
                                   u, v, solver->distances[v], new_dist);
                    
                    if (solver->distances[v] == SSSP_INFINITY) {
                        // First time seeing this vertex
                        solver->distances[v] = new_dist;
                        solver->predecessors[v] = u;
                        result = sssp_partitioning_heap_insert(solver->heap, v, new_dist);
                    } else {
                        // Update existing distance
                        solver->distances[v] = new_dist;
                        solver->predecessors[v] = u;
                        result = sssp_partitioning_heap_decrease_key(solver->heap, v, new_dist);
                    }
                    
                    if (result != SSSP_SUCCESS) {
                        SSSP_LOG_ERROR("Failed heap operation for vertex %u", v);
                        return result;
                    }
                    
                    solver->stats.heap_operations++;
                }
                
                edge = edge->next;
            }
        }
    }
    
    SSSP_LOG_TRACE("Standard Dijkstra completed");
    return SSSP_SUCCESS;
}

/**
 * Implementation of Algorithm 3 (bounded multi-source shortest paths)
 */
sssp_error_t sssp_solve_bounded_multi_source(sssp_solver_t* solver, const sssp_graph_t* graph,
                                              const vertex_id_t* sources, vertex_count_t num_sources,
                                              distance_t max_distance) {
    if (!solver || !graph || !sources) {
        SSSP_LOG_ERROR("Invalid parameters");
        return SSSP_ERROR_INVALID_PARAMETER;
    }
    
    if (num_sources == 0) {
        SSSP_LOG_DEBUG("No sources provided");
        return SSSP_SUCCESS;
    }
    
    SSSP_LOG_INFO("Starting bounded multi-source SSSP: %u sources, max distance %.2f", 
                  num_sources, max_distance);
    
    solver->stats.algorithm_calls++;
    
    // Initialize solver state
    sssp_error_t result = initialize_sources(solver, sources, num_sources);
    if (result != SSSP_SUCCESS) {
        return result;
    }
    
    // Base case: if small number of sources, use standard Dijkstra
    const vertex_count_t SMALL_SET_THRESHOLD = 10; // Configurable threshold
    if (num_sources <= SMALL_SET_THRESHOLD) {
        SSSP_LOG_DEBUG("Using standard Dijkstra for small source set (%u sources)", num_sources);
        return run_standard_dijkstra(solver, graph, max_distance);
    }
    
    // Algorithm 3: Advanced multi-source approach
    SSSP_LOG_DEBUG("Using advanced multi-source algorithm");
    
    // Step 1: Compute threshold distance (Lemma 3.3)
    // τ = max_distance / log(num_sources) - heuristic from paper
    distance_t threshold = max_distance / log((double)num_sources);
    if (threshold <= 0) {
        threshold = max_distance * 0.5; // Fallback heuristic
    }
    
    SSSP_LOG_DEBUG("Computed threshold distance: %.2f", threshold);
    
    // Step 2: Partition vertices using the threshold
    result = sssp_partitioning_heap_partition(solver->heap, threshold, solver->close_vertices);
    if (result != SSSP_SUCCESS) {
        SSSP_LOG_ERROR("Failed to partition vertices");
        return result;
    }
    
    vertex_count_t close_count = sssp_vertex_set_size(solver->close_vertices);
    SSSP_LOG_DEBUG("Partitioned vertices: %u close (≤ %.2f)", close_count, threshold);
    
    // Step 3: For close vertices, run standard Dijkstra to completion
    if (close_count > 0) {
        // Re-insert close vertices into heap
        for (vertex_count_t i = 0; i < close_count; i++) {
            vertex_id_t v = sssp_vertex_set_get_vertex(solver->close_vertices, i);
            if (!solver->visited[v] && solver->distances[v] < SSSP_INFINITY) {
                sssp_partitioning_heap_insert(solver->heap, v, solver->distances[v]);
                solver->stats.heap_operations++;
            }
        }
        
        // Run Dijkstra on close vertices
        result = run_standard_dijkstra(solver, graph, max_distance);
        if (result != SSSP_SUCCESS) {
            SSSP_LOG_ERROR("Failed to process close vertices");
            return result;
        }
    }
    
    // Step 4: Collect far vertices (those still in heap or not yet processed)
    sssp_vertex_set_clear(solver->far_vertices);
    for (vertex_count_t v = 0; v < solver->max_vertices; v++) {
        if (!solver->visited[v] && solver->distances[v] < max_distance) {
            sssp_vertex_set_add(solver->far_vertices, v);
        }
    }
    
    vertex_count_t far_count = sssp_vertex_set_size(solver->far_vertices);
    SSSP_LOG_DEBUG("Far vertices to process: %u", far_count);
    
    // Step 5: If there are far vertices, use FINDPIVOTS and recurse
    if (far_count > 0) {
        // Compute target diameter for pivot finding
        distance_t target_diameter = (max_distance - threshold) * 0.5; // Heuristic
        
        SSSP_LOG_DEBUG("Finding pivots for far vertices with target diameter %.2f", target_diameter);
        
        // Clear the pivot finder first
        sssp_pivot_finder_clear(solver->pivot_finder);
        
        // Create configuration for FINDPIVOTS
        sssp_find_pivots_config_t config = sssp_find_pivots_config_default(solver->allocator);
        
        // Create result structure
        sssp_find_pivots_result_t* pivot_result = sssp_find_pivots_result_create(solver->allocator);
        if (!pivot_result) {
            SSSP_LOG_ERROR("Failed to create pivot result structure");
            return SSSP_ERROR_OUT_OF_MEMORY;
        }
        
        // Compute k parameter (heuristic: log of far vertex count)
        vertex_count_t k = (vertex_count_t)log((double)(far_count + 1)) + 1;
        if (k < 1) k = 1;
        
        SSSP_LOG_DEBUG("Finding pivots for far vertices with target diameter %.2f, k=%u", target_diameter, k);
        
        // Use the correct function signature: (graph, threshold, source_set, k, config, result)
        result = sssp_find_pivots(graph, target_diameter, solver->far_vertices, k, &config, pivot_result);
        if (result != SSSP_SUCCESS) {
            SSSP_LOG_ERROR("Failed to find pivots");
            sssp_find_pivots_result_destroy(pivot_result);
            return result;
        }
        
        // Extract pivots from result and store in pivot_finder for compatibility
        vertex_count_t num_pivots = sssp_vertex_set_size(pivot_result->pivots);
        solver->stats.pivots_used += num_pivots;
        
        // Copy pivots to pivot_finder structure for existing code compatibility
        sssp_pivot_finder_clear(solver->pivot_finder);
        for (vertex_count_t i = 0; i < num_pivots && i < solver->pivot_finder->max_vertices; i++) {
            vertex_id_t pivot = sssp_vertex_set_get_vertex(pivot_result->pivots, i);
            if (solver->pivot_finder->num_pivots < solver->pivot_finder->max_vertices) {
                solver->pivot_finder->pivots[solver->pivot_finder->num_pivots] = pivot;
                solver->pivot_finder->distances[solver->pivot_finder->num_pivots] = solver->distances[pivot];
                solver->pivot_finder->num_pivots++;
            }
        }
        
        SSSP_LOG_DEBUG("Found %u pivots", solver->pivot_finder->num_pivots);
        
        // Clean up
        sssp_find_pivots_result_destroy(pivot_result);
        
        // Recursively solve for each pivot as a single source
        for (vertex_count_t i = 0; i < solver->pivot_finder->num_pivots; i++) {
            vertex_id_t pivot = sssp_pivot_finder_get_pivot(solver->pivot_finder, i);
            
            SSSP_LOG_TRACE("Processing pivot %u", pivot);
            
            // Solve single-source problem from this pivot
            result = sssp_solve_bounded_multi_source(solver, graph, &pivot, 1, 
                                                     max_distance - solver->distances[pivot]);
            if (result != SSSP_SUCCESS) {
                SSSP_LOG_ERROR("Failed to solve from pivot %u", pivot);
                return result;
            }
        }
    }
    
    SSSP_LOG_INFO("Bounded multi-source SSSP completed successfully");
    SSSP_LOG_INFO("Statistics: %u vertices processed, %u edges relaxed, %u pivots used", 
                  solver->stats.total_vertices_processed, 
                  solver->stats.total_edges_relaxed,
                  solver->stats.pivots_used);
    
    return SSSP_SUCCESS;
}

/**
 * Solve standard single-source shortest path problem
 */
sssp_error_t sssp_solve_single_source(const sssp_graph_t* graph,
                                       vertex_id_t source,
                                       const sssp_algorithm_config_t* config,
                                       sssp_algorithm_result_t* result) {
    if (!graph || !result) {
        return SSSP_ERROR_INVALID_PARAMETER;
    }
    
    vertex_count_t num_vertices = sssp_graph_get_vertex_count(graph);
    if (source >= num_vertices) {
        return SSSP_ERROR_INVALID_PARAMETER;
    }
    
    // Use default config if none provided
    sssp_algorithm_config_t default_config;
    if (!config) {
        default_config = sssp_algorithm_config_default(num_vertices, NULL);
        config = &default_config;
    }
    
    SSSP_LOG_INFO("Solving single-source SSSP from vertex %u", source);
    
    clock_t start_time = clock();
    
    // Create internal solver
    sssp_solver_t* solver = sssp_solver_create(num_vertices, config->allocator);
    if (!solver) {
        return SSSP_ERROR_OUT_OF_MEMORY;
    }
    
    // Run algorithm
    sssp_error_t error = initialize_sources(solver, &source, 1);
    if (error == SSSP_SUCCESS) {
        error = run_standard_dijkstra(solver, graph, SSSP_INFINITY);
    }
    
    if (error == SSSP_SUCCESS) {
        // Copy results
        for (vertex_count_t i = 0; i < num_vertices; i++) {
            result->distances[i] = solver->distances[i];
            result->predecessors[i] = solver->predecessors[i];
            if (solver->visited[i]) {
                sssp_vertex_set_add(result->processed_vertices, i);
            }
        }
        
        result->vertices_processed = solver->stats.total_vertices_processed;
        result->relaxations_performed = solver->stats.total_edges_relaxed;
        result->recursive_calls = 1;
        result->is_optimal = true;
        result->validation_status = SSSP_SUCCESS;
    }
    
    clock_t end_time = clock();
    result->total_time_ms = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000.0;
    
    sssp_solver_destroy(solver);
    
    SSSP_LOG_INFO("Single-source SSSP completed in %.2f ms", result->total_time_ms);
    return error;
}

/**
 * Configuration management functions
 */
sssp_algorithm_config_t sssp_algorithm_config_default(vertex_count_t num_vertices,
                                                       const sssp_allocator_t* allocator) {
    sssp_algorithm_config_t config;
    memset(&config, 0, sizeof(config));
    
    config.k = sssp_compute_optimal_k(num_vertices);
    config.t = sssp_compute_optimal_t(num_vertices);
    config.max_recursion_depth = sssp_compute_optimal_recursion_depth(num_vertices, config.t);
    
    config.use_parallel_processing = false;
    config.use_early_termination = true;
    config.heap_block_size = 1024;
    
    config.allocator = allocator ? allocator : &SSSP_DEFAULT_ALLOCATOR;
    config.memory_limit_bytes = 0; // No limit
    
    config.enable_profiling = false;
    config.enable_validation = false;
    config.log_level = 0; // Default log level
    
    return config;
}

/**
 * Result management functions
 */
sssp_algorithm_result_t* sssp_algorithm_result_create(vertex_count_t num_vertices,
                                                       const sssp_allocator_t* allocator) {
    if (allocator == NULL) {
        allocator = &SSSP_DEFAULT_ALLOCATOR;
    }
    
    sssp_algorithm_result_t* result = sssp_alloc(allocator, sizeof(sssp_algorithm_result_t));
    if (!result) {
        return NULL;
    }
    
    memset(result, 0, sizeof(sssp_algorithm_result_t));
    
    result->distances = sssp_alloc(allocator, num_vertices * sizeof(weight_t));
    result->predecessors = sssp_alloc(allocator, num_vertices * sizeof(vertex_id_t));
    result->processed_vertices = sssp_vertex_set_create(num_vertices, allocator);
    
    if (!result->distances || !result->predecessors || !result->processed_vertices) {
        if (result->distances) sssp_free(allocator, result->distances);
        if (result->predecessors) sssp_free(allocator, result->predecessors);
        if (result->processed_vertices) sssp_vertex_set_destroy(result->processed_vertices);
        sssp_free(allocator, result);
        return NULL;
    }
    
    // Initialize arrays
    for (vertex_count_t i = 0; i < num_vertices; i++) {
        result->distances[i] = SSSP_INFINITY;
        result->predecessors[i] = SSSP_INVALID_VERTEX;
    }
    
    return result;
}

void sssp_algorithm_result_destroy(sssp_algorithm_result_t* result) {
    if (!result) return;
    
    const sssp_allocator_t* allocator = &SSSP_DEFAULT_ALLOCATOR; // We don't store allocator in result
    
    if (result->distances) sssp_free(allocator, result->distances);
    if (result->predecessors) sssp_free(allocator, result->predecessors);
    if (result->processed_vertices) sssp_vertex_set_destroy(result->processed_vertices);
    sssp_free(allocator, result);
}

/**
 * Main Algorithm 3 implementation
 */
sssp_error_t sssp_bounded_multi_source(const sssp_graph_t* graph,
                                        vertex_count_t recursion_level,
                                        weight_t threshold,
                                        const sssp_vertex_set_t* source_set,
                                        vertex_count_t k,
                                        vertex_count_t t,
                                        const sssp_algorithm_config_t* config,
                                        sssp_vertex_set_t* output_set,
                                        weight_t* B_prime_out) {
    if (!graph || !source_set || !output_set || !B_prime_out) {
        return SSSP_ERROR_INVALID_PARAMETER;
    }
    
    vertex_count_t source_count = sssp_vertex_set_size(source_set);
    
    SSSP_LOG_DEBUG("Algorithm 3: recursion_level=%u, threshold=%.2f, sources=%u, k=%u, t=%u",
                   recursion_level, threshold, source_count, k, t);
    
    // Check recursion depth limit
    if (recursion_level >= config->max_recursion_depth) {
        SSSP_LOG_DEBUG("Reached maximum recursion depth, using base case");
        return sssp_base_case(graph, threshold, source_set, k, config, output_set, B_prime_out);
    }
    
    // Base case: small source set
    if (source_count <= t) {
        return sssp_base_case(graph, threshold, source_set, k, config, output_set, B_prime_out);
    }
    
    // Main recursive case - use FINDPIVOTS
    sssp_find_pivots_config_t pivot_config = sssp_find_pivots_config_default(config->allocator);
    sssp_find_pivots_result_t* pivot_result = sssp_find_pivots_result_create(config->allocator);
    
    if (!pivot_result) {
        return SSSP_ERROR_OUT_OF_MEMORY;
    }
    
    sssp_error_t result = sssp_find_pivots(graph, threshold, source_set, k, &pivot_config, pivot_result);
    if (result != SSSP_SUCCESS) {
        sssp_find_pivots_result_destroy(pivot_result);
        return result;
    }
    
    // Process pivots and witnesses
    vertex_count_t num_pivots = sssp_vertex_set_size(pivot_result->pivots);
    vertex_count_t num_witnesses = sssp_vertex_set_size(pivot_result->witnesses);
    
    SSSP_LOG_DEBUG("Found %u pivots and %u witnesses", num_pivots, num_witnesses);
    
    // Recursively solve subproblems
    weight_t max_B_prime = 0.0;
    
    if (num_pivots > 0) {
        weight_t pivot_B_prime;
        result = sssp_bounded_multi_source(graph, recursion_level + 1, threshold,
                                           pivot_result->pivots, k, t, config,
                                           output_set, &pivot_B_prime);
        if (result != SSSP_SUCCESS) {
            sssp_find_pivots_result_destroy(pivot_result);
            return result;
        }
        max_B_prime = fmax(max_B_prime, pivot_B_prime);
    }
    
    if (num_witnesses > 0) {
        weight_t witness_B_prime;
        result = sssp_bounded_multi_source(graph, recursion_level + 1, threshold,
                                           pivot_result->witnesses, k, t, config,
                                           output_set, &witness_B_prime);
        if (result != SSSP_SUCCESS) {
            sssp_find_pivots_result_destroy(pivot_result);
            return result;
        }
        max_B_prime = fmax(max_B_prime, witness_B_prime);
    }
    
    *B_prime_out = max_B_prime;
    
    sssp_find_pivots_result_destroy(pivot_result);
    return SSSP_SUCCESS;
}

/**
 * Algorithm 2 implementation (base case)
 */
sssp_error_t sssp_base_case(const sssp_graph_t* graph,
                             weight_t threshold,
                             const sssp_vertex_set_t* source_set,
                             vertex_count_t k,
                             const sssp_algorithm_config_t* config,
                             sssp_vertex_set_t* output_set,
                             weight_t* B_prime_out) {
    if (!graph || !source_set || !output_set || !B_prime_out) {
        return SSSP_ERROR_INVALID_PARAMETER;
    }
    
    vertex_count_t num_vertices = sssp_graph_get_vertex_count(graph);
    vertex_count_t source_count = sssp_vertex_set_size(source_set);
    
    SSSP_LOG_DEBUG("Algorithm 2 (base case): threshold=%.2f, sources=%u", threshold, source_count);
    
    // Suppress unused parameter warning for k (used in paper but not in implementation)
    (void)k;
    
    // Create internal solver
    sssp_solver_t* solver = sssp_solver_create(num_vertices, config->allocator);
    if (!solver) {
        return SSSP_ERROR_OUT_OF_MEMORY;
    }
    
    // Convert vertex set to array
    vertex_id_t* source_array = sssp_alloc(config->allocator, source_count * sizeof(vertex_id_t));
    if (!source_array) {
        sssp_solver_destroy(solver);
        return SSSP_ERROR_OUT_OF_MEMORY;
    }
    
    for (vertex_count_t i = 0; i < source_count; i++) {
        source_array[i] = sssp_vertex_set_get_vertex(source_set, i);
    }
    
    // Run bounded multi-source algorithm
    sssp_error_t result = initialize_sources(solver, source_array, source_count);
    if (result == SSSP_SUCCESS) {
        result = run_standard_dijkstra(solver, graph, threshold);
    }
    
    if (result == SSSP_SUCCESS) {
        // Collect vertices within threshold
        sssp_vertex_set_clear(output_set);
        weight_t max_distance = 0.0;
        
        for (vertex_count_t v = 0; v < num_vertices; v++) {
            if (solver->distances[v] <= threshold) {
                sssp_vertex_set_add(output_set, v);
                if (solver->distances[v] > max_distance && solver->distances[v] < SSSP_INFINITY) {
                    max_distance = solver->distances[v];
                }
            }
        }
        
        *B_prime_out = max_distance;
        SSSP_LOG_DEBUG("Base case found %u vertices within threshold, max distance %.2f",
                       sssp_vertex_set_size(output_set), max_distance);
    }
    
    sssp_free(config->allocator, source_array);
    sssp_solver_destroy(solver);
    return result;
}

/**
 * Parameter computation utilities
 */
vertex_count_t sssp_compute_optimal_k(vertex_count_t num_vertices) {
    if (num_vertices <= 1) return 1;
    return (vertex_count_t)ceil(log2((double)num_vertices));
}

vertex_count_t sssp_compute_optimal_t(vertex_count_t num_vertices) {
    if (num_vertices <= 10) return num_vertices;
    return (vertex_count_t)ceil(sqrt((double)num_vertices));
}

vertex_count_t sssp_compute_optimal_recursion_depth(vertex_count_t num_vertices,
                                                     vertex_count_t t) {
    if (t <= 1) return 1;
    return (vertex_count_t)ceil(log((double)num_vertices) / log((double)t));
}