/**
 * @file sssp_algorithm.h
 * @brief Main SSSP algorithm implementation (Algorithm 3 from the paper)
 * 
 * This file implements the main bounded multi-source shortest path algorithm
 * as described in Algorithm 3 of the research paper arXiv:2504.17033v2.
 * 
 * @author Sambit Chakraborty
 * @date 21-08-2025
 * @version 1.0
 */

#ifndef SSSP_ALGORITHM_H
#define SSSP_ALGORITHM_H

#include "sssp_common.h"
#include "graph.h"
#include "vertex_set.h"
#include "partitioning_heap.h"
#include "find_pivots.h"

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct sssp_solver sssp_solver_t;
typedef struct sssp_stats sssp_stats_t;

/**
 * @brief Algorithm performance statistics
 */
struct sssp_stats {
    uint64_t total_vertices_processed;  ///< Total vertices processed
    uint64_t total_edges_relaxed;       ///< Total edge relaxations
    uint64_t pivots_used;               ///< Number of pivots used
    uint64_t heap_operations;           ///< Number of heap operations
    uint64_t algorithm_calls;           ///< Number of algorithm calls
    double execution_time_ms;           ///< Total execution time in milliseconds
};

/**
 * @brief Main SSSP solver structure
 */
struct sssp_solver {
    vertex_count_t max_vertices;        ///< Maximum number of vertices
    const sssp_allocator_t* allocator;  ///< Memory allocator
    
    // Core algorithm data structures
    distance_t* distances;              ///< Distance array
    vertex_id_t* predecessors;          ///< Predecessor array
    bool* visited;                      ///< Visited array
    
    // Algorithm components
    sssp_partitioning_heap_t* heap;     ///< Partitioning heap
    sssp_pivot_finder_t* pivot_finder;  ///< Pivot finder
    
    // Working sets
    sssp_vertex_set_t* sources;         ///< Source vertices set
    sssp_vertex_set_t* close_vertices;  ///< Close vertices set (distance <= B)
    sssp_vertex_set_t* far_vertices;    ///< Far vertices set (distance > B)
    
    // Statistics
    sssp_stats_t stats;                 ///< Performance statistics
};

/**
 * @brief Algorithm configuration
 */
typedef struct sssp_algorithm_config {
    // Algorithm parameters
    vertex_count_t k;                   ///< Parameter k (derived from graph size)
    vertex_count_t t;                   ///< Parameter t (derived from graph size) 
    vertex_count_t max_recursion_depth; ///< Maximum recursion depth (l parameter)
    
    // Performance options
    bool use_parallel_processing;       ///< Enable parallel processing where possible
    bool use_early_termination;         ///< Enable early termination optimizations
    vertex_count_t heap_block_size;     ///< Block size for partitioning heap
    
    // Memory management
    const sssp_allocator_t* allocator;  ///< Memory allocator
    size_t memory_limit_bytes;          ///< Memory usage limit (0 for no limit)
    
    // Debugging and profiling
    bool enable_profiling;              ///< Enable detailed profiling
    bool enable_validation;             ///< Enable algorithm validation
    sssp_log_level_t log_level;         ///< Logging level
} sssp_algorithm_config_t;

/**
 * @brief Algorithm result
 */
typedef struct sssp_algorithm_result {
    // Distance results
    weight_t* distances;                ///< Final distance array
    vertex_id_t* predecessors;          ///< Predecessor array for path reconstruction
    
    // Algorithm state
    sssp_vertex_set_t* processed_vertices; ///< Vertices that were processed
    vertex_count_t vertices_processed;  ///< Number of vertices processed
    
    // Performance metrics
    double total_time_ms;               ///< Total execution time
    uint64_t relaxations_performed;     ///< Total edge relaxations
    vertex_count_t recursive_calls;     ///< Number of recursive calls made
    size_t peak_memory_bytes;           ///< Peak memory usage
    
    // Validation
    bool is_optimal;                    ///< Whether result is guaranteed optimal
    sssp_error_t validation_status;     ///< Result of validation check
} sssp_algorithm_result_t;

/**
 * @brief Main algorithm interface
 */

/**
 * @brief Solve single-source shortest paths
 * @param graph Input graph
 * @param source Source vertex
 * @param config Algorithm configuration (NULL for default)
 * @param result Result structure to fill
 * @return Error code
 */
sssp_error_t sssp_solve_single_source(const sssp_graph_t* graph,
                                       vertex_id_t source,
                                       const sssp_algorithm_config_t* config,
                                       sssp_algorithm_result_t* result);

/**
 * @brief Solve bounded multi-source shortest paths (Algorithm 3)
 * @param graph Input graph
 * @param recursion_level Current recursion level (l parameter)
 * @param threshold Distance threshold (B parameter)
 * @param source_set Source vertex set (S parameter)
 * @param k Algorithm parameter k
 * @param t Algorithm parameter t
 * @param config Algorithm configuration
 * @param output_set Output vertex set (U parameter)
 * @param B_prime_out Pointer to store updated threshold
 * @return Error code
 */
sssp_error_t sssp_bounded_multi_source(const sssp_graph_t* graph,
                                        vertex_count_t recursion_level,
                                        weight_t threshold,
                                        const sssp_vertex_set_t* source_set,
                                        vertex_count_t k,
                                        vertex_count_t t,
                                        const sssp_algorithm_config_t* config,
                                        sssp_vertex_set_t* output_set,
                                        weight_t* B_prime_out);

/**
 * @brief Base case implementation (Algorithm 2)
 * @param graph Input graph
 * @param threshold Distance threshold
 * @param source_set Source vertex set
 * @param k Algorithm parameter k
 * @param config Algorithm configuration
 * @param output_set Output vertex set
 * @param B_prime_out Pointer to store updated threshold
 * @return Error code
 */
sssp_error_t sssp_base_case(const sssp_graph_t* graph,
                             weight_t threshold,
                             const sssp_vertex_set_t* source_set,
                             vertex_count_t k,
                             const sssp_algorithm_config_t* config,
                             sssp_vertex_set_t* output_set,
                             weight_t* B_prime_out);

/**
 * @brief Configuration management
 */

/**
 * @brief Create default algorithm configuration
 * @param num_vertices Number of vertices in graph
 * @param allocator Memory allocator (NULL for default)
 * @return Default configuration
 */
sssp_algorithm_config_t sssp_algorithm_config_default(vertex_count_t num_vertices,
                                                       const sssp_allocator_t* allocator);

/**
 * @brief Create optimized configuration based on graph properties
 * @param graph Input graph
 * @param optimization_target Target to optimize for ("speed", "memory", "balanced")
 * @return Optimized configuration
 */
sssp_algorithm_config_t sssp_algorithm_config_optimized(const sssp_graph_t* graph,
                                                         const char* optimization_target);

/**
 * @brief Validate algorithm configuration
 * @param config Configuration to validate
 * @param num_vertices Number of vertices in target graph
 * @return Error code (SSSP_SUCCESS if valid)
 */
sssp_error_t sssp_algorithm_config_validate(const sssp_algorithm_config_t* config,
                                             vertex_count_t num_vertices);

/**
 * @brief Result management
 */

/**
 * @brief Create algorithm result structure
 * @param num_vertices Number of vertices
 * @param allocator Memory allocator (NULL for default)
 * @return Initialized result structure or NULL on failure
 */
sssp_algorithm_result_t* sssp_algorithm_result_create(vertex_count_t num_vertices,
                                                       const sssp_allocator_t* allocator);

/**
 * @brief Destroy algorithm result and free memory
 * @param result Result structure to destroy
 */
void sssp_algorithm_result_destroy(sssp_algorithm_result_t* result);

/**
 * @brief Clear result structure for reuse
 * @param result Result structure to clear
 * @param num_vertices Number of vertices
 * @return Error code
 */
sssp_error_t sssp_algorithm_result_clear(sssp_algorithm_result_t* result,
                                          vertex_count_t num_vertices);

/**
 * @brief Copy algorithm result
 * @param dest Destination result
 * @param src Source result
 * @param num_vertices Number of vertices
 * @return Error code
 */
sssp_error_t sssp_algorithm_result_copy(sssp_algorithm_result_t* dest,
                                         const sssp_algorithm_result_t* src,
                                         vertex_count_t num_vertices);

/**
 * @brief Path reconstruction
 */

/**
 * @brief Reconstruct shortest path from source to target
 * @param result Algorithm result containing predecessors
 * @param source Source vertex
 * @param target Target vertex
 * @param path Output vertex set for path
 * @return Error code
 */
sssp_error_t sssp_reconstruct_path(const sssp_algorithm_result_t* result,
                                   vertex_id_t source,
                                   vertex_id_t target,
                                   sssp_vertex_set_t* path);

/**
 * @brief Get distance to target vertex
 * @param result Algorithm result
 * @param target Target vertex
 * @param distance_out Pointer to store distance
 * @return Error code
 */
sssp_error_t sssp_get_distance(const sssp_algorithm_result_t* result,
                                vertex_id_t target,
                                weight_t* distance_out);

/**
 * @brief Validation and verification
 */

/**
 * @brief Validate algorithm result against expected distances
 * @param graph Input graph
 * @param source Source vertex
 * @param result Algorithm result to validate
 * @param expected_distances Expected distance array (can be NULL)
 * @return Error code
 */
sssp_error_t sssp_validate_result(const sssp_graph_t* graph,
                                   vertex_id_t source,
                                   const sssp_algorithm_result_t* result,
                                   const weight_t* expected_distances);

/**
 * @brief Compare two algorithm results for equality
 * @param result1 First result
 * @param result2 Second result
 * @param num_vertices Number of vertices
 * @param tolerance Floating-point tolerance for distance comparison
 * @return true if results are equivalent
 */
bool sssp_results_equal(const sssp_algorithm_result_t* result1,
                        const sssp_algorithm_result_t* result2,
                        vertex_count_t num_vertices,
                        weight_t tolerance);

/**
 * @brief Reference implementations for validation
 */

/**
 * @brief Dijkstra's algorithm for validation
 * @param graph Input graph
 * @param source Source vertex
 * @param allocator Memory allocator
 * @param distances_out Output distance array
 * @param predecessors_out Output predecessor array (can be NULL)
 * @return Error code
 */
sssp_error_t sssp_dijkstra_reference(const sssp_graph_t* graph,
                                      vertex_id_t source,
                                      const sssp_allocator_t* allocator,
                                      weight_t** distances_out,
                                      vertex_id_t** predecessors_out);

/**
 * @brief Bellman-Ford algorithm for graphs with negative weights
 * @param graph Input graph
 * @param source Source vertex
 * @param allocator Memory allocator
 * @param distances_out Output distance array
 * @param predecessors_out Output predecessor array (can be NULL)
 * @param has_negative_cycle_out Pointer to store negative cycle detection
 * @return Error code
 */
sssp_error_t sssp_bellman_ford_reference(const sssp_graph_t* graph,
                                          vertex_id_t source,
                                          const sssp_allocator_t* allocator,
                                          weight_t** distances_out,
                                          vertex_id_t** predecessors_out,
                                          bool* has_negative_cycle_out);

/**
 * @brief Performance analysis
 */

/**
 * @brief Detailed profiling information
 */
typedef struct sssp_performance_profile {
    // Time breakdown
    double total_time_ms;
    double initialization_time_ms;
    double find_pivots_time_ms;
    double heap_operations_time_ms;
    double recursive_calls_time_ms;
    double finalization_time_ms;
    
    // Operation counts
    uint64_t total_relaxations;
    uint64_t useful_relaxations;
    uint64_t heap_inserts;
    uint64_t heap_pulls;
    uint64_t recursive_calls;
    
    // Memory usage
    size_t peak_memory_bytes;
    size_t avg_memory_bytes;
    size_t heap_memory_bytes;
    size_t temporary_memory_bytes;
    
    // Algorithm behavior
    vertex_count_t max_recursion_depth;
    vertex_count_t avg_pivot_set_size;
    vertex_count_t max_heap_size;
    double cache_hit_ratio;
} sssp_performance_profile_t;

/**
 * @brief Execute algorithm with detailed profiling
 * @param graph Input graph
 * @param source Source vertex
 * @param config Algorithm configuration
 * @param result Result structure to fill
 * @param profile Profiling information to fill
 * @return Error code
 */
sssp_error_t sssp_solve_with_profiling(const sssp_graph_t* graph,
                                        vertex_id_t source,
                                        const sssp_algorithm_config_t* config,
                                        sssp_algorithm_result_t* result,
                                        sssp_performance_profile_t* profile);

/**
 * @brief Debugging and visualization
 */

/**
 * @brief Print algorithm result statistics
 * @param result Algorithm result
 * @param num_vertices Number of vertices
 */
void sssp_algorithm_result_print_stats(const sssp_algorithm_result_t* result,
                                        vertex_count_t num_vertices);

/**
 * @brief Print performance profile
 * @param profile Performance profile
 */
void sssp_performance_profile_print(const sssp_performance_profile_t* profile);

/**
 * @brief Export result to various formats
 * @param result Algorithm result
 * @param num_vertices Number of vertices
 * @param filename Output filename
 * @param format Output format ("distances", "paths", "dot")
 * @return Error code
 */
sssp_error_t sssp_algorithm_result_export(const sssp_algorithm_result_t* result,
                                           vertex_count_t num_vertices,
                                           const char* filename,
                                           const char* format);

/**
 * @brief Parameter computation utilities
 */

/**
 * @brief Compute optimal k parameter based on graph size
 * @param num_vertices Number of vertices
 * @return Optimal k value
 */
vertex_count_t sssp_compute_optimal_k(vertex_count_t num_vertices);

/**
 * @brief Compute optimal t parameter based on graph size
 * @param num_vertices Number of vertices
 * @return Optimal t value
 */
vertex_count_t sssp_compute_optimal_t(vertex_count_t num_vertices);

/**
 * @brief Compute optimal recursion depth based on parameters
 * @param num_vertices Number of vertices
 * @param t Parameter t
 * @return Optimal recursion depth
 */
vertex_count_t sssp_compute_optimal_recursion_depth(vertex_count_t num_vertices,
                                                     vertex_count_t t);

#ifdef __cplusplus
}
#endif

#endif // SSSP_ALGORITHM_H
