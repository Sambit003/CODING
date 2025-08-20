#define _POSIX_C_SOURCE 200809L // Expose clock_gettime and CLOCK_MONOTONIC
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <string.h>

// --- Data Structures (Graph, MinHeap, etc.) ---
typedef struct AdjListNode { int dest, weight; struct AdjListNode* next; } AdjListNode;
typedef struct AdjList { AdjListNode* head; } AdjList;
typedef struct Graph { int numVertices; AdjList* array; } Graph;
typedef struct MinHeapNode { int vertex, dist; } MinHeapNode;
typedef struct MinHeap { int size, capacity, *pos; MinHeapNode** array; } MinHeap;

// --- Prototypes for graph/heap functions (implementation is below main) ---
Graph* createGraph(int numVertices);
void addEdge(Graph* graph, int src, int dest, int weight);
void freeGraph(Graph* graph);
void printShortestPaths(const int dist[], int n);

// --- ALGORITHM 1: MIN-HEAP IMPLEMENTATION O((m+n) log n) ---
void dijkstra_min_heap(const Graph* graph, int src, bool enable_print);

// --- ALGORITHM 2: NAIVE IMPLEMENTATION O(n^2) ---
int findMinDistance(const int dist[], const bool sptSet[], int V) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    return min_index;
}

void dijkstra_naive(const Graph* graph, int src, bool enable_print) {
    if (!graph) return;
    int V = graph->numVertices;
    int* dist = (int*)malloc(V * sizeof(int));
    bool* sptSet = (bool*)malloc(V * sizeof(bool));
    if (!dist || !sptSet) { free(dist); free(sptSet); return; }

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = findMinDistance(dist, sptSet, V);
        if (u == -1) break;
        sptSet[u] = true;
        AdjListNode* crawler = graph->array[u].head;
        while (crawler != NULL) {
            int v = crawler->dest;
            if (!sptSet[v] && dist[u] != INT_MAX && (dist[u] + crawler->weight < dist[v])) {
                dist[v] = dist[u] + crawler->weight;
            }
            crawler = crawler->next;
        }
    }
    if (enable_print) printShortestPaths(dist, V);
    free(dist);
    free(sptSet);
}


// --- BENCHMARKING UTILITIES ---
Graph* generateRandomGraph(int numVertices, int numEdges) {
    if (numEdges < numVertices - 1) {
        fprintf(stderr, "To be connected, a graph needs at least V-1 edges.\n");
        return NULL;
    }
    Graph* graph = createGraph(numVertices);
    if (!graph) return NULL;

    // Seed the random number generator
    srand(time(NULL));

    // Ensure the graph is connected by creating a path
    for (int i = 0; i < numVertices - 1; ++i) {
        int weight = 1 + rand() % 100;
        addEdge(graph, i, i + 1, weight);
    }
    
    long currentEdges = numVertices - 1;

    // Add remaining random edges
    while(currentEdges < numEdges) {
        int u = rand() % numVertices;
        int v = rand() % numVertices;
        int weight = 1 + rand() % 100;

        if (u != v) {
            addEdge(graph, u, v, weight);
            currentEdges++;
        }
    }
    return graph;
}

// --- MAIN BENCHMARKING DRIVER ---
int main() {
    const int sparse_configs[][2] = {
        {500, 1000}, {1000, 2500}, {2000, 5000}, {4000, 10000}
    };
    const int dense_configs[][2] = {
        {100, 4000}, {200, 15000}, {400, 60000}, {500, 100000}
    };
    int num_sparse = sizeof(sparse_configs) / sizeof(sparse_configs[0]);
    int num_dense = sizeof(dense_configs) / sizeof(dense_configs[0]);

    printf("--- Benchmarking Dijkstra's Algorithms ---\n");
    printf("All times are in milliseconds (ms)\n\n");

    struct timespec start, end;

    printf("--- Testing on SPARSE graphs (m ~ n) ---\n");
    printf("--------------------------------------------------------------------------\n");
    printf("| Vertices (n) | Edges (m)    | O(m log n) Min-Heap | O(n^2) Naive      |\n");
    printf("--------------------------------------------------------------------------\n");
    for (int i = 0; i < num_sparse; ++i) {
        int V = sparse_configs[i][0];
        int E = sparse_configs[i][1];
        Graph* g = generateRandomGraph(V, E);
        if (!g) continue;

        printf("| %-12d | %-12d |", V, E);
        
        clock_gettime(CLOCK_MONOTONIC, &start);
        dijkstra_min_heap(g, 0, false);
        clock_gettime(CLOCK_MONOTONIC, &end);
        double heap_time = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
        printf(" %-19.3f |", heap_time);

        clock_gettime(CLOCK_MONOTONIC, &start);
        dijkstra_naive(g, 0, false);
        clock_gettime(CLOCK_MONOTONIC, &end);
        double naive_time = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
        printf(" %-17.3f |\n", naive_time);

        freeGraph(g);
    }
    printf("--------------------------------------------------------------------------\n\n");

    printf("--- Testing on DENSE graphs (m approaching n^2) ---\n");
    printf("--------------------------------------------------------------------------\n");
    printf("| Vertices (n) | Edges (m)    | O(m log n) Min-Heap | O(n^2) Naive      |\n");
    printf("--------------------------------------------------------------------------\n");
    for (int i = 0; i < num_dense; ++i) {
        int V = dense_configs[i][0];
        int E = dense_configs[i][1];
        Graph* g = generateRandomGraph(V, E);
        if (!g) continue;

        printf("| %-12d | %-12d |", V, E);

        clock_gettime(CLOCK_MONOTONIC, &start);
        dijkstra_min_heap(g, 0, false);
        clock_gettime(CLOCK_MONOTONIC, &end);
        double heap_time = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
        printf(" %-19.3f |", heap_time);

        clock_gettime(CLOCK_MONOTONIC, &start);
        dijkstra_naive(g, 0, false);
        clock_gettime(CLOCK_MONOTONIC, &end);
        double naive_time = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
        printf(" %-17.3f |\n", naive_time);

        freeGraph(g);
    }
    printf("--------------------------------------------------------------------------\n");


    return 0;
}

// --- IMPLEMENTATION OF UTILITIES AND ALGORITHMS ---
AdjListNode* createAdjListNode(int dest, int weight) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest; newNode->weight = weight; newNode->next = NULL;
    return newNode;
}
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->array = (AdjList*)calloc(numVertices, sizeof(AdjList));
    return graph;
}
void addEdge(Graph* graph, int src, int dest, int weight) {
    AdjListNode* newNode = createAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    newNode = createAdjListNode(src, weight);
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
    free(graph->array); free(graph);
}
void printShortestPaths(const int dist[], int n) {
    printf("Vertex\t\tDistance from Source\n");
    for (int i = 0; i < n; ++i) printf("%d \t\t %d\n", i, dist[i]);
}

MinHeapNode* createMinHeapNode(int vertex, int dist) {
    MinHeapNode* n = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    n->vertex = vertex; n->dist = dist;
    return n;
}
MinHeap* createMinHeap(int capacity) {
    MinHeap* h = (MinHeap*)malloc(sizeof(MinHeap));
    h->pos = (int*)malloc(capacity * sizeof(int));
    h->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    h->size = 0; h->capacity = capacity;
    return h;
}
void freeMinHeap(MinHeap* minHeap) {
    if (!minHeap) return;
    free(minHeap->pos); free(minHeap->array); free(minHeap);
}
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) { MinHeapNode* t = *a; *a = *b; *b = t; }
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx, left = 2 * idx + 1, right = 2 * idx + 2;
    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist) smallest = left;
    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist) smallest = right;
    if (smallest != idx) {
        MinHeapNode* smallestNode = minHeap->array[smallest]; MinHeapNode* idxNode = minHeap->array[idx];
        minHeap->pos[smallestNode->vertex] = idx; minHeap->pos[idxNode->vertex] = smallest;
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}
bool isEmpty(const MinHeap* minHeap) { return minHeap->size == 0; }
MinHeapNode* extractMin(MinHeap* minHeap) {
    if (isEmpty(minHeap)) return NULL;
    MinHeapNode* root = minHeap->array[0];
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
    minHeap->pos[root->vertex] = minHeap->size - 1; minHeap->pos[lastNode->vertex] = 0;
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
bool isInMinHeap(const MinHeap* minHeap, int vertex) { return minHeap->pos[vertex] < minHeap->size; }

void dijkstra_min_heap(const Graph* graph, int src, bool enable_print) {
    if (!graph) return;
    int V = graph->numVertices;
    int* dist = (int*)malloc(V * sizeof(int));
    MinHeap* minHeap = createMinHeap(V);
    if (!dist || !minHeap) { free(dist); freeMinHeap(minHeap); return; }

    for (int v = 0; v < V; ++v) {
        dist[v] = INT_MAX;
        minHeap->array[v] = createMinHeapNode(v, INT_MAX);
        minHeap->pos[v] = v;
    }
    minHeap->size = V;
    dist[src] = 0;
    decreaseKey(minHeap, src, 0);

    while (!isEmpty(minHeap)) {
        MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->vertex;
        free(minHeapNode);
        AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->weight + dist[u] < dist[v]) {
                dist[v] = dist[u] + pCrawl->weight;
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
    if (enable_print) printShortestPaths(dist, V);
    for(int i = 0; i < minHeap->size; ++i) free(minHeap->array[i]);
    free(dist);
    freeMinHeap(minHeap);
}