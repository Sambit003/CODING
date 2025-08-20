/**
 * @file test_sssp.c
 * @brief Comprehensive test suite for the SSSP implementation
 * 
 * @author Sambit Chakraborty
 * @date 21-08-2025
 * @version 1.0
 */

#include "sssp_algorithm.h"
#include "graph.h"
#include "partitioning_heap.h"
#include "find_pivots.h"
#include "vertex_set.h"
#include "sssp_common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define TEST_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "TEST FAILED: %s\n", message); \
            return false; \
        } \
    } while(0)

#define TEST_PASS(test_name) \
    printf("✓ %s passed\n", test_name)

/**
 * Test vertex set operations
 */
static bool test_vertex_set() {
    sssp_vertex_set_t* set = sssp_vertex_set_create(10, NULL);
    TEST_ASSERT(set != NULL, "Failed to create vertex set");
    
    // Test empty set
    TEST_ASSERT(sssp_vertex_set_size(set) == 0, "Empty set should have size 0");
    TEST_ASSERT(sssp_vertex_set_is_empty(set), "Empty set should be empty");
    TEST_ASSERT(!sssp_vertex_set_contains(set, 0), "Empty set should not contain vertex 0");
    
    // Test adding vertices
    TEST_ASSERT(sssp_vertex_set_add(set, 5) == SSSP_SUCCESS, "Failed to add vertex 5");
    TEST_ASSERT(sssp_vertex_set_size(set) == 1, "Set should have size 1 after adding vertex");
    TEST_ASSERT(!sssp_vertex_set_is_empty(set), "Set should not be empty after adding vertex");
    TEST_ASSERT(sssp_vertex_set_contains(set, 5), "Set should contain vertex 5");
    TEST_ASSERT(!sssp_vertex_set_contains(set, 4), "Set should not contain vertex 4");
    
    // Test adding duplicate
    TEST_ASSERT(sssp_vertex_set_add(set, 5) == SSSP_ERROR_INVALID_PARAMETER, 
                "Adding duplicate vertex should fail");
    TEST_ASSERT(sssp_vertex_set_size(set) == 1, "Size should remain 1 after duplicate add");
    
    // Test adding more vertices
    TEST_ASSERT(sssp_vertex_set_add(set, 0) == SSSP_SUCCESS, "Failed to add vertex 0");
    TEST_ASSERT(sssp_vertex_set_add(set, 9) == SSSP_SUCCESS, "Failed to add vertex 9");
    TEST_ASSERT(sssp_vertex_set_size(set) == 3, "Set should have size 3");
    
    // Test getting vertices
    TEST_ASSERT(sssp_vertex_set_get_vertex(set, 0) != SSSP_INVALID_VERTEX, 
                "Should be able to get vertex at index 0");
    TEST_ASSERT(sssp_vertex_set_get_vertex(set, 3) == SSSP_INVALID_VERTEX, 
                "Should not be able to get vertex at invalid index");
    
    // Test removing vertices
    TEST_ASSERT(sssp_vertex_set_remove(set, 5) == SSSP_SUCCESS, "Failed to remove vertex 5");
    TEST_ASSERT(sssp_vertex_set_size(set) == 2, "Set should have size 2 after removal");
    TEST_ASSERT(!sssp_vertex_set_contains(set, 5), "Set should not contain removed vertex 5");
    
    // Test removing non-existent vertex
    TEST_ASSERT(sssp_vertex_set_remove(set, 5) == SSSP_ERROR_INVALID_PARAMETER, 
                "Removing non-existent vertex should fail");
    
    // Test clear
    sssp_vertex_set_clear(set);
    TEST_ASSERT(sssp_vertex_set_size(set) == 0, "Set should be empty after clear");
    TEST_ASSERT(sssp_vertex_set_is_empty(set), "Set should be empty after clear");
    
    sssp_vertex_set_destroy(set);
    TEST_PASS("test_vertex_set");
    return true;
}

/**
 * Test graph operations
 */
static bool test_graph() {
    sssp_graph_t* graph = sssp_graph_create(5, NULL);
    TEST_ASSERT(graph != NULL, "Failed to create graph");
    
    // Test empty graph
    TEST_ASSERT(sssp_graph_get_vertex_count(graph) == 5, "Graph should have 5 vertices");
    TEST_ASSERT(sssp_graph_get_edge_count(graph) == 0, "Empty graph should have 0 edges");
    
    // Test adding edges
    TEST_ASSERT(sssp_graph_add_edge(graph, 0, 1, 1.0) == SSSP_SUCCESS, 
                "Failed to add edge 0->1");
    TEST_ASSERT(sssp_graph_add_edge(graph, 0, 2, 2.5) == SSSP_SUCCESS, 
                "Failed to add edge 0->2");
    TEST_ASSERT(sssp_graph_add_edge(graph, 1, 3, 1.5) == SSSP_SUCCESS, 
                "Failed to add edge 1->3");
    TEST_ASSERT(sssp_graph_add_edge(graph, 2, 4, 3.0) == SSSP_SUCCESS, 
                "Failed to add edge 2->4");
    
    TEST_ASSERT(sssp_graph_get_edge_count(graph) == 4, "Graph should have 4 edges");
    
    // Test invalid edge additions
    TEST_ASSERT(sssp_graph_add_edge(graph, 5, 0, 1.0) == SSSP_ERROR_INVALID_PARAMETER, 
                "Adding edge from invalid vertex should fail");
    TEST_ASSERT(sssp_graph_add_edge(graph, 0, 5, 1.0) == SSSP_ERROR_INVALID_PARAMETER, 
                "Adding edge to invalid vertex should fail");
    TEST_ASSERT(sssp_graph_add_edge(graph, 0, 1, -1.0) == SSSP_ERROR_INVALID_PARAMETER, 
                "Adding edge with negative weight should fail");
    
    // Test adjacency lists
    const sssp_adj_list_t* adj_list = sssp_graph_get_adj_list(graph, 0);
    TEST_ASSERT(adj_list != NULL, "Should get adjacency list for vertex 0");
    TEST_ASSERT(adj_list->count == 2, "Vertex 0 should have 2 outgoing edges");
    
    adj_list = sssp_graph_get_adj_list(graph, 4);
    TEST_ASSERT(adj_list != NULL, "Should get adjacency list for vertex 4");
    TEST_ASSERT(adj_list->count == 0, "Vertex 4 should have 0 outgoing edges");
    
    sssp_graph_destroy(graph);
    TEST_PASS("test_graph");
    return true;
}

/**
 * Test partitioning heap operations
 */
static bool test_partitioning_heap() {
    sssp_partitioning_heap_t* heap = sssp_partitioning_heap_create(10, NULL);
    TEST_ASSERT(heap != NULL, "Failed to create partitioning heap");
    
    // Test empty heap
    TEST_ASSERT(sssp_partitioning_heap_is_empty(heap), "Empty heap should be empty");
    TEST_ASSERT(sssp_partitioning_heap_size(heap) == 0, "Empty heap should have size 0");
    TEST_ASSERT(!sssp_partitioning_heap_contains(heap, 0), "Empty heap should not contain vertex 0");
    
    // Test insertions
    TEST_ASSERT(sssp_partitioning_heap_insert(heap, 5, 10.0) == SSSP_SUCCESS, 
                "Failed to insert vertex 5");
    TEST_ASSERT(sssp_partitioning_heap_insert(heap, 2, 5.0) == SSSP_SUCCESS, 
                "Failed to insert vertex 2");
    TEST_ASSERT(sssp_partitioning_heap_insert(heap, 8, 15.0) == SSSP_SUCCESS, 
                "Failed to insert vertex 8");
    TEST_ASSERT(sssp_partitioning_heap_insert(heap, 1, 3.0) == SSSP_SUCCESS, 
                "Failed to insert vertex 1");
    
    TEST_ASSERT(sssp_partitioning_heap_size(heap) == 4, "Heap should have size 4");
    TEST_ASSERT(!sssp_partitioning_heap_is_empty(heap), "Heap should not be empty");
    TEST_ASSERT(sssp_partitioning_heap_contains(heap, 1), "Heap should contain vertex 1");
    TEST_ASSERT(!sssp_partitioning_heap_contains(heap, 0), "Heap should not contain vertex 0");
    
    // Test heap property (min-heap)
    TEST_ASSERT(sssp_partitioning_heap_is_valid(heap), "Heap should be valid");
    
    // Test extract min
    vertex_id_t vertex;
    distance_t distance;
    TEST_ASSERT(sssp_partitioning_heap_extract_min(heap, &vertex, &distance) == SSSP_SUCCESS, 
                "Failed to extract min");
    TEST_ASSERT(vertex == 1 && distance == 3.0, "Min should be vertex 1 with distance 3.0");
    TEST_ASSERT(sssp_partitioning_heap_size(heap) == 3, "Heap should have size 3 after extraction");
    
    // Test decrease key
    TEST_ASSERT(sssp_partitioning_heap_decrease_key(heap, 8, 4.0) == SSSP_SUCCESS, 
                "Failed to decrease key for vertex 8");
    TEST_ASSERT(sssp_partitioning_heap_get_distance(heap, 8) == 4.0, 
                "Distance for vertex 8 should be updated");
    TEST_ASSERT(sssp_partitioning_heap_is_valid(heap), "Heap should be valid after decrease key");
    
    // Test that vertex 8 is now the minimum
    TEST_ASSERT(sssp_partitioning_heap_extract_min(heap, &vertex, &distance) == SSSP_SUCCESS, 
                "Failed to extract min after decrease key");
    TEST_ASSERT(vertex == 8 && distance == 4.0, "Min should now be vertex 8 with distance 4.0");
    
    sssp_partitioning_heap_destroy(heap);
    TEST_PASS("test_partitioning_heap");
    return true;
}

/**
 * Test SSSP solver on a simple graph
 */
static bool test_simple_sssp() {
    // Create a simple graph: 0 -> 1 -> 2 -> 3
    //                            \-> 3 (direct path)
    sssp_graph_t* graph = sssp_graph_create(4, NULL);
    TEST_ASSERT(graph != NULL, "Failed to create graph");
    
    TEST_ASSERT(sssp_graph_add_edge(graph, 0, 1, 1.0) == SSSP_SUCCESS, "Failed to add edge 0->1");
    TEST_ASSERT(sssp_graph_add_edge(graph, 1, 2, 2.0) == SSSP_SUCCESS, "Failed to add edge 1->2");
    TEST_ASSERT(sssp_graph_add_edge(graph, 2, 3, 1.0) == SSSP_SUCCESS, "Failed to add edge 2->3");
    TEST_ASSERT(sssp_graph_add_edge(graph, 1, 3, 5.0) == SSSP_SUCCESS, "Failed to add edge 1->3");
    
    // Create result structure
    sssp_algorithm_result_t* result = sssp_algorithm_result_create(4, NULL);
    TEST_ASSERT(result != NULL, "Failed to create algorithm result");
    
    // Solve single-source from vertex 0
    TEST_ASSERT(sssp_solve_single_source(graph, 0, NULL, result) == SSSP_SUCCESS, 
                "Failed to solve single-source SSSP");
    
    // Check distances
    TEST_ASSERT(result->distances[0] == 0.0, "Distance to source should be 0");
    TEST_ASSERT(result->distances[1] == 1.0, "Distance to vertex 1 should be 1.0");
    TEST_ASSERT(result->distances[2] == 3.0, "Distance to vertex 2 should be 3.0");
    TEST_ASSERT(result->distances[3] == 4.0, "Distance to vertex 3 should be 4.0");
    
    // Check predecessors
    TEST_ASSERT(result->predecessors[0] == SSSP_INVALID_VERTEX, 
                "Source should have no predecessor");
    TEST_ASSERT(result->predecessors[1] == 0, "Predecessor of vertex 1 should be 0");
    TEST_ASSERT(result->predecessors[2] == 1, "Predecessor of vertex 2 should be 1");
    TEST_ASSERT(result->predecessors[3] == 2, "Predecessor of vertex 3 should be 2");
    
    sssp_algorithm_result_destroy(result);
    sssp_graph_destroy(graph);
    TEST_PASS("test_simple_sssp");
    return true;
}

/**
 * Test multi-source SSSP using Algorithm 3
 */
static bool test_multi_source_sssp() {
    // Create a graph with multiple sources
    sssp_graph_t* graph = sssp_graph_create(6, NULL);
    TEST_ASSERT(graph != NULL, "Failed to create graph");
    
    // Add edges creating a connected graph
    TEST_ASSERT(sssp_graph_add_edge(graph, 0, 1, 2.0) == SSSP_SUCCESS, "Failed to add edge 0->1");
    TEST_ASSERT(sssp_graph_add_edge(graph, 1, 2, 1.0) == SSSP_SUCCESS, "Failed to add edge 1->2");
    TEST_ASSERT(sssp_graph_add_edge(graph, 3, 4, 1.5) == SSSP_SUCCESS, "Failed to add edge 3->4");
    TEST_ASSERT(sssp_graph_add_edge(graph, 4, 5, 2.0) == SSSP_SUCCESS, "Failed to add edge 4->5");
    TEST_ASSERT(sssp_graph_add_edge(graph, 2, 5, 10.0) == SSSP_SUCCESS, "Failed to add edge 2->5");
    TEST_ASSERT(sssp_graph_add_edge(graph, 0, 3, 8.0) == SSSP_SUCCESS, "Failed to add edge 0->3");
    
    // Create vertex sets and configuration
    sssp_vertex_set_t* source_set = sssp_vertex_set_create(6, NULL);
    sssp_vertex_set_t* output_set = sssp_vertex_set_create(6, NULL);
    TEST_ASSERT(source_set != NULL && output_set != NULL, "Failed to create vertex sets");
    
    // Add sources 0 and 3
    TEST_ASSERT(sssp_vertex_set_add(source_set, 0) == SSSP_SUCCESS, "Failed to add source 0");
    TEST_ASSERT(sssp_vertex_set_add(source_set, 3) == SSSP_SUCCESS, "Failed to add source 3");
    
    // Create configuration
    sssp_algorithm_config_t config = sssp_algorithm_config_default(6, NULL);
    
    // Test Algorithm 3 (bounded multi-source)
    weight_t B_prime;
    weight_t threshold = 10.0; // Large enough threshold
    
    sssp_error_t result = sssp_bounded_multi_source(graph, 0, threshold, source_set,
                                                    config.k, config.t, &config,
                                                    output_set, &B_prime);
    
    TEST_ASSERT(result == SSSP_SUCCESS, "Failed to solve multi-source SSSP");
    TEST_ASSERT(B_prime >= 0.0, "B_prime should be non-negative");
    TEST_ASSERT(sssp_vertex_set_size(output_set) > 0, "Should find some vertices within threshold");
    
    sssp_vertex_set_destroy(source_set);
    sssp_vertex_set_destroy(output_set);
    sssp_graph_destroy(graph);
    TEST_PASS("test_multi_source_sssp");
    return true;
}

/**
 * Test bounded SSSP using base case algorithm
 */
static bool test_bounded_sssp() {
    // Create a chain graph: 0 -> 1 -> 2 -> 3 -> 4
    sssp_graph_t* graph = sssp_graph_create(5, NULL);
    TEST_ASSERT(graph != NULL, "Failed to create graph");
    
    for (vertex_id_t i = 0; i < 4; i++) {
        TEST_ASSERT(sssp_graph_add_edge(graph, i, i + 1, 1.0) == SSSP_SUCCESS, 
                    "Failed to add edge in chain");
    }
    
    // Create vertex sets
    sssp_vertex_set_t* source_set = sssp_vertex_set_create(5, NULL);
    sssp_vertex_set_t* output_set = sssp_vertex_set_create(5, NULL);
    TEST_ASSERT(source_set != NULL && output_set != NULL, "Failed to create vertex sets");
    
    // Add source vertex 0
    TEST_ASSERT(sssp_vertex_set_add(source_set, 0) == SSSP_SUCCESS, "Failed to add source");
    
    // Create configuration
    sssp_algorithm_config_t config = sssp_algorithm_config_default(5, NULL);
    
    // Test base case with distance bound of 2.5
    weight_t B_prime;
    weight_t threshold = 2.5;
    
    sssp_error_t result = sssp_base_case(graph, threshold, source_set, config.k, 
                                        &config, output_set, &B_prime);
    
    TEST_ASSERT(result == SSSP_SUCCESS, "Failed to solve bounded SSSP");
    TEST_ASSERT(B_prime <= threshold, "B_prime should not exceed threshold");
    
    // Check that vertices within bound are found
    vertex_count_t output_size = sssp_vertex_set_size(output_set);
    TEST_ASSERT(output_size >= 3, "Should find at least vertices 0, 1, 2 within bound");
    TEST_ASSERT(output_size <= 5, "Should not find more vertices than exist");
    
    sssp_vertex_set_destroy(source_set);
    sssp_vertex_set_destroy(output_set);
    sssp_graph_destroy(graph);
    TEST_PASS("test_bounded_sssp");
    return true;
}

/**
 * Test pivot finding algorithm
 */
static bool test_pivot_finding() {
    // Create a small complete graph
    const vertex_count_t n = 5;
    sssp_graph_t* graph = sssp_graph_create(n, NULL);
    TEST_ASSERT(graph != NULL, "Failed to create graph");
    
    // Add all possible edges with unit weights
    for (vertex_id_t i = 0; i < n; i++) {
        for (vertex_id_t j = 0; j < n; j++) {
            if (i != j) {
                TEST_ASSERT(sssp_graph_add_edge(graph, i, j, 1.0) == SSSP_SUCCESS, 
                            "Failed to add edge in complete graph");
            }
        }
    }
    
    // Create vertex set with all vertices
    sssp_vertex_set_t* vertex_set = sssp_vertex_set_create(n, NULL);
    TEST_ASSERT(vertex_set != NULL, "Failed to create vertex set");
    
    for (vertex_id_t i = 0; i < n; i++) {
        TEST_ASSERT(sssp_vertex_set_add(vertex_set, i) == SSSP_SUCCESS, 
                    "Failed to add vertex to set");
    }
    
    // Create configuration and result structures
    sssp_find_pivots_config_t config = sssp_find_pivots_config_default(NULL);
    sssp_find_pivots_result_t* result = sssp_find_pivots_result_create(NULL);
    TEST_ASSERT(result != NULL, "Failed to create pivot result");
    
    // Find pivots with target diameter 1.5
    vertex_count_t k = 2; // Small k for testing
    sssp_error_t error = sssp_find_pivots(graph, 1.5, vertex_set, k, &config, result);
    TEST_ASSERT(error == SSSP_SUCCESS, "Failed to find pivots");
    
    vertex_count_t num_pivots = sssp_vertex_set_size(result->pivots);
    TEST_ASSERT(num_pivots <= n, "Should not find more pivots than vertices");
    
    // Validate pivot vertices
    for (vertex_count_t i = 0; i < num_pivots; i++) {
        vertex_id_t pivot = sssp_vertex_set_get_vertex(result->pivots, i);
        TEST_ASSERT(pivot < n, "Pivot should be valid vertex");
    }
    
    sssp_find_pivots_result_destroy(result);
    sssp_vertex_set_destroy(vertex_set);
    sssp_graph_destroy(graph);
    TEST_PASS("test_pivot_finding");
    return true;
}

/**
 * Test with disconnected graph
 */
static bool test_disconnected_graph() {
    // Create two disconnected components: {0,1} and {2,3}
    sssp_graph_t* graph = sssp_graph_create(4, NULL);
    TEST_ASSERT(graph != NULL, "Failed to create graph");
    
    TEST_ASSERT(sssp_graph_add_edge(graph, 0, 1, 1.0) == SSSP_SUCCESS, "Failed to add edge 0->1");
    TEST_ASSERT(sssp_graph_add_edge(graph, 2, 3, 2.0) == SSSP_SUCCESS, "Failed to add edge 2->3");
    
    // Create result structure
    sssp_algorithm_result_t* result = sssp_algorithm_result_create(4, NULL);
    TEST_ASSERT(result != NULL, "Failed to create algorithm result");
    
    // Solve from vertex 0
    TEST_ASSERT(sssp_solve_single_source(graph, 0, NULL, result) == SSSP_SUCCESS, 
                "Failed to solve SSSP on disconnected graph");
    
    // Check reachability
    TEST_ASSERT(result->distances[0] == 0.0, "Source should have distance 0");
    TEST_ASSERT(result->distances[1] == 1.0, "Connected vertex should be reachable");
    TEST_ASSERT(result->distances[2] == SSSP_INFINITY, 
                "Disconnected vertex should be unreachable");
    TEST_ASSERT(result->distances[3] == SSSP_INFINITY, 
                "Disconnected vertex should be unreachable");
    
    sssp_algorithm_result_destroy(result);
    sssp_graph_destroy(graph);
    TEST_PASS("test_disconnected_graph");
    return true;
}

/**
 * Test parameter computation utilities
 */
static bool test_parameter_computation() {
    // Test k computation
    vertex_count_t k1 = sssp_compute_optimal_k(1);
    vertex_count_t k16 = sssp_compute_optimal_k(16);
    vertex_count_t k1000 = sssp_compute_optimal_k(1000);
    
    TEST_ASSERT(k1 >= 1, "k should be at least 1");
    TEST_ASSERT(k16 > k1, "k should increase with vertex count");
    TEST_ASSERT(k1000 > k16, "k should increase with vertex count");
    
    // Test t computation
    vertex_count_t t1 = sssp_compute_optimal_t(1);
    vertex_count_t t100 = sssp_compute_optimal_t(100);
    vertex_count_t t1000 = sssp_compute_optimal_t(1000);
    
    TEST_ASSERT(t1 >= 1, "t should be at least 1");
    TEST_ASSERT(t100 > t1, "t should increase with vertex count");
    TEST_ASSERT(t1000 > t100, "t should increase with vertex count");
    
    // Test recursion depth computation
    vertex_count_t depth = sssp_compute_optimal_recursion_depth(1000, 10);
    TEST_ASSERT(depth >= 1, "Recursion depth should be at least 1");
    TEST_ASSERT(depth < 1000, "Recursion depth should be reasonable");
    
    TEST_PASS("test_parameter_computation");
    return true;
}

/**
 * Run all tests
 */
int main() {
    printf("=== Production SSSP Algorithm Test Suite ===\n\n");
    
    int tests_passed = 0;
    int total_tests = 0;
    
    printf("Running component tests...\n");
    
    total_tests++;
    if (test_vertex_set()) tests_passed++;
    
    total_tests++;
    if (test_graph()) tests_passed++;
    
    total_tests++;
    if (test_partitioning_heap()) tests_passed++;
    
    printf("\nRunning algorithm tests...\n");
    
    total_tests++;
    if (test_simple_sssp()) tests_passed++;
    
    total_tests++;
    if (test_multi_source_sssp()) tests_passed++;
    
    total_tests++;
    if (test_bounded_sssp()) tests_passed++;
    
    total_tests++;
    if (test_pivot_finding()) tests_passed++;
    
    total_tests++;
    if (test_disconnected_graph()) tests_passed++;
    
    total_tests++;
    if (test_parameter_computation()) tests_passed++;
    
    printf("\n=== TEST RESULTS ===\n");
    printf("Tests passed: %d/%d\n", tests_passed, total_tests);
    
    if (tests_passed == total_tests) {
        printf("🎉 All tests passed!\n");
        return 0;
    } else {
        printf("❌ Some tests failed.\n");
        return 1;
    }
}
