/**
 * @file graph.c
 * @brief Implementation of graph data structures and operations for SSSP algorithm
 * 
 * @author Sambit Chakraborty
 * @date 21-08-2025
 * @version 1.0
 */

#include "graph.h"
#include "sssp_common.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <stdio.h>

/**
 * Create a new graph with specified number of vertices
 */
sssp_graph_t* sssp_graph_create(vertex_count_t num_vertices, const sssp_allocator_t* allocator) {
    SSSP_LOG_DEBUG("Creating graph with %u vertices", num_vertices);
    
    if (num_vertices == 0) {
        SSSP_LOG_ERROR("Cannot create graph with 0 vertices");
        return NULL;
    }
    
    if (allocator == NULL) {
        allocator = &SSSP_DEFAULT_ALLOCATOR;
    }
    
    sssp_graph_t* graph = sssp_alloc(allocator, sizeof(sssp_graph_t));
    if (!graph) {
        SSSP_LOG_ERROR("Failed to allocate memory for graph");
        return NULL;
    }
    
    graph->num_vertices = num_vertices;
    graph->num_edges = 0;
    graph->total_edges = 0;  // Initialize total_edges
    graph->has_negative_weights = false;
    graph->allocator = allocator;
    
    // Allocate adjacency list array
    graph->adj_list = sssp_alloc(allocator, num_vertices * sizeof(sssp_adj_list_t));
    if (!graph->adj_list) {
        SSSP_LOG_ERROR("Failed to allocate adjacency list array");
        sssp_free(allocator, graph);
        return NULL;
    }
    
    // Initialize each adjacency list
    for (vertex_count_t i = 0; i < num_vertices; i++) {
        graph->adj_list[i].head = NULL;
        graph->adj_list[i].count = 0;
    }
    
    SSSP_LOG_DEBUG("Graph created successfully");
    return graph;
}

/**
 * Destroy a graph and free all associated memory
 */
void sssp_graph_destroy(sssp_graph_t* graph) {
    if (!graph) return;
    
    SSSP_LOG_DEBUG("Destroying graph with %u vertices", graph->num_vertices);
    
    const sssp_allocator_t* allocator = graph->allocator;
    
    // Free all edge nodes
    for (vertex_count_t i = 0; i < graph->num_vertices; i++) {
        sssp_edge_node_t* current = graph->adj_list[i].head;
        while (current) {
            sssp_edge_node_t* next = current->next;
            sssp_free(allocator, current);
            current = next;
        }
    }
    
    // Free adjacency list array
    sssp_free(allocator, graph->adj_list);
    
    // Free graph structure
    sssp_free(allocator, graph);
    
    SSSP_LOG_DEBUG("Graph destroyed successfully");
}

/**
 * Add an edge to the graph
 */
sssp_error_t sssp_graph_add_edge(sssp_graph_t* graph, vertex_id_t from, vertex_id_t to, 
                                 edge_weight_t weight) {
    if (!graph) {
        SSSP_LOG_ERROR("Graph is NULL");
        return SSSP_ERROR_INVALID_PARAMETER;
    }
    
    if (from >= graph->num_vertices || to >= graph->num_vertices) {
        SSSP_LOG_ERROR("Invalid vertex IDs: from=%u, to=%u (max=%u)", 
                       from, to, graph->num_vertices - 1);
        return SSSP_ERROR_INVALID_PARAMETER;
    }
    
    if (weight < 0) {
        SSSP_LOG_ERROR("Negative edge weight not supported: %f", weight);
        return SSSP_ERROR_INVALID_PARAMETER;
    }
    
    SSSP_LOG_TRACE("Adding edge: %u -> %u (weight=%.2f)", from, to, weight);
    
    // Allocate new edge node
    sssp_edge_node_t* edge_node = sssp_alloc(graph->allocator, sizeof(sssp_edge_node_t));
    if (!edge_node) {
        SSSP_LOG_ERROR("Failed to allocate memory for edge node");
        return SSSP_ERROR_OUT_OF_MEMORY;
    }
    
    // Initialize edge node
    edge_node->to = to;
    edge_node->weight = weight;
    edge_node->next = graph->adj_list[from].head;
    
    // Insert at head of adjacency list
    graph->adj_list[from].head = edge_node;
    graph->adj_list[from].count++;
    graph->num_edges++;
    graph->total_edges++;  // Update total_edges as well
    
    SSSP_LOG_TRACE("Edge added successfully. Total edges: %u", graph->num_edges);
    return SSSP_SUCCESS;
}

/**
 * Get the number of edges in the graph
 */
edge_count_t sssp_graph_get_edge_count(const sssp_graph_t* graph) {
    return graph ? graph->num_edges : 0;
}

/**
 * Check if the graph is valid
 */
bool sssp_graph_is_valid(const sssp_graph_t* graph) {
    if (!graph) {
        SSSP_LOG_ERROR("Graph is NULL");
        return false;
    }
    
    if (graph->num_vertices == 0) {
        SSSP_LOG_ERROR("Graph has 0 vertices");
        return false;
    }
    
    if (!graph->adj_list) {
        SSSP_LOG_ERROR("Graph adjacency list is NULL");
        return false;
    }
    
    // Verify edge count consistency
    edge_count_t counted_edges = 0;
    for (vertex_count_t i = 0; i < graph->num_vertices; i++) {
        counted_edges += graph->adj_list[i].count;
        
        // Verify adjacency list integrity
        edge_count_t list_count = 0;
        sssp_edge_node_t* current = graph->adj_list[i].head;
        while (current) {
            if (current->to >= graph->num_vertices) {
                SSSP_LOG_ERROR("Invalid destination vertex %u in adjacency list of %u", 
                               current->to, i);
                return false;
            }
            if (current->weight < 0) {
                SSSP_LOG_ERROR("Negative edge weight %.2f in edge %u -> %u", 
                               current->weight, i, current->to);
                return false;
            }
            list_count++;
            current = current->next;
        }
        
        if (list_count != graph->adj_list[i].count) {
            SSSP_LOG_ERROR("Edge count mismatch for vertex %u: stored=%u, counted=%u", 
                           i, graph->adj_list[i].count, list_count);
            return false;
        }
    }
    
    if (counted_edges != graph->num_edges) {
        SSSP_LOG_ERROR("Total edge count mismatch: stored=%u, counted=%u", 
                       graph->num_edges, counted_edges);
        return false;
    }
    
    return true;
}

/**
 * Load graph from file (simple format: num_vertices, then edges as "from to weight")
 */
sssp_graph_t* sssp_graph_load_from_file(const char* filename, const sssp_allocator_t* allocator) {
    if (!filename) {
        SSSP_LOG_ERROR("Filename is NULL");
        return NULL;
    }
    
    SSSP_LOG_INFO("Loading graph from file: %s", filename);
    
    FILE* file = fopen(filename, "r");
    if (!file) {
        SSSP_LOG_ERROR("Failed to open file %s: %s", filename, strerror(errno));
        return NULL;
    }
    
    vertex_count_t num_vertices;
    if (fscanf(file, "%u", &num_vertices) != 1) {
        SSSP_LOG_ERROR("Failed to read number of vertices from file");
        fclose(file);
        return NULL;
    }
    
    sssp_graph_t* graph = sssp_graph_create(num_vertices, allocator);
    if (!graph) {
        SSSP_LOG_ERROR("Failed to create graph");
        fclose(file);
        return NULL;
    }
    
    vertex_id_t from, to;
    edge_weight_t weight;
    edge_count_t edges_read = 0;
    
    while (fscanf(file, "%u %u %lf", &from, &to, &weight) == 3) {
        sssp_error_t result = sssp_graph_add_edge(graph, from, to, weight);
        if (result != SSSP_SUCCESS) {
            SSSP_LOG_ERROR("Failed to add edge %u -> %u (weight=%.2f)", from, to, weight);
            sssp_graph_destroy(graph);
            fclose(file);
            return NULL;
        }
        edges_read++;
    }
    
    fclose(file);
    
    SSSP_LOG_INFO("Successfully loaded graph: %u vertices, %u edges", 
                  num_vertices, edges_read);
    
    return graph;
}

/**
 * Save graph to file
 */
sssp_error_t sssp_graph_save_to_file(const sssp_graph_t* graph, const char* filename) {
    if (!graph || !filename) {
        SSSP_LOG_ERROR("Invalid parameters: graph=%p, filename=%p", 
                       (void*)graph, (void*)filename);
        return SSSP_ERROR_INVALID_PARAMETER;
    }
    
    SSSP_LOG_INFO("Saving graph to file: %s", filename);
    
    FILE* file = fopen(filename, "w");
    if (!file) {
        SSSP_LOG_ERROR("Failed to open file %s for writing: %s", filename, strerror(errno));
        return SSSP_ERROR_IO;
    }
    
    // Write number of vertices
    fprintf(file, "%u\n", graph->num_vertices);
    
    // Write all edges
    for (vertex_count_t i = 0; i < graph->num_vertices; i++) {
        sssp_edge_node_t* current = graph->adj_list[i].head;
        while (current) {
            fprintf(file, "%u %u %.6f\n", i, current->to, current->weight);
            current = current->next;
        }
    }
    
    fclose(file);
    
    SSSP_LOG_INFO("Graph saved successfully: %u vertices, %u edges", 
                  graph->num_vertices, graph->num_edges);
    
    return SSSP_SUCCESS;
}

/**
 * Print graph statistics
 */
void sssp_graph_print_stats(const sssp_graph_t* graph) {
    if (!graph) {
        printf("Graph: NULL\n");
        return;
    }
    
    printf("Graph Statistics:\n");
    printf("  Vertices: %u\n", graph->num_vertices);
    printf("  Edges: %u\n", graph->num_edges);
    
    if (graph->num_vertices > 0) {
        // Calculate degree statistics
        edge_count_t min_degree = UINT32_MAX;
        edge_count_t max_degree = 0;
        edge_count_t total_degree = 0;
        
        for (vertex_count_t i = 0; i < graph->num_vertices; i++) {
            edge_count_t degree = graph->adj_list[i].count;
            if (degree < min_degree) min_degree = degree;
            if (degree > max_degree) max_degree = degree;
            total_degree += degree;
        }
        
        if (min_degree == UINT32_MAX) min_degree = 0;
        
        printf("  Average degree: %.2f\n", (double)total_degree / graph->num_vertices);
        printf("  Min degree: %u\n", min_degree);
        printf("  Max degree: %u\n", max_degree);
        printf("  Density: %.6f\n", 
               (double)graph->num_edges / (graph->num_vertices * (graph->num_vertices - 1)));
    }
}
