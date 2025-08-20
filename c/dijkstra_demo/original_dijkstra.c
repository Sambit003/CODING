/**
 * @file original_dijkstra.c
 * @brief Production-quality implementation of Dijkstra's algorithm in C.
 *
 * This implementation uses an adjacency list to represent the graph and a
 * min-heap as a priority queue to efficiently find the shortest paths.
 *
 * - Modular design with distinct data structures for Graph and Min-Heap.
 * - Dynamic memory allocation with robust error checking.
 * - Comprehensive memory management to prevent leaks (e.g., freeGraph).
 * - Efficient implementation with O(E log V) time complexity.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h> // For INT_MAX

// --- Data Structures ---

// Represents a node in the adjacency list
typedef struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
} AdjListNode;

// Represents the adjacency list for a single vertex
typedef struct AdjList {
    AdjListNode* head;
} AdjList;

// Represents the graph
typedef struct Graph {
    int numVertices;
    AdjList* array; // An array of adjacency lists
} Graph;

// Represents a node in the min-heap (Priority Queue)
typedef struct MinHeapNode {
    int vertex;
    int dist;
} MinHeapNode;

// Represents a min-heap
typedef struct MinHeap {
    int size;       // Number of heap nodes currently present
    int capacity;   // Maximum possible number of heap nodes
    int* pos;       // Needed for the decreaseKey() operation
    MinHeapNode** array;
} MinHeap;

// --- Graph Utility Functions ---

/**
 * @brief Creates a new adjacency list node.
 * @param dest The destination vertex.
 * @param weight The weight of the edge.
 * @return A pointer to the newly created node, or NULL on failure.
 */
AdjListNode* createAdjListNode(int dest, int weight) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    if (!newNode) {
        perror("Failed to allocate memory for AdjListNode");
        return NULL;
    }
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

/**
 * @brief Creates a graph with a given number of vertices.
 * @param numVertices The number of vertices in the graph.
 * @return A pointer to the newly created graph, or NULL on failure.
 */
Graph* createGraph(int numVertices) {
    if (numVertices <= 0) {
        fprintf(stderr, "Error: Number of vertices must be positive.\n");
        return NULL;
    }
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) {
        perror("Failed to allocate memory for Graph");
        return NULL;
    }
    graph->numVertices = numVertices;

    // Allocate memory for an array of adjacency lists
    graph->array = (AdjList*)malloc(numVertices * sizeof(AdjList));
    if (!graph->array) {
        perror("Failed to allocate memory for adjacency list array");
        free(graph); // Clean up partially allocated graph
        return NULL;
    }

    // Initialize each adjacency list as empty
    for (int i = 0; i < numVertices; ++i) {
        graph->array[i].head = NULL;
    }

    return graph;
}

/**
 * @brief Adds a weighted, undirected edge to the graph.
 * @param graph The graph to add the edge to.
 * @param src The source vertex.
 * @param dest The destination vertex.
 * @param weight The weight of the edge.
 */
void addEdge(Graph* graph, int src, int dest, int weight) {
    if (!graph || src < 0 || src >= graph->numVertices || dest < 0 || dest >= graph->numVertices) {
        fprintf(stderr, "Error: Invalid graph or vertex in addEdge.\n");
        return;
    }
    // Add an edge from src to dest
    AdjListNode* newNode = createAdjListNode(dest, weight);
    if (!newNode) return; // Error handled in createAdjListNode
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Since the graph is undirected, add an edge from dest to src as well
    newNode = createAdjListNode(src, weight);
    if (!newNode) return;
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

/**
 * @brief Frees all memory associated with a graph.
 * @param graph The graph to be freed.
 */
void freeGraph(Graph* graph) {
    if (!graph) return;
    for (int i = 0; i < graph->numVertices; ++i) {
        AdjListNode* current = graph->array[i].head;
        while (current != NULL) {
            AdjListNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);
}


// --- Min-Heap (Priority Queue) Utility Functions ---

/**
 * @brief Creates a new min-heap node.
 */
MinHeapNode* createMinHeapNode(int vertex, int dist) {
    MinHeapNode* minHeapNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    if (!minHeapNode) {
        perror("Failed to allocate memory for MinHeapNode");
        return NULL;
    }
    minHeapNode->vertex = vertex;
    minHeapNode->dist = dist;
    return minHeapNode;
}

/**
 * @brief Creates a min-heap of a given capacity.
 */
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!minHeap) {
        perror("Failed to allocate memory for MinHeap");
        return NULL;
    }
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    if (!minHeap->pos || !minHeap->array) {
        perror("Failed to allocate memory for MinHeap internal arrays");
        free(minHeap->pos);
        free(minHeap->array);
        free(minHeap);
        return NULL;
    }
    minHeap->size = 0;
    minHeap->capacity = capacity;
    return minHeap;
}

/**
 * @brief Frees all memory associated with a min-heap.
 */
void freeMinHeap(MinHeap* minHeap) {
    if (!minHeap) return;
    // The nodes within the array are freed separately
    // as they are created one by one.
    for(int i = 0; i < minHeap->size; ++i) {
        free(minHeap->array[i]);
    }
    free(minHeap->pos);
    free(minHeap->array);
    free(minHeap);
}


/**
 * @brief Swaps two min-heap nodes.
 */
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

/**
 * @brief A standard min-heapify function.
 */
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx) {
        MinHeapNode* smallestNode = minHeap->array[smallest];
        MinHeapNode* idxNode = minHeap->array[idx];

        // Swap positions
        minHeap->pos[smallestNode->vertex] = idx;
        minHeap->pos[idxNode->vertex] = smallest;

        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

/**
 * @brief Checks if the min-heap is empty.
 */
bool isEmpty(const MinHeap* minHeap) {
    return minHeap->size == 0;
}

/**
 * @brief Extracts the node with the minimum distance value from the heap.
 */
MinHeapNode* extractMin(MinHeap* minHeap) {
    if (isEmpty(minHeap))
        return NULL;

    MinHeapNode* root = minHeap->array[0];

    // Replace root with the last node
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    // Update position of last node
    minHeap->pos[root->vertex] = minHeap->size - 1; // Mark root as extracted
    minHeap->pos[lastNode->vertex] = 0;

    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

/**
 * @brief Decreases the distance value of a given vertex `v`.
 * This function uses the `pos` array to get the current index of the node in the min-heap.
 */
void decreaseKey(MinHeap* minHeap, int vertex, int dist) {
    // Get the index of the vertex in the heap array
    int i = minHeap->pos[vertex];

    // Update the distance value of the node
    minHeap->array[i]->dist = dist;

    // Travel up while the complete tree is not heapified.
    // This is O(log V)
    while (i > 0 && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->vertex] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->vertex] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        // Move to the parent index
        i = (i - 1) / 2;
    }
}

/**
 * @brief Utility function to check if a vertex is in the min-heap.
 */
bool isInMinHeap(const MinHeap* minHeap, int vertex) {
    return minHeap->pos[vertex] < minHeap->size;
}

/**
 * @brief Prints the final shortest distances from the source.
 */
void printShortestPaths(const int dist[], int n) {
    printf("Vertex\t\tDistance from Source\n");
    printf("------\t\t--------------------\n");
    for (int i = 0; i < n; ++i) {
        if (dist[i] == INT_MAX) {
            printf("%d \t\t %s\n", i, "UNREACHABLE");
        } else {
            printf("%d \t\t %d\n", i, dist[i]);
        }
    }
}


// --- Dijkstra's Algorithm ---

/**
 * @brief The main function that implements Dijkstra's single-source shortest path algorithm.
 * @param graph The graph.
 * @param src The source vertex.
 */
void dijkstra(const Graph* graph, int src) {
    if (!graph) {
        fprintf(stderr, "Error: Graph is NULL.\n");
        return;
    }
    int V = graph->numVertices;
    if (src < 0 || src >= V) {
        fprintf(stderr, "Error: Source vertex %d is out of bounds.\n", src);
        return;
    }

    // Allocate memory for distance array
    int* dist = (int*)malloc(V * sizeof(int));
    if (!dist) {
        perror("Failed to allocate memory for distance array");
        return;
    }

    // Create and initialize the min-heap
    MinHeap* minHeap = createMinHeap(V);
    if (!minHeap) {
        free(dist);
        return;
    }

    for (int v = 0; v < V; ++v) {
        dist[v] = INT_MAX;
        minHeap->array[v] = createMinHeapNode(v, dist[v]);
        if (!minHeap->array[v]) { // Critical error check
            // Cleanup on failure
            for(int k=0; k<v; ++k) free(minHeap->array[k]);
            freeMinHeap(minHeap);
            free(dist);
            return;
        }
        minHeap->pos[v] = v;
    }
    minHeap->size = V;

    // Set distance of source vertex to 0 and update it in the min-heap
    dist[src] = 0;
    decreaseKey(minHeap, src, 0);

    // Main loop: process vertices until the min-heap is empty
    while (!isEmpty(minHeap)) {
        // Extract the vertex with the minimum distance value
        MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->vertex;
        free(minHeapNode); // Free the extracted node

        // Traverse all adjacent vertices of the extracted vertex 'u'
        AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;

            // Relaxation step: If a shorter path to v is found through u
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX &&
                pCrawl->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->weight;

                // Update distance value in min heap
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }

    // Print the calculated shortest distances
    printShortestPaths(dist, V);

    // Cleanup
    free(dist);
    freeMinHeap(minHeap);
}


// --- Main Driver Function ---

int main() {
    int V = 9;
    Graph* graph = createGraph(V);
    if (!graph) {
        return EXIT_FAILURE;
    }

    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 7, 8);
    addEdge(graph, 1, 2, 8);
    addEdge(graph, 1, 7, 11);
    addEdge(graph, 2, 3, 7);
    addEdge(graph, 2, 8, 2);
    addEdge(graph, 2, 5, 4);
    addEdge(graph, 3, 4, 9);
    addEdge(graph, 3, 5, 14);
    addEdge(graph, 4, 5, 10);
    addEdge(graph, 5, 6, 2);
    addEdge(graph, 6, 7, 1);
    addEdge(graph, 6, 8, 6);
    addEdge(graph, 7, 8, 7);

    printf("Running Dijkstra's Algorithm from source vertex 0:\n");
    dijkstra(graph, 0);

    // IMPORTANT: Free all allocated memory
    freeGraph(graph);

    return EXIT_SUCCESS;
}