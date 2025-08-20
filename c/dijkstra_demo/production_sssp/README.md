# Production SSSP Algorithm Implementation

This is a production-grade implementation of the Single-Source Shortest Path (SSSP) algorithm based on the research paper "Breaking the Sorting Barrier for Directed Single-Source Shortest Paths" (arXiv:2504.17033v2).

## Overview

The implementation provides a modern, modular C library that implements advanced SSSP algorithms including:

- **Algorithm 1 (FINDPIVOTS)**: Efficient pivot selection for graph partitioning
- **Algorithm 3**: Bounded multi-source shortest paths with improved complexity
- **Lemma 3.3**: Partitioning heap for efficient distance-based vertex separation

## Features

### Core Algorithms

- Single-source shortest path (Dijkstra's algorithm)
- Multi-source shortest path
- Bounded shortest path with distance limits
- Advanced pivot-based graph partitioning

### Data Structures

- **Partitioning Heap**: Min-heap with O(1) decrease-key for efficient distance updates
- **Dynamic Vertex Sets**: Efficient set operations for algorithm state management
- **Adjacency List Graph**: Memory-efficient graph representation
- **Pivot Finder**: Implementation of the FINDPIVOTS algorithm

### Production Features

- Comprehensive error handling and validation
- Configurable memory allocation
- Structured logging with multiple levels
- Thread-safe design (when used properly)
- Extensive test suite
- Performance benchmarking
- Memory leak detection support

## Directory Structure

```text
production_sssp/
├── include/              # Header files
│   ├── sssp_common.h     # Common types, constants, and utilities
│   ├── graph.h           # Graph data structure interface
│   ├── vertex_set.h      # Dynamic vertex set interface
│   ├── partitioning_heap.h # Partitioning heap interface
│   ├── find_pivots.h     # FINDPIVOTS algorithm interface
│   └── sssp_algorithm.h  # Main SSSP solver interface
├── src/                  # Implementation files
│   ├── sssp_common.c     # Common utilities and error handling
│   ├── graph.c           # Graph operations
│   ├── vertex_set.c      # Vertex set operations
│   ├── partitioning_heap.c # Heap implementation
│   ├── find_pivots.c     # Pivot finding algorithm
│   └── sssp_algorithm.c  # Main SSSP algorithms
├── demo.c                # Demo program
├── test_sssp.c           # Comprehensive test suite
├── CMakeLists.txt        # CMake build configuration
└── sssp.pc.in           # pkg-config template
```

## Building

### Prerequisites

- CMake 3.10 or higher
- C17-compatible compiler (GCC 7+, Clang 6+, MSVC 2019+)
- Optional: Valgrind for memory checking
- Optional: Address Sanitizer support

### Build Instructions

```bash
# Create build directory
mkdir build && cd build

# Configure with CMake
cmake .. 

# Build the library and programs
make

# Run tests
make test
# or directly:
./test_sssp

# Run demo
./sssp_demo -g 1000000 -s 0  # Generate random graph with 1000 vertices, source 0
```

### Build Options

```bash
# Debug build with sanitizers
cmake -DCMAKE_BUILD_TYPE=Debug -DENABLE_SANITIZERS=ON ..

# Release build with optimizations
cmake -DCMAKE_BUILD_TYPE=Release ..

# Build with tests and benchmarks
cmake -DBUILD_TESTS=ON -DBUILD_BENCHMARKS=ON ..

# Generate documentation
cmake -DBUILD_DOCS=ON ..
make docs
```

## Usage

### Basic Example

```c
#include "sssp_algorithm.h"
#include "graph.h"

// Create a graph
sssp_graph_t* graph = sssp_graph_create(1000, NULL);

// Add edges
sssp_graph_add_edge(graph, 0, 1, 1.5);
sssp_graph_add_edge(graph, 1, 2, 2.0);
// ... add more edges

// Create solver
sssp_solver_t* solver = sssp_solver_create(1000, NULL);

// Solve single-source shortest path
sssp_solve_single_source(solver, graph, 0);

// Get results
distance_t dist = sssp_solver_get_distance(solver, 999);
vertex_id_t pred = sssp_solver_get_predecessor(solver, 999);

// Cleanup
sssp_solver_destroy(solver);
sssp_graph_destroy(graph);
```

### Multi-Source Example

```c
// Multiple sources
vertex_id_t sources[] = {0, 10, 20};
sssp_solve_multi_source(solver, graph, sources, 3);
```

### Bounded Distance Example

```c
// Limit search to distance 100.0
sssp_solve_bounded_multi_source(solver, graph, sources, 3, 100.0);
```

### Graph I/O

```c
// Load graph from file
sssp_graph_t* graph = sssp_graph_load_from_file("graph.txt", NULL);

// Save graph to file  
sssp_graph_save_to_file(graph, "output.txt");
```

File format:

```text
<num_vertices>
<from_vertex> <to_vertex> <weight>
<from_vertex> <to_vertex> <weight>
...
```

## Demo Program

The `demo` program provides examples of all features:

```bash
# Generate random graph and solve
./demo -g 1000 -s 0

# Load graph from file
./demo -f mygraph.txt -s 5

# Multi-source with distance bound
./demo -g 500 -m 0,10,20,30 -d 50.0

# Verbose output
./demo -g 100 -s 0 -v
```

## API Reference

### Graph Operations

- `sssp_graph_create()` - Create new graph
- `sssp_graph_add_edge()` - Add weighted edge
- `sssp_graph_load_from_file()` - Load from file
- `sssp_graph_save_to_file()` - Save to file

### Solver Operations  

- `sssp_solver_create()` - Create solver
- `sssp_solve_single_source()` - Single source SSSP
- `sssp_solve_multi_source()` - Multi-source SSSP
- `sssp_solve_bounded_multi_source()` - Bounded SSSP
- `sssp_solver_get_distance()` - Get shortest distance
- `sssp_solver_get_predecessor()` - Get predecessor in path

### Utility Operations

- `sssp_set_log_level()` - Configure logging
- `sssp_solver_get_stats()` - Get performance statistics

## Error Handling

All functions return `sssp_error_t` status codes:

- `SSSP_SUCCESS` - Operation successful
- `SSSP_ERROR_INVALID_PARAMETER` - Invalid input
- `SSSP_ERROR_OUT_OF_MEMORY` - Memory allocation failed
- `SSSP_ERROR_IO` - File I/O error
- `SSSP_ERROR_ALGORITHM` - Algorithm error

## Performance

The implementation includes several optimizations:

- **Partitioning Heap**: O(log n) operations with efficient decrease-key
- **Smart Pivoting**: Reduces recursive calls through strategic vertex selection
- **Memory Pool**: Reduced allocation overhead
- **Cache-Friendly**: Adjacency list layout optimized for memory access

### Complexity Analysis

- **Standard Dijkstra**: O((V + E) log V)
- **Multi-source**: O(S * (V + E) log V) worst case, but often much better with pivoting
- **Bounded**: O(V_reachable * log V) where V_reachable is vertices within distance bound

## Testing

The test suite (`test_sssp.c`) includes:

- Unit tests for all data structures
- Algorithm correctness tests
- Edge case handling (disconnected graphs, etc.)
- Performance benchmarks
- Memory leak detection

Run tests with:

```bash
make test
# or
./test_sssp
```

## Memory Management

The library supports custom allocators:

```c
sssp_allocator_t custom_allocator = {
    .alloc = my_alloc,
    .realloc = my_realloc,
    .free = my_free,
    .context = my_context
};

sssp_graph_t* graph = sssp_graph_create(1000, &custom_allocator);
```

## Logging

Configure logging levels:

```c
sssp_set_log_level(SSSP_LOG_LEVEL_DEBUG);  // Verbose
sssp_set_log_level(SSSP_LOG_LEVEL_INFO);   // Normal
sssp_set_log_level(SSSP_LOG_LEVEL_ERROR);  // Errors only
```

## Thread Safety

The library is thread-safe when:

- Each thread uses separate solver instances
- Graph structures are not modified concurrently
- Custom allocators are thread-safe

## Contributing

1. Follow the existing code style
2. Add tests for new features
3. Update documentation
4. Ensure all tests pass
5. Check for memory leaks with Valgrind

## Research Paper Reference

This implementation is based on:

**"Breaking the Sorting Barrier for Directed Single-Source Shortest Paths"**  
arXiv:2504.17033v2 [cs.DS]

The paper presents novel algorithms that break traditional complexity barriers for SSSP problems through advanced partitioning and pivot selection techniques.

## License

This implementation is provided for educational and research purposes. Please refer to the original research paper for algorithmic details and theoretical analysis.

## Performance Notes

### When to Use Each Algorithm

- **Single-source Dijkstra**: Small to medium graphs, single source
- **Multi-source**: Multiple sources, especially when sources are well-distributed
- **Bounded**: When you only need distances up to a certain limit
- **Pivot-based**: Large graphs with many sources where standard approaches become inefficient

### Tuning Parameters

The implementation includes several tunable parameters in `sssp_common.h`:

- `SMALL_SET_THRESHOLD`: When to switch from pivot-based to standard Dijkstra
- Heap sizes and growth factors
- Logging levels and output detail

## Troubleshooting

### Common Issues

1. **Memory allocation failures**: Check available memory, use custom allocator if needed
2. **Invalid distances**: Ensure graph has no negative edge weights
3. **Performance issues**: Use appropriate algorithm variant for your use case
4. **Build errors**: Ensure C17 support, check CMake version

### Debugging

Enable debug logging:

```c
sssp_set_log_level(SSSP_LOG_LEVEL_TRACE);
```

Use memory checkers:

```bash
valgrind --leak-check=full ./demo -g 100
```

## Benchmarking

The demo program includes built-in benchmarking:

```bash
./demo -g 10000 -s 0  # Automatically runs benchmarks for large graphs
```

For custom benchmarks, use the statistics API:

```c
const sssp_stats_t* stats = sssp_solver_get_stats(solver);
printf("Vertices processed: %u\n", stats->total_vertices_processed);
printf("Edges relaxed: %u\n", stats->total_edges_relaxed);
```
