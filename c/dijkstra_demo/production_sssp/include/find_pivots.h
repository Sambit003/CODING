/**
 * @file find_pivots.h
 * @brief FINDPIVOTS algorithm implementation (Algorithm 1 from the paper)
 * 
 * This file implements the FINDPIVOTS algorithm as described in Algorithm 1
 * of the research paper, which constructs a relaxation forest and identifies
 * pivot vertices for the SSSP algorithm.
 * 
 * @author Sambit Chakraborty
 * @date 21-08-2025
 * @version 1.0
 */

#ifndef SSSP_FIND_PIVOTS_H
#define SSSP_FIND_PIVOTS_H

#include "sssp_common.h"
#include "graph.h"
#include "vertex_set.h"

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct sssp_pivot_finder sssp_pivot_finder_t;

/**
 * @brief Pivot finder structure for Algorithm 1 (FINDPIVOTS)
 */
struct sssp_pivot_finder {
    vertex_count_t max_vertices;        ///< Maximum number of vertices
    const sssp_allocator_t* allocator;  ///< Memory allocator
    
    // Working data structures
    sssp_vertex_set_t* candidates;      ///< Candidate vertices set
    vertex_id_t* pivots;                ///< Array of found pivots
    distance_t* distances;              ///< Distances array for pivots
    distance_t* vertex_distances;       ///< Working distance array
    bool* visited;                      ///< Visited vertices array
    vertex_count_t num_pivots;          ///< Current number of pivots
};

/**
 * @brief Configuration for FINDPIVOTS algorithm
 */
typedef struct sssp_find_pivots_config {
    vertex_count_t max_layers;         ///< Maximum number of layers to process
    bool use_early_termination;        ///< Whether to use early termination
    const sssp_allocator_t* allocator; ///< Memory allocator
} sssp_find_pivots_config_t;

/**
 * @brief Result structure for FINDPIVOTS algorithm
 */
typedef struct sssp_find_pivots_result {
    sssp_vertex_set_t* pivots;          ///< Set of pivot vertices (P)
    sssp_vertex_set_t* witnesses;       ///< Set of witness vertices (W)
    vertex_count_t layers_processed;    ///< Number of layers actually processed
    uint64_t relaxations_performed;     ///< Number of edge relaxations performed
    double execution_time_ms;           ///< Execution time in milliseconds
} sssp_find_pivots_result_t;

/**
 * @brief Relaxation forest information
 */
typedef struct sssp_relaxation_forest {
    vertex_id_t* predecessors;          ///< Predecessor array for forest
    vertex_count_t* tree_sizes;        ///< Size of tree rooted at each vertex
    vertex_count_t* depths;             ///< Depth of each vertex in forest
    weight_t* distances;                ///< Distance estimates
    bool* in_forest;                    ///< Whether vertex is in forest
} sssp_relaxation_forest_t;

/**
 * @brief Main FINDPIVOTS algorithm implementation
 */

/**
 * @brief Execute FINDPIVOTS algorithm (Algorithm 1)
 * @param graph Input graph
 * @param threshold Distance threshold (B parameter)
 * @param source_set Source vertex set (S parameter) 
 * @param k Algorithm parameter k
 * @param config Algorithm configuration
 * @param result Result structure to fill
 * @return Error code
 */
sssp_error_t sssp_find_pivots(const sssp_graph_t* graph,
                               weight_t threshold,
                               const sssp_vertex_set_t* source_set,
                               vertex_count_t k,
                               const sssp_find_pivots_config_t* config,
                               sssp_find_pivots_result_t* result);

/**
 * @brief Optimized version with pre-allocated data structures
 * @param graph Input graph
 * @param threshold Distance threshold (B parameter)
 * @param source_set Source vertex set (S parameter)
 * @param k Algorithm parameter k
 * @param config Algorithm configuration
 * @param forest Pre-allocated relaxation forest
 * @param result Result structure to fill
 * @return Error code
 */
sssp_error_t sssp_find_pivots_with_forest(const sssp_graph_t* graph,
                                           weight_t threshold,
                                           const sssp_vertex_set_t* source_set,
                                           vertex_count_t k,
                                           const sssp_find_pivots_config_t* config,
                                           sssp_relaxation_forest_t* forest,
                                           sssp_find_pivots_result_t* result);

/**
 * @brief Relaxation forest operations
 */

/**
 * @brief Create a new relaxation forest
 * @param num_vertices Number of vertices in the graph
 * @param allocator Memory allocator (NULL for default)
 * @return Pointer to new forest or NULL on failure
 */
sssp_relaxation_forest_t* sssp_relaxation_forest_create(vertex_count_t num_vertices,
                                                         const sssp_allocator_t* allocator);

/**
 * @brief Destroy relaxation forest and free memory
 * @param forest Forest to destroy
 */
void sssp_relaxation_forest_destroy(sssp_relaxation_forest_t* forest);

/**
 * @brief Initialize forest with source vertices
 * @param forest Target forest
 * @param source_set Source vertices
 * @param distances Initial distance array
 * @return Error code
 */
sssp_error_t sssp_relaxation_forest_init(sssp_relaxation_forest_t* forest,
                                          const sssp_vertex_set_t* source_set,
                                          const weight_t* distances);

/**
 * @brief Reset forest to initial state
 * @param forest Target forest
 * @return Error code
 */
sssp_error_t sssp_relaxation_forest_reset(sssp_relaxation_forest_t* forest);

/**
 * @brief Layer-by-layer construction
 */

/**
 * @brief Process a single layer of the relaxation forest
 * @param graph Input graph
 * @param forest Relaxation forest
 * @param current_layer Current layer vertices
 * @param next_layer Output for next layer vertices
 * @param threshold Distance threshold
 * @param relaxations_out Pointer to store number of relaxations performed
 * @return Error code
 */
sssp_error_t sssp_process_layer(const sssp_graph_t* graph,
                                 sssp_relaxation_forest_t* forest,
                                 const sssp_vertex_set_t* current_layer,
                                 sssp_vertex_set_t* next_layer,
                                 weight_t threshold,
                                 uint64_t* relaxations_out);

/**
 * @brief Relax all edges from vertices in current layer
 * @param graph Input graph
 * @param forest Relaxation forest
 * @param layer_vertices Vertices in current layer
 * @param threshold Distance threshold
 * @param improved_vertices Output set of vertices with improved distances
 * @param relaxations_out Pointer to store number of relaxations
 * @return Error code
 */
sssp_error_t sssp_relax_layer_edges(const sssp_graph_t* graph,
                                     sssp_relaxation_forest_t* forest,
                                     const sssp_vertex_set_t* layer_vertices,
                                     weight_t threshold,
                                     sssp_vertex_set_t* improved_vertices,
                                     uint64_t* relaxations_out);

/**
 * @brief Pivot selection
 */

/**
 * @brief Select pivot vertices based on tree sizes
 * @param forest Relaxation forest
 * @param source_set Source vertices to consider as potential pivots
 * @param k Algorithm parameter k
 * @param pivots Output set for pivot vertices
 * @return Error code
 */
sssp_error_t sssp_select_pivots(const sssp_relaxation_forest_t* forest,
                                 const sssp_vertex_set_t* source_set,
                                 vertex_count_t k,
                                 sssp_vertex_set_t* pivots);

/**
 * @brief Compute tree sizes for all vertices in the forest
 * @param forest Relaxation forest
 * @param num_vertices Number of vertices
 * @return Error code
 */
sssp_error_t sssp_compute_tree_sizes(sssp_relaxation_forest_t* forest,
                                      vertex_count_t num_vertices);

/**
 * @brief Get size of tree rooted at given vertex
 * @param forest Relaxation forest
 * @param vertex Root vertex
 * @return Size of tree rooted at vertex
 */
vertex_count_t sssp_get_tree_size(const sssp_relaxation_forest_t* forest,
                                   vertex_id_t vertex);

/**
 * @brief Utilities and validation
 */

/**
 * @brief Validate that the relaxation forest is consistent
 * @param forest Relaxation forest
 * @param num_vertices Number of vertices
 * @return true if forest is valid
 */
bool sssp_relaxation_forest_validate(const sssp_relaxation_forest_t* forest,
                                      vertex_count_t num_vertices);

/**
 * @brief Check early termination condition
 * @param witnesses Current witness set
 * @param source_set Source vertex set
 * @param k Algorithm parameter k
 * @return true if early termination should occur
 */
bool sssp_should_terminate_early(const sssp_vertex_set_t* witnesses,
                                  const sssp_vertex_set_t* source_set,
                                  vertex_count_t k);

/**
 * @brief Configuration and result management
 */

/**
 * @brief Create default FINDPIVOTS configuration
 * @param allocator Memory allocator (NULL for default)
 * @return Default configuration
 */
sssp_find_pivots_config_t sssp_find_pivots_config_default(const sssp_allocator_t* allocator);

/**
 * @brief Create FINDPIVOTS result structure
 * @param allocator Memory allocator (NULL for default)
 * @return Initialized result structure or NULL on failure
 */
sssp_find_pivots_result_t* sssp_find_pivots_result_create(const sssp_allocator_t* allocator);

/**
 * @brief Destroy FINDPIVOTS result and free memory
 * @param result Result structure to destroy
 */
void sssp_find_pivots_result_destroy(sssp_find_pivots_result_t* result);

/**
 * @brief Clear result structure for reuse
 * @param result Result structure to clear
 * @return Error code
 */
sssp_error_t sssp_find_pivots_result_clear(sssp_find_pivots_result_t* result);

/**
 * @brief Debugging and visualization
 */

/**
 * @brief Print FINDPIVOTS statistics
 * @param result Algorithm result
 */
void sssp_find_pivots_print_stats(const sssp_find_pivots_result_t* result);

/**
 * @brief Print relaxation forest structure
 * @param forest Relaxation forest
 * @param num_vertices Number of vertices
 * @param max_vertices Maximum vertices to print
 */
void sssp_relaxation_forest_print(const sssp_relaxation_forest_t* forest,
                                   vertex_count_t num_vertices,
                                   vertex_count_t max_vertices);

/**
 * @brief Export relaxation forest to DOT format for visualization
 * @param forest Relaxation forest
 * @param num_vertices Number of vertices
 * @param filename Output filename
 * @return Error code
 */
sssp_error_t sssp_relaxation_forest_export_dot(const sssp_relaxation_forest_t* forest,
                                                vertex_count_t num_vertices,
                                                const char* filename);

/**
 * @brief Performance profiling
 */

/**
 * @brief Profiling information for FINDPIVOTS execution
 */
typedef struct sssp_find_pivots_profile {
    double total_time_ms;               ///< Total execution time
    double forest_construction_ms;      ///< Time for forest construction
    double pivot_selection_ms;          ///< Time for pivot selection
    uint64_t total_relaxations;         ///< Total edge relaxations
    uint64_t useful_relaxations;        ///< Relaxations that improved distances
    vertex_count_t max_layer_size;      ///< Maximum layer size encountered
    double avg_layer_size;              ///< Average layer size
} sssp_find_pivots_profile_t;

/**
 * @brief Execute FINDPIVOTS with detailed profiling
 * @param graph Input graph
 * @param threshold Distance threshold
 * @param source_set Source vertex set
 * @param k Algorithm parameter k
 * @param config Algorithm configuration
 * @param result Result structure to fill
 * @param profile Profiling information to fill
 * @return Error code
 */
sssp_error_t sssp_find_pivots_profiled(const sssp_graph_t* graph,
                                        weight_t threshold,
                                        const sssp_vertex_set_t* source_set,
                                        vertex_count_t k,
                                        const sssp_find_pivots_config_t* config,
                                        sssp_find_pivots_result_t* result,
                                        sssp_find_pivots_profile_t* profile);

/**
 * @brief Pivot finder utility functions
 */

/**
 * @brief Create a new pivot finder
 * @param max_vertices Maximum number of vertices
 * @param allocator Memory allocator (NULL for default)
 * @return Pointer to new pivot finder or NULL on failure
 */
sssp_pivot_finder_t* sssp_pivot_finder_create(vertex_count_t max_vertices,
                                               const sssp_allocator_t* allocator);

/**
 * @brief Destroy a pivot finder
 * @param finder Pivot finder to destroy
 */
void sssp_pivot_finder_destroy(sssp_pivot_finder_t* finder);

/**
 * @brief Clear pivot finder state
 * @param finder Pivot finder to clear
 */
void sssp_pivot_finder_clear(sssp_pivot_finder_t* finder);

/**
 * @brief Get number of pivots found
 * @param finder Pivot finder instance
 * @return Number of pivots
 */
vertex_count_t sssp_pivot_finder_get_pivot_count(const sssp_pivot_finder_t* finder);

/**
 * @brief Get specific pivot vertex
 * @param finder Pivot finder instance
 * @param index Pivot index
 * @return Pivot vertex ID or SSSP_INVALID_VERTEX
 */
vertex_id_t sssp_pivot_finder_get_pivot(const sssp_pivot_finder_t* finder, vertex_count_t index);

/**
 * @brief Validate pivot finder state
 * @param finder Pivot finder instance
 * @return true if valid
 */
bool sssp_pivot_finder_is_valid(const sssp_pivot_finder_t* finder);

#ifdef __cplusplus
}
#endif

#endif // SSSP_FIND_PIVOTS_H
