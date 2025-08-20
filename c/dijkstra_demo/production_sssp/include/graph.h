/**
 * @file graph.h
 * @brief Graph data structure and operations
 * 
 * This file defines the graph data structure used by the SSSP algorithm,
 * including adjacency list representation and related operations.
 * 
 * @author Sambit Chakraborty
 * @date 21-08-2025
 * @version 1.0
 */

#ifndef SSSP_GRAPH_H
#define SSSP_GRAPH_H

#include "sssp_common.h"

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct sssp_graph sssp_graph_t;
typedef struct sssp_edge_node sssp_edge_node_t;
typedef struct sssp_adj_list sssp_adj_list_t;

/**
 * @brief Edge node structure representing a directed edge in the graph
 */
struct sssp_edge_node {
    vertex_id_t to;                     ///< Destination vertex  
    weight_t weight;                    ///< Edge weight
    struct sssp_edge_node* next;        ///< Next edge in adjacency list
};

/**
 * @brief Adjacency list for a single vertex
 */
struct sssp_adj_list {
    sssp_edge_node_t* head;             ///< First edge in the list
    edge_count_t count;                 ///< Number of outgoing edges  
};

/**
 * @brief Graph data structure
 */
struct sssp_graph {
    vertex_count_t num_vertices;        ///< Number of vertices
    edge_count_t num_edges;             ///< Number of edges
    edge_count_t total_edges;           ///< Alias for num_edges for compatibility
    bool has_negative_weights;          ///< Whether graph has negative edge weights
    sssp_adj_list_t* adj_list;          ///< Adjacency lists
    
    // Memory management
    const sssp_allocator_t* allocator;  ///< Memory allocator
};

/**
 * @brief Graph creation and destruction
 */

/**
 * @brief Create a new graph with specified number of vertices
 * @param num_vertices Number of vertices in the graph
 * @param allocator Memory allocator to use (NULL for default)
 * @return Pointer to new graph or NULL on failure
 */
sssp_graph_t* sssp_graph_create(vertex_count_t num_vertices, 
                                 const sssp_allocator_t* allocator);

/**
 * @brief Destroy a graph and free all associated memory
 * @param graph Graph to destroy
 */
void sssp_graph_destroy(sssp_graph_t* graph);

/**
 * @brief Clear all edges from the graph while keeping vertices
 * @param graph Graph to clear
 * @return Error code
 */
sssp_error_t sssp_graph_clear(sssp_graph_t* graph);

/**
 * @brief Edge operations
 */

/**
 * @brief Add a directed edge to the graph
 * @param graph Target graph
 * @param src Source vertex
 * @param dest Destination vertex
 * @param weight Edge weight
 * @return Error code
 */
sssp_error_t sssp_graph_add_edge(sssp_graph_t* graph, 
                                  vertex_id_t src, 
                                  vertex_id_t dest, 
                                  weight_t weight);

/**
 * @brief Remove a directed edge from the graph
 * @param graph Target graph
 * @param src Source vertex
 * @param dest Destination vertex
 * @return Error code (SSSP_SUCCESS if edge was removed, other if not found)
 */
sssp_error_t sssp_graph_remove_edge(sssp_graph_t* graph, 
                                     vertex_id_t src, 
                                     vertex_id_t dest);

/**
 * @brief Check if an edge exists in the graph
 * @param graph Target graph
 * @param src Source vertex
 * @param dest Destination vertex
 * @param weight_out Pointer to store edge weight (can be NULL)
 * @return true if edge exists, false otherwise
 */
bool sssp_graph_has_edge(const sssp_graph_t* graph, 
                         vertex_id_t src, 
                         vertex_id_t dest, 
                         weight_t* weight_out);

/**
 * @brief Get the out-degree of a vertex
 * @param graph Target graph
 * @param vertex Vertex ID
 * @return Out-degree of the vertex, or 0 if vertex is invalid
 */
vertex_count_t sssp_graph_out_degree(const sssp_graph_t* graph, vertex_id_t vertex);

/**
 * @brief Graph properties and utilities
 */

/**
 * @brief Get the number of vertices in the graph
 * @param graph Target graph
 * @return Number of vertices
 */
SSSP_INLINE vertex_count_t sssp_graph_num_vertices(const sssp_graph_t* graph) {
    return graph ? graph->num_vertices : 0;
}

/**
 * @brief Get the total number of edges in the graph
 * @param graph Target graph
 * @return Total number of edges
 */
SSSP_INLINE size_t sssp_graph_num_edges(const sssp_graph_t* graph) {
    return graph ? graph->total_edges : 0;
}

/**
 * @brief Check if the graph has negative weights
 * @param graph Target graph
 * @return true if graph has negative weights
 */
SSSP_INLINE bool sssp_graph_has_negative_weights(const sssp_graph_t* graph) {
    return graph ? graph->has_negative_weights : false;
}

/**
 * @brief Validate that a vertex ID is within valid range
 * @param graph Target graph
 * @param vertex Vertex ID to validate
 * @return true if vertex is valid
 */
SSSP_INLINE bool sssp_graph_is_valid_vertex(const sssp_graph_t* graph, vertex_id_t vertex) {
    return graph && vertex >= 0 && vertex < (vertex_id_t)graph->num_vertices;
}

/**
 * @brief Get number of vertices in the graph
 * @param graph Graph instance
 * @return Number of vertices
 */
SSSP_INLINE vertex_count_t sssp_graph_get_vertex_count(const sssp_graph_t* graph) {
    return graph ? graph->num_vertices : 0;
}

/**
 * @brief Get the number of edges in the graph
 * @param graph Graph instance  
 * @return Number of edges
 */
edge_count_t sssp_graph_get_edge_count(const sssp_graph_t* graph);

/**
 * @brief Get adjacency list for a vertex
 * @param graph Graph instance
 * @param vertex Vertex ID
 * @return Pointer to adjacency list or NULL
 */
SSSP_INLINE const sssp_adj_list_t* sssp_graph_get_adj_list(const sssp_graph_t* graph, vertex_id_t vertex) {
    if (!graph || vertex >= graph->num_vertices) {
        return NULL;
    }
    return &graph->adj_list[vertex];
}

/**
 * @brief Graph I/O and serialization
 */

/**
 * @brief Load graph from file in edgelist format
 * @param filename Path to the graph file
 * @param allocator Memory allocator to use
 * @return Pointer to loaded graph or NULL on failure
 */
sssp_graph_t* sssp_graph_load_from_file(const char* filename, 
                                         const sssp_allocator_t* allocator);

/**
 * @brief Save graph to file in edgelist format
 * @param graph Graph to save
 * @param filename Output file path
 * @return Error code
 */
sssp_error_t sssp_graph_save_to_file(const sssp_graph_t* graph, 
                                      const char* filename);

/**
 * @brief Graph generation for testing
 */

/**
 * @brief Generate a random graph for testing
 * @param num_vertices Number of vertices
 * @param edge_probability Probability of each edge existing (0.0 to 1.0)
 * @param min_weight Minimum edge weight
 * @param max_weight Maximum edge weight
 * @param seed Random seed
 * @param allocator Memory allocator
 * @return Generated graph or NULL on failure
 */
sssp_graph_t* sssp_graph_generate_random(vertex_count_t num_vertices,
                                          double edge_probability,
                                          weight_t min_weight,
                                          weight_t max_weight,
                                          unsigned int seed,
                                          const sssp_allocator_t* allocator);

/**
 * @brief Generate a grid graph for testing
 * @param rows Number of rows
 * @param cols Number of columns
 * @param diagonal_edges Whether to include diagonal edges
 * @param allocator Memory allocator
 * @return Generated grid graph or NULL on failure
 */
sssp_graph_t* sssp_graph_generate_grid(vertex_count_t rows,
                                        vertex_count_t cols,
                                        bool diagonal_edges,
                                        const sssp_allocator_t* allocator);

/**
 * @brief Iterator for traversing edges
 */
typedef struct sssp_edge_iterator {
    const sssp_graph_t* graph;
    vertex_id_t current_vertex;
    const sssp_edge_node_t* current_edge;
} sssp_edge_iterator_t;

/**
 * @brief Initialize edge iterator for a specific vertex
 * @param graph Target graph
 * @param vertex Vertex to iterate edges from
 * @param iter Iterator to initialize
 * @return Error code
 */
sssp_error_t sssp_edge_iterator_init(const sssp_graph_t* graph, 
                                      vertex_id_t vertex,
                                      sssp_edge_iterator_t* iter);

/**
 * @brief Get next edge from iterator
 * @param iter Edge iterator
 * @param edge_out Pointer to store edge information
 * @return true if edge was retrieved, false if no more edges
 */
bool sssp_edge_iterator_next(sssp_edge_iterator_t* iter, 
                             const sssp_edge_node_t** edge_out);

/**
 * @brief Memory statistics
 */

/**
 * @brief Get memory usage statistics for the graph
 * @param graph Target graph
 * @return Memory statistics structure
 */
sssp_memory_stats_t sssp_graph_memory_stats(const sssp_graph_t* graph);

/**
 * @brief Print graph statistics to stdout
 * @param graph Target graph
 */
void sssp_graph_print_stats(const sssp_graph_t* graph);

#ifdef __cplusplus
}
#endif

#endif // SSSP_GRAPH_H
