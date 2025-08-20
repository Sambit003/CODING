/**
 * @file sssp_dijkstra.c
 * @brief SSSP implementation for sparse graphs using Dijkstra's algorithm.
 *
 * This implementation is optimized for sparse graphs by using an Adjacency List
 * representation, which has a space complexity of O(n + m).
 *
 * The algorithm uses a Binary Min-Heap as a priority queue to achieve a
 * time complexity of O(m + n log n), which is the practical standard for
 * high-performance implementations.
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

// The Graph structure (Adjacency List representation)
typedef struct Graph {
    int numVertices;
    AdjList* array;
} Graph;

// Represents a node in the min-heap
typedef struct MinHeapNode {
    int vertex;
    int dist;
} MinHeapNode;

// Represents a min-heap (Priority Queue)
typedef struct MinHeap {
    int size;
    int capacity;
    int* pos;       // Maps vertex number to heap array index
    MinHeapNode** array;
} MinHeap;

// --- Graph Utility Functions (Optimized for Sparse Graphs) ---

AdjListNode* createAdjListNode(int dest, int weight) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    if (!newNode) return NULL;
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int numVertices) {
    if (numVertices <= 0) return NULL;
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) return NULL;
    graph->numVertices = numVertices;
    graph->array = (AdjList*)calloc(numVertices, sizeof(AdjList)); // calloc initializes heads to NULL
    if (!graph->array) {
        free(graph);
        return NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    if (!graph || src < 0 || src >= graph->numVertices || dest < 0 || dest >= graph->numVertices) return;
    AdjListNode* newNode = createAdjListNode(dest, weight);
    if (!newNode) return;
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // For undirected graph, add edge from dest to src as well
    newNode = createAdjListNode(src, weight);
    if (!newNode) return;
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

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

// --- Min-Heap (Priority Queue) Functions ---

MinHeapNode* createMinHeapNode(int vertex, int dist) {
    MinHeapNode* minHeapNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    if (!minHeapNode) return NULL;
    minHeapNode->vertex = vertex;
    minHeapNode->dist = dist;
    return minHeapNode;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!minHeap) return NULL;
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    if (!minHeap->pos || !minHeap->array) {
        free(minHeap->pos); free(minHeap->array); free(minHeap);
        return NULL;
    }
    minHeap->size = 0;
    minHeap->capacity = capacity;
    return minHeap;
}

void freeMinHeap(MinHeap* minHeap) {
    if (!minHeap) return;
    // Note: The nodes inside minHeap->array are freed within the dijkstra function
    // as they are extracted one by one. Or at the end if there is an error.
    free(minHeap->pos);
    free(minHeap->array);
    free(minHeap);
}

void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;
    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx) {
        minHeap->pos[minHeap->array[smallest]->vertex] = idx;
        minHeap->pos[minHeap->array[idx]->vertex] = smallest;
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

bool isEmpty(const MinHeap* minHeap) {
    return minHeap->size == 0;
}

MinHeapNode* extractMin(MinHeap* minHeap) {
    if (isEmpty(minHeap)) return NULL;
    MinHeapNode* root = minHeap->array[0];
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
    minHeap->pos[root->vertex] = minHeap->size - 1;
    minHeap->pos[lastNode->vertex] = 0;
    --minHeap->size;
    minHeapify(minHeap, 0);
    return root;
}

void decreaseKey(MinHeap* minHeap, int vertex, int dist) {
    int i = minHeap->pos[vertex];
    minHeap->array[i]->dist = dist;
    while (i > 0 && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        minHeap->pos[minHeap->array[i]->vertex] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->vertex] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

bool isInMinHeap(const MinHeap* minHeap, int vertex) {
    return minHeap->pos[vertex] < minHeap->size;
}

void printShortestPaths(const int dist[], int n) {
    printf("Vertex\t\tDistance from Source\n");
    printf("------\t\t--------------------\n");
    for (int i = 0; i < n; ++i) {
        if (dist[i] == INT_MAX) printf("%d \t\t UNREACHABLE\n", i);
        else printf("%d \t\t %d\n", i, dist[i]);
    }
}


// --- Dijkstra's Algorithm ---

/**
 * @brief SSSP algorithm for a weighted graph.
 * @param graph The graph, represented by an adjacency list.
 * @param src The source vertex.
 *
 * @brief Time Complexity: O(m log n) using a binary min-heap.
 * With a Fibonacci heap, this could be O(m + n log n).
 * @brief Space Complexity: O(n + m) for the graph + O(n) for auxiliary data.
 */
void dijkstra(const Graph* graph, int src) {
    if (!graph || src < 0 || src >= graph->numVertices) return;

    int V = graph->numVertices;
    int* dist = (int*)malloc(V * sizeof(int));
    MinHeap* minHeap = createMinHeap(V);

    if (!dist || !minHeap) { // Error handling
        perror("Memory allocation failed");
        free(dist);
        freeMinHeap(minHeap);
        return;
    }

    // Initialization
    for (int v = 0; v < V; ++v) {
        dist[v] = INT_MAX;
        minHeap->array[v] = createMinHeapNode(v, INT_MAX);
        minHeap->pos[v] = v;
    }
    minHeap->size = V;

    // Set source distance and update in heap
    dist[src] = 0;
    decreaseKey(minHeap, src, 0);

    // Main loop
    while (!isEmpty(minHeap)) {
        MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->vertex;
        free(minHeapNode); // Free the extracted node

        // Iterate over all neighbors of u
        AdjListNode* crawler = graph->array[u].head;
        while (crawler != NULL) {
            int v = crawler->dest;
            // Relaxation step
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && (dist[u] + crawler->weight < dist[v])) {
                dist[v] = dist[u] + crawler->weight;
                decreaseKey(minHeap, v, dist[v]);
            }
            crawler = crawler->next;
        }
    }

    printShortestPaths(dist, V);

    // Cleanup
    free(dist);
    freeMinHeap(minHeap);
}

// --- Main Driver Function ---
int main() {
    int V = 9;
    Graph* graph = createGraph(V);
    if (!graph) return EXIT_FAILURE;

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

    printf("Running SSSP (Dijkstra) from source vertex 0...\n");
    dijkstra(graph, 0);

    freeGraph(graph);
    return EXIT_SUCCESS;
}