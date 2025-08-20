/**
 * @file demo.c
 * @brief Demo program showcasing the production SSSP implementation
 * 
 * @author Sambit Chakraborty
 * @date 21-08-2025
 * @version 1.0
 */

#include "sssp_algorithm.h"
#include "graph.h"
#include "sssp_common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Add missing string functions
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

/**
 * Print usage information
 */
static void print_usage(const char* program_name) {
    printf("Usage: %s [options]\n", program_name);
    printf("Options:\n");
    printf("  -f <file>       Load graph from file\n");
    printf("  -g <vertices>   Generate random graph with specified number of vertices\n");
    printf("  -s <source>     Single source vertex (default: 0)\n");
    printf("  -m <sources>    Multi-source (comma-separated list)\n");
    printf("  -d <distance>   Maximum distance bound (default: infinity)\n");
    printf("  -v              Verbose output\n");
    printf("  -h              Show this help\n");
    printf("\nExamples:\n");
    printf("  %s -g 1000                    # Random graph with 1000 vertices\n", program_name);
    printf("  %s -f graph.txt -s 5          # Load graph from file, source vertex 5\n", program_name);
    printf("  %s -g 500 -m 0,10,20 -d 100   # Multi-source with distance bound\n", program_name);
}

/**
 * Generate a random graph for testing
 */
static sssp_graph_t* generate_random_graph(vertex_count_t num_vertices, double edge_probability,
                                            double max_weight) {
    printf("Generating random graph: %u vertices, edge probability %.3f, max weight %.2f\n",
           num_vertices, edge_probability, max_weight);
    
    sssp_graph_t* graph = sssp_graph_create(num_vertices, NULL);
    if (!graph) {
        fprintf(stderr, "Failed to create graph\n");
        return NULL;
    }
    
    srand((unsigned int)time(NULL));
    
    edge_count_t edges_added = 0;
    for (vertex_id_t u = 0; u < num_vertices; u++) {
        for (vertex_id_t v = 0; v < num_vertices; v++) {
            if (u != v && ((double)rand() / RAND_MAX) < edge_probability) {
                double weight = ((double)rand() / RAND_MAX) * max_weight;
                if (sssp_graph_add_edge(graph, u, v, weight) == SSSP_SUCCESS) {
                    edges_added++;
                }
            }
        }
    }
    
    printf("Generated graph with %u edges\n", edges_added);
    return graph;
}

/**
 * Parse comma-separated list of source vertices
 */
static vertex_count_t parse_sources(const char* sources_str, vertex_id_t** sources_out) {
    if (!sources_str || !sources_out) return 0;
    
    // Count commas to estimate number of sources
    vertex_count_t count = 1;
    for (const char* p = sources_str; *p; p++) {
        if (*p == ',') count++;
    }
    
    *sources_out = malloc(count * sizeof(vertex_id_t));
    if (!*sources_out) return 0;
    
    // Parse the sources - manual string duplication
    size_t len = strlen(sources_str);
    char* str_copy = malloc(len + 1);
    if (!str_copy) {
        free(*sources_out);
        *sources_out = NULL;
        return 0;
    }
    strcpy(str_copy, sources_str);
    
    vertex_count_t actual_count = 0;
    char* token = strtok(str_copy, ",");
    while (token && actual_count < count) {
        (*sources_out)[actual_count] = (vertex_id_t)atoi(token);
        actual_count++;
        token = strtok(NULL, ",");
    }
    
    free(str_copy);
    return actual_count;
}

/**
 * Print shortest path from source to target using algorithm result
 */
static void print_path(const sssp_algorithm_result_t* result, vertex_id_t source, vertex_id_t target) {
    if (result->distances[target] == SSSP_INFINITY) {
        printf("No path from %u to %u\n", source, target);
        return;
    }
    
    // Build path by following predecessors
    vertex_id_t path[1000]; // Reasonable limit
    int path_length = 0;
    vertex_id_t current = target;
    
    while (current != SSSP_INVALID_VERTEX && path_length < 1000) {
        path[path_length++] = current;
        current = result->predecessors[current];
    }
    
    printf("Path from %u to %u (distance %.2f): ", 
           source, target, result->distances[target]);
    
    for (int i = path_length - 1; i >= 0; i--) {
        printf("%u", path[i]);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
}

/**
 * Print summary of results
 */
static void print_results_summary(const sssp_algorithm_result_t* result, const sssp_graph_t* graph,
                                  const vertex_id_t* sources, vertex_count_t num_sources) {
    vertex_count_t num_vertices = sssp_graph_get_vertex_count(graph);
    edge_count_t num_edges = 0; // We'll count edges manually since function might not exist
    
    // Count edges manually
    for (vertex_count_t v = 0; v < num_vertices; v++) {
        const sssp_adj_list_t* adj_list = sssp_graph_get_adj_list(graph, v);
        if (adj_list) {
            sssp_edge_node_t* edge = adj_list->head;
            while (edge) {
                num_edges++;
                edge = edge->next;
            }
        }
    }
    
    printf("\n=== RESULTS SUMMARY ===\n");
    printf("Graph: %u vertices, %u edges\n", num_vertices, num_edges);
    printf("Sources: %u vertices\n", num_sources);
    
    // Count reachable vertices and compute statistics
    vertex_count_t reachable = 0;
    weight_t min_dist = SSSP_INFINITY, max_dist = 0.0, total_dist = 0.0;
    
    for (vertex_count_t v = 0; v < num_vertices; v++) {
        weight_t dist = result->distances[v];
        if (dist < SSSP_INFINITY) {
            reachable++;
            if (dist < min_dist) min_dist = dist;
            if (dist > max_dist) max_dist = dist;
            total_dist += dist;
        }
    }
    
    printf("Reachable vertices: %u (%.1f%%)\n", reachable, 
           100.0 * reachable / num_vertices);
    
    if (reachable > 0) {
        printf("Distance range: %.2f to %.2f\n", min_dist, max_dist);
        printf("Average distance: %.2f\n", total_dist / reachable);
    }
    
    printf("\n=== ALGORITHM STATISTICS ===\n");
    printf("Vertices processed: %u\n", result->vertices_processed);
    printf("Edges relaxed: %lu\n", result->relaxations_performed);
    printf("Recursive calls: %u\n", result->recursive_calls);
    printf("Total time: %.3f ms\n", result->total_time_ms);
    
    // Show some example paths
    printf("\n=== EXAMPLE PATHS ===\n");
    for (vertex_count_t i = 0; i < num_sources && i < 3; i++) {
        vertex_id_t source = sources[i];
        
        // Find a few interesting targets
        vertex_id_t targets[] = {
            num_vertices - 1,           // Last vertex
            num_vertices / 2,           // Middle vertex
            (source + num_vertices / 4) % num_vertices  // Offset vertex
        };
        
        for (int j = 0; j < 3 && j < (int)num_vertices; j++) {
            if (targets[j] != source) {
                print_path(result, source, targets[j]);
            }
        }
    }
}

/**
 * Benchmark the algorithm
 */
static void run_benchmark(const sssp_graph_t* graph, const vertex_id_t* sources, 
                          vertex_count_t num_sources, distance_t max_distance) {
    printf("\n=== BENCHMARK ===\n");
    
    vertex_count_t num_vertices = sssp_graph_get_vertex_count(graph);
    
    const int NUM_RUNS = 5;
    double total_time = 0.0;
    
    for (int run = 0; run < NUM_RUNS; run++) {
        // Create result structure for this run
        sssp_algorithm_result_t* result = sssp_algorithm_result_create(num_vertices, NULL);
        if (!result) {
            fprintf(stderr, "Failed to create result structure for run %d\n", run + 1);
            return;
        }
        
        clock_t start = clock();
        
        sssp_error_t error;
        if (num_sources == 1) {
            // Single source case
            error = sssp_solve_single_source(graph, sources[0], NULL, result);
        } else {
            // Multi-source case - use Algorithm 3 via bounded multi-source
            sssp_algorithm_config_t config = sssp_algorithm_config_default(num_vertices, NULL);
            sssp_vertex_set_t* source_set = sssp_vertex_set_create(num_vertices, NULL);
            sssp_vertex_set_t* output_set = sssp_vertex_set_create(num_vertices, NULL);
            
            if (!source_set || !output_set) {
                fprintf(stderr, "Failed to create vertex sets for run %d\n", run + 1);
                if (source_set) sssp_vertex_set_destroy(source_set);
                if (output_set) sssp_vertex_set_destroy(output_set);
                sssp_algorithm_result_destroy(result);
                return;
            }
            
            // Add sources to set
            for (vertex_count_t i = 0; i < num_sources; i++) {
                sssp_vertex_set_add(source_set, sources[i]);
            }
            
            weight_t B_prime;
            weight_t threshold = (max_distance == SSSP_INFINITY) ? 1000.0 : max_distance;
            
            error = sssp_bounded_multi_source(graph, 0, threshold, source_set,
                                             config.k, config.t, &config,
                                             output_set, &B_prime);
            
            sssp_vertex_set_destroy(source_set);
            sssp_vertex_set_destroy(output_set);
        }
        
        clock_t end = clock();
        
        if (error != SSSP_SUCCESS) {
            fprintf(stderr, "Algorithm failed in run %d with error %d\n", run + 1, error);
            sssp_algorithm_result_destroy(result);
            return;
        }
        
        double run_time = (double)(end - start) / CLOCKS_PER_SEC;
        total_time += run_time;
        printf("Run %d: %.3f seconds\n", run + 1, run_time);
        
        sssp_algorithm_result_destroy(result);
    }
    
    double avg_time = total_time / NUM_RUNS;
    printf("Average time: %.3f seconds\n", avg_time);
}

/**
 * Main demo program
 */
int main(int argc, char* argv[]) {
    // Default parameters
    const char* graph_file = NULL;
    vertex_count_t gen_vertices = 0;
    vertex_id_t single_source = 0;
    char* multi_sources_str = NULL;
    distance_t max_distance = SSSP_INFINITY;
    bool verbose = false;
    
    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            graph_file = argv[++i];
        } else if (strcmp(argv[i], "-g") == 0 && i + 1 < argc) {
            gen_vertices = (vertex_count_t)atoi(argv[++i]);
        } else if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
            single_source = (vertex_id_t)atoi(argv[++i]);
        } else if (strcmp(argv[i], "-m") == 0 && i + 1 < argc) {
            multi_sources_str = argv[++i];
        } else if (strcmp(argv[i], "-d") == 0 && i + 1 < argc) {
            max_distance = atof(argv[++i]);
        } else if (strcmp(argv[i], "-v") == 0) {
            verbose = true;
        } else if (strcmp(argv[i], "-h") == 0) {
            print_usage(argv[0]);
            return 0;
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            print_usage(argv[0]);
            return 1;
        }
    }
    
    // Configure logging - use simple approach since constants might not exist
    printf("=== Production SSSP Algorithm Demo ===\n");
    printf("Based on: Breaking the Sorting Barrier for Directed Single-Source Shortest Paths\n\n");
    
    // Load or generate graph
    sssp_graph_t* graph = NULL;
    if (graph_file) {
        printf("Loading graph from file: %s\n", graph_file);
        // Note: sssp_graph_load_from_file might not be implemented
        fprintf(stderr, "File loading not yet implemented\n");
        return 1;
    } else if (gen_vertices > 0) {
        graph = generate_random_graph(gen_vertices, 0.01, 100.0); // 1% edge probability
        if (!graph) {
            fprintf(stderr, "Failed to generate random graph\n");
            return 1;
        }
    } else {
        fprintf(stderr, "No graph specified. Use -f <file> or -g <vertices>\n");
        print_usage(argv[0]);
        return 1;
    }
    
    // Simple graph validation
    if (!graph) {
        fprintf(stderr, "Graph creation failed\n");
        return 1;
    }
    
    vertex_count_t num_vertices = sssp_graph_get_vertex_count(graph);
    printf("Graph created with %u vertices\n", num_vertices);
    
    // Setup sources
    vertex_id_t* sources = NULL;
    vertex_count_t num_sources = 0;
    
    if (multi_sources_str) {
        num_sources = parse_sources(multi_sources_str, &sources);
        if (num_sources == 0) {
            fprintf(stderr, "Failed to parse source vertices\n");
            sssp_graph_destroy(graph);
            return 1;
        }
    } else {
        // Single source
        sources = malloc(sizeof(vertex_id_t));
        if (!sources) {
            fprintf(stderr, "Memory allocation failed\n");
            sssp_graph_destroy(graph);
            return 1;
        }
        sources[0] = single_source;
        num_sources = 1;
    }
    
    // Validate sources
    for (vertex_count_t i = 0; i < num_sources; i++) {
        if (sources[i] >= num_vertices) {
            fprintf(stderr, "Invalid source vertex: %u (max: %u)\n", sources[i], num_vertices - 1);
            free(sources);
            sssp_graph_destroy(graph);
            return 1;
        }
    }
    
    printf("\nSolving SSSP with %u source(s)", num_sources);
    if (max_distance != SSSP_INFINITY) {
        printf(" and distance bound %.2f", max_distance);
    }
    printf("...\n");
    
    // Create result structure
    sssp_algorithm_result_t* result = sssp_algorithm_result_create(num_vertices, NULL);
    if (!result) {
        fprintf(stderr, "Failed to create result structure\n");
        free(sources);
        sssp_graph_destroy(graph);
        return 1;
    }
    
    // Solve the problem
    clock_t start = clock();
    
    sssp_error_t error;
    if (num_sources == 1) {
        // Single source case
        error = sssp_solve_single_source(graph, sources[0], NULL, result);
    } else {
        // Multi-source case - use Algorithm 3
        sssp_algorithm_config_t config = sssp_algorithm_config_default(num_vertices, NULL);
        sssp_vertex_set_t* source_set = sssp_vertex_set_create(num_vertices, NULL);
        sssp_vertex_set_t* output_set = sssp_vertex_set_create(num_vertices, NULL);
        
        if (!source_set || !output_set) {
            fprintf(stderr, "Failed to create vertex sets\n");
            if (source_set) sssp_vertex_set_destroy(source_set);
            if (output_set) sssp_vertex_set_destroy(output_set);
            sssp_algorithm_result_destroy(result);
            free(sources);
            sssp_graph_destroy(graph);
            return 1;
        }
        
        // Add sources to set
        for (vertex_count_t i = 0; i < num_sources; i++) {
            sssp_vertex_set_add(source_set, sources[i]);
        }
        
        weight_t B_prime;
        weight_t threshold = (max_distance == SSSP_INFINITY) ? 1000.0 : max_distance;
        
        error = sssp_bounded_multi_source(graph, 0, threshold, source_set,
                                         config.k, config.t, &config,
                                         output_set, &B_prime);
        
        // For demo purposes, we'll just report success but won't have full distance info
        printf("Multi-source algorithm completed with B' = %.2f\n", B_prime);
        
        sssp_vertex_set_destroy(source_set);
        sssp_vertex_set_destroy(output_set);
    }
    
    clock_t end = clock();
    
    if (error != SSSP_SUCCESS) {
        fprintf(stderr, "SSSP algorithm failed with error: %d\n", error);
        sssp_algorithm_result_destroy(result);
        free(sources);
        sssp_graph_destroy(graph);
        return 1;
    }
    
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Algorithm completed in %.3f seconds\n", elapsed);
    
    // Print results only for single-source case (where we have full result)
    if (num_sources == 1) {
        print_results_summary(result, graph, sources, num_sources);
    }
    
    // Run benchmark if graph is reasonably sized
    if (num_vertices >= 100 && num_vertices <= 10000) {
        run_benchmark(graph, sources, num_sources, max_distance);
    }
    
    // Cleanup
    sssp_algorithm_result_destroy(result);
    free(sources);
    sssp_graph_destroy(graph);
    
    printf("\nDemo completed successfully!\n");
    return 0;
}
