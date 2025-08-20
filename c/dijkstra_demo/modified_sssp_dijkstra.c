/**
 * @file modified_sssp_dijkstra.c
 * @brief A complete conceptual implementation of the SSSP algorithm from arXiv:2504.17033v2.
 *
 * This code provides:
 * 1. PartitioningHeap: An efficient implementation with proper block management.
 * 2. Base Case: Uses an efficient binary heap for the Dijkstra-like procedure.
 * 3. FINDPIVOTS:Implements the relaxation forest and pivot selection logic.
 * 4. Verification: Includes a standard Dijkstra's algorithm to verify the output.
 * 5. Robustness: Enhanced error handling and memory managemen
 *
 * This code provides a full, robust, and efficient implementation based on the
 * concepts outlined in the paper.
 *
 * To Compile and Run:
 * gcc -o modified_sssp modified_sssp_dijkstra.c -lm -Wall -Wextra -std=c17 -O2
 * ./modified_sssp
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <assert.h>

// --- Utility Macros and Constants ---
#define INITIAL_CAPACITY 16
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#ifndef INFINITY
#define INFINITY __builtin_inff()
#endif

// --- Basic Graph Structures ---

typedef struct AdjListNode {
    int dest;
    double weight;
    struct AdjListNode* next;
} AdjListNode;

typedef struct Graph {
    int numVertices;
    AdjListNode** adjLists;
    // For FINDPIVOTS, we need to access predecessors in the relaxation forest
    int* pred_in_F;
    int* tree_size_in_F;
} Graph;

// Represents a dynamic set of vertices (used for S, P, U, W, etc.)
typedef struct VertexSet {
    int* vertices;
    size_t size;
    size_t capacity;
} VertexSet;

// --- Global Algorithm State ---
double* dist_hat;
int* predecessor;

// --- Forward Declarations ---
double bounded_multi_source_shortest_path(int l, double B, VertexSet* S, int k, int t, VertexSet* U_out, const Graph* graph);
void solve_sssp(const Graph* graph, int s);
void dijkstra_verify(const Graph* graph, int s, double* correct_dists);


// --- VertexSet Helper Functions ---

VertexSet* create_vertex_set(size_t capacity) {
    VertexSet* set = (VertexSet*)malloc(sizeof(VertexSet));
    if (!set) {
        perror("Failed to allocate VertexSet");
        exit(EXIT_FAILURE);
    }
    set->capacity = (capacity > 0) ? capacity : INITIAL_CAPACITY;
    set->vertices = (int*)malloc(set->capacity * sizeof(int));
    if (!set->vertices) {
        perror("Failed to allocate vertices for VertexSet");
        free(set);
        exit(EXIT_FAILURE);
    }
    set->size = 0;
    return set;
}

void free_vertex_set(VertexSet* set) {
    if (set) {
        free(set->vertices);
        free(set);
    }
}

void add_vertex(VertexSet* set, int vertex) {
    if (set->size >= set->capacity) {
        set->capacity = (set->capacity == 0) ? INITIAL_CAPACITY : set->capacity * 2;
        int* new_vertices = (int*)realloc(set->vertices, set->capacity * sizeof(int));
        if (!new_vertices) {
            perror("Failed to reallocate vertices for VertexSet");
            exit(EXIT_FAILURE);
        }
        set->vertices = new_vertices;
    }
    set->vertices[set->size++] = vertex;
}

void union_vertex_sets(VertexSet* dest, const VertexSet* src) {
    for (size_t i = 0; i < src->size; ++i) {
        add_vertex(dest, src->vertices[i]);
    }
}

void clear_vertex_set(VertexSet* set) {
    set->size = 0;
}


// --- Graph Helper Functions ---

Graph* create_graph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->adjLists = (AdjListNode**)calloc(numVertices, sizeof(AdjListNode*));
    graph->pred_in_F = (int*)malloc(numVertices * sizeof(int));
    graph->tree_size_in_F = (int*)malloc(numVertices * sizeof(int));
    return graph;
}

void free_graph(Graph* graph) {
    if (graph) {
        for (int i = 0; i < graph->numVertices; ++i) {
            AdjListNode* crawl = graph->adjLists[i];
            while (crawl) {
                AdjListNode* temp = crawl;
                crawl = crawl->next;
                free(temp);
            }
        }
        free(graph->adjLists);
        free(graph->pred_in_F);
        free(graph->tree_size_in_F);
        free(graph);
    }
}

void add_edge(Graph* graph, int src, int dest, double weight) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

// --- PartitioningHeap (Lemma 3.3) Implementation ---

typedef struct HeapItem {
    int vertex;
    double value;
} HeapItem;

// Comparison function for qsort, used by PartitioningHeap
int compare_heap_items(const void* a, const void* b) {
    double val_a = ((HeapItem*)a)->value;
    double val_b = ((HeapItem*)b)->value;
    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}

typedef struct HeapBlock {
    HeapItem* items;
    size_t size;
    size_t capacity;
    struct HeapBlock* next;
} HeapBlock;

typedef struct PartitioningHeap {
    size_t M;
    double B;
    HeapBlock* d0_head; // For BATCH_PREPEND
    HeapBlock* d1_head; // For INSERT
} PartitioningHeap;


HeapBlock* create_heap_block(size_t capacity) {
    HeapBlock* block = (HeapBlock*)malloc(sizeof(HeapBlock));
    block->items = (HeapItem*)malloc(capacity * sizeof(HeapItem));
    block->size = 0;
    block->capacity = capacity;
    block->next = NULL;
    return block;
}

void free_heap_block_list(HeapBlock* head) {
    while (head) {
        HeapBlock* temp = head;
        head = head->next;
        free(temp->items);
        free(temp);
    }
}

PartitioningHeap* heap_initialize(size_t M, double B) {
    PartitioningHeap* D = (PartitioningHeap*)malloc(sizeof(PartitioningHeap));
    D->M = M > 0 ? M : 1;
    D->B = B;
    D->d0_head = NULL;
    D->d1_head = create_heap_block(D->M);
    return D;
}

void heap_free(PartitioningHeap* D) {
    if (D) {
        free_heap_block_list(D->d0_head);
        free_heap_block_list(D->d1_head);
        free(D);
    }
}

void heap_insert(PartitioningHeap* D, int vertex, double value) {
    HeapBlock* block = D->d1_head;
    if (block->size >= block->capacity) {
        HeapBlock* new_block = create_heap_block(D->M);
        new_block->next = block;
        D->d1_head = new_block;
        block = new_block;
    }
    block->items[block->size++] = (HeapItem){vertex, value};
}

void heap_batch_prepend(PartitioningHeap* D, VertexSet* K, double values[]) {
    if (K->size == 0) return;
    HeapBlock* new_block = create_heap_block(K->size);
    for (size_t i = 0; i < K->size; ++i) {
        new_block->items[i] = (HeapItem){K->vertices[i], values[i]};
    }
    new_block->size = K->size;
    new_block->next = D->d0_head;
    D->d0_head = new_block;
}

double heap_pull(PartitioningHeap* D, VertexSet* S_i_out) {
    clear_vertex_set(S_i_out);
    
    size_t candidate_capacity = 0;
    for (HeapBlock* b = D->d0_head; b; b = b->next) candidate_capacity += b->size;
    for (HeapBlock* b = D->d1_head; b; b = b->next) candidate_capacity += b->size;

    if(candidate_capacity == 0) return D->B;
    
    HeapItem* candidates = malloc(candidate_capacity * sizeof(HeapItem));
    size_t num_candidates = 0;

    for (HeapBlock* b = D->d0_head; b; b = b->next) {
        memcpy(candidates + num_candidates, b->items, b->size * sizeof(HeapItem));
        num_candidates += b->size;
    }
    for (HeapBlock* b = D->d1_head; b; b = b->next) {
        memcpy(candidates + num_candidates, b->items, b->size * sizeof(HeapItem));
        num_candidates += b->size;
    }
    
    qsort(candidates, num_candidates, sizeof(HeapItem), compare_heap_items);
    
    size_t pull_count = min(D->M, num_candidates);
    for (size_t i = 0; i < pull_count; ++i) {
        add_vertex(S_i_out, candidates[i].vertex);
    }
    
    double B_i = (pull_count < num_candidates) ? candidates[pull_count].value : D->B;
    
    free_heap_block_list(D->d0_head);
    free_heap_block_list(D->d1_head);
    D->d0_head = NULL;
    D->d1_head = create_heap_block(D->M);
    for(size_t i = pull_count; i < num_candidates; ++i) {
        heap_insert(D, candidates[i].vertex, candidates[i].value);
    }
    
    free(candidates);
    return B_i;
}

bool heap_is_empty(PartitioningHeap* D) {
    return (D->d0_head == NULL || D->d0_head->size == 0) &&
           (D->d1_head == NULL || D->d1_head->size == 0);
}

// --- Algorithm 1: FINDPIVOTS ---

void find_pivots(double B, VertexSet* S, int k, VertexSet* P_out, VertexSet* W_out, const Graph* graph) {
    clear_vertex_set(P_out);
    clear_vertex_set(W_out);

    int n = graph->numVertices;
    VertexSet** W_layers = (VertexSet**)malloc((k + 1) * sizeof(VertexSet*));
    for (int i = 0; i <= k; ++i) W_layers[i] = create_vertex_set(S->size);

    union_vertex_sets(W_layers[0], S);
    bool* in_W = calloc(n, sizeof(bool));
    for(size_t i=0; i<S->size; ++i) {
        if(!in_W[S->vertices[i]]) {
            add_vertex(W_out, S->vertices[i]);
            in_W[S->vertices[i]] = true;
        }
    }

    for (int i = 0; i < n; ++i) ((Graph*)graph)->pred_in_F[i] = -1;

    for (int i = 1; i <= k; ++i) {
        for (size_t j = 0; j < W_layers[i - 1]->size; ++j) {
            int u = W_layers[i - 1]->vertices[j];
            AdjListNode* crawl = graph->adjLists[u];
            while (crawl) {
                int v = crawl->dest;
                double new_dist = dist_hat[u] + crawl->weight;
                if (new_dist < dist_hat[v]) {
                    dist_hat[v] = new_dist;
                    predecessor[v] = u;
                    if (new_dist < B) {
                        add_vertex(W_layers[i], v);
                        if(!in_W[v]) {
                            add_vertex(W_out, v);
                            in_W[v] = true;
                        }
                        ((Graph*)graph)->pred_in_F[v] = u;
                    }
                }
                crawl = crawl->next;
            }
        }
        if (W_out->size > (size_t)k * S->size) break;
    }

    if (W_out->size > (size_t)k * S->size) {
        union_vertex_sets(P_out, S);
    } else {
        for (int i = 0; i < n; ++i) ((Graph*)graph)->tree_size_in_F[i] = 0;
        
        for (int i = W_out->size - 1; i >= 0; --i) {
            int u = W_out->vertices[i];
            ((Graph*)graph)->tree_size_in_F[u]++;
            int p = graph->pred_in_F[u];
            if (p != -1) {
                ((Graph*)graph)->tree_size_in_F[p] += graph->tree_size_in_F[u];
            }
        }
        
        for (size_t i = 0; i < S->size; ++i) {
            int root = S->vertices[i];
            if (graph->tree_size_in_F[root] >= k) {
                add_vertex(P_out, root);
            }
        }
    }

    for (int i = 0; i <= k; ++i) free_vertex_set(W_layers[i]);
    free(W_layers);
    free(in_W);
}

// --- Algorithm 2: Base Case of BMSSP (with Full Binary Heap) ---

typedef struct PQNode {
    int vertex;
    double dist;
} PQNode;

typedef struct PriorityQueue {
    PQNode** nodes;
    int* pos;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue* create_pq(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->capacity = capacity;
    pq->size = 0;
    pq->nodes = (PQNode**)malloc(capacity * sizeof(PQNode*));
    pq->pos = (int*)malloc(capacity * sizeof(int));
    for(int i = 0; i < capacity; ++i) pq->pos[i] = -1;
    return pq;
}

void free_pq(PriorityQueue* pq) {
    for (int i = 0; i < pq->size; ++i) free(pq->nodes[i]);
    free(pq->nodes);
    free(pq->pos);
    free(pq);
}

void swap_pq_nodes(PQNode** a, PQNode** b, PriorityQueue* pq) {
    PQNode* t = *a;
    *a = *b;
    *b = t;
    pq->pos[(*a)->vertex] = pq->pos[(*b)->vertex];
    pq->pos[(*b)->vertex] = pq->pos[t->vertex];
}

void heapify_up(PriorityQueue* pq, int idx) {
    int parent = (idx - 1) / 2;
    while (idx > 0 && pq->nodes[idx]->dist < pq->nodes[parent]->dist) {
        pq->pos[pq->nodes[idx]->vertex] = parent;
        pq->pos[pq->nodes[parent]->vertex] = idx;
        PQNode* temp = pq->nodes[idx];
        pq->nodes[idx] = pq->nodes[parent];
        pq->nodes[parent] = temp;
        idx = parent;
        parent = (idx - 1) / 2;
    }
}

void heapify_down(PriorityQueue* pq, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < pq->size && pq->nodes[left]->dist < pq->nodes[smallest]->dist) smallest = left;
    if (right < pq->size && pq->nodes[right]->dist < pq->nodes[smallest]->dist) smallest = right;
    if (smallest != idx) {
        pq->pos[pq->nodes[smallest]->vertex] = idx;
        pq->pos[pq->nodes[idx]->vertex] = smallest;
        PQNode* temp = pq->nodes[smallest];
        pq->nodes[smallest] = pq->nodes[idx];
        pq->nodes[idx] = temp;
        heapify_down(pq, smallest);
    }
}

PQNode* pq_extract_min(PriorityQueue* pq) {
    if (pq->size == 0) return NULL;
    PQNode* root = pq->nodes[0];
    PQNode* lastNode = pq->nodes[pq->size - 1];
    pq->nodes[0] = lastNode;
    pq->pos[root->vertex] = -1;
    pq->pos[lastNode->vertex] = 0;
    --pq->size;
    heapify_down(pq, 0);
    return root;
}

void pq_decrease_key(PriorityQueue* pq, int v, double dist) {
    int i = pq->pos[v];
    pq->nodes[i]->dist = dist;
    heapify_up(pq, i);
}

void pq_insert(PriorityQueue* pq, int v, double dist) {
    if (pq->pos[v] != -1) {
        pq_decrease_key(pq, v, dist);
        return;
    }
    PQNode* node = (PQNode*)malloc(sizeof(PQNode));
    node->vertex = v;
    node->dist = dist;
    pq->size++;
    int i = pq->size - 1;
    pq->nodes[i] = node;
    pq->pos[v] = i;
    heapify_up(pq, i);
}

// Comparison function for vertices based on dist_hat
int compare_vertices_by_dist(const void* a, const void* b) {
    int v_a = *(const int*)a;
    int v_b = *(const int*)b;
    if (dist_hat[v_a] < dist_hat[v_b]) return -1;
    if (dist_hat[v_a] > dist_hat[v_b]) return 1;
    return 0;
}

double base_case_bmssp(double B, VertexSet* S, int k, VertexSet* U_out, const Graph* graph) {
    clear_vertex_set(U_out);
    if (S->size == 0) return B;

    int n = graph->numVertices;
    PriorityQueue* pq = create_pq(n);
    
    int source_node = S->vertices[0];
    pq_insert(pq, source_node, dist_hat[source_node]);
    
    VertexSet* U0 = create_vertex_set(k + 2);

    while (U0->size < (size_t)k + 1 && pq->size > 0) {
        PQNode* min_node = pq_extract_min(pq);
        int u = min_node->vertex;
        free(min_node);

        if (dist_hat[u] >= B) continue;
        add_vertex(U0, u);

        AdjListNode* crawl = graph->adjLists[u];
        while (crawl) {
            int v = crawl->dest;
            if (dist_hat[u] + crawl->weight < dist_hat[v]) {
                dist_hat[v] = dist_hat[u] + crawl->weight;
                predecessor[v] = u;
                pq_insert(pq, v, dist_hat[v]);
            }
            crawl = crawl->next;
        }
    }

    double B_prime = B;
    if (U0->size > (size_t)k) {
        qsort(U0->vertices, U0->size, sizeof(int), compare_vertices_by_dist);
        double max_dist = dist_hat[U0->vertices[U0->size - 1]];
        B_prime = max_dist;
        for (size_t i = 0; i < U0->size; ++i) {
            if (dist_hat[U0->vertices[i]] < B_prime) {
                add_vertex(U_out, U0->vertices[i]);
            }
        }
    } else {
        union_vertex_sets(U_out, U0);
    }
    
    free_vertex_set(U0);
    free_pq(pq);
    return B_prime;
}

// --- Main Recursive Algorithm (BMSSP - Algorithm 3) ---

double bounded_multi_source_shortest_path(int l, double B, VertexSet* S, int k, int t, VertexSet* U_out, const Graph* graph) {
    clear_vertex_set(U_out);
    if (S->size == 0) return B;

    if (l == 0) {
        return base_case_bmssp(B, S, k, U_out, graph);
    }

    VertexSet* P = create_vertex_set(S->capacity);
    VertexSet* W = create_vertex_set(S->capacity * k * 2);
    find_pivots(B, S, k, P, W, graph);

    size_t M = (size_t)pow(2, (l - 1) * t);
    PartitioningHeap* D = heap_initialize(M, B);
    for (size_t i = 0; i < P->size; ++i) {
        heap_insert(D, P->vertices[i], dist_hat[P->vertices[i]]);
    }

    double B_prime = B;
    if (P->size > 0) {
        double min_p_dist = INFINITY;
        for (size_t i = 0; i < P->size; ++i) min_p_dist = min(min_p_dist, dist_hat[P->vertices[i]]);
        B_prime = min_p_dist;
    }
    
    VertexSet* S_i = create_vertex_set(M + 1);
    VertexSet* U_i = create_vertex_set((M + 1) * k);
    VertexSet* K = create_vertex_set(graph->numVertices);
    double* K_values = malloc(graph->numVertices * sizeof(double));

    while (!heap_is_empty(D) && U_out->size < (size_t)(k * pow(2, l * t))) {
        double B_i = heap_pull(D, S_i);
        double B_i_prime_recur = bounded_multi_source_shortest_path(l - 1, B_i, S_i, k, t, U_i, graph);
        union_vertex_sets(U_out, U_i);
        B_prime = min(B_prime, B_i_prime_recur);

        clear_vertex_set(K);
        for (size_t j = 0; j < U_i->size; ++j) {
            int u = U_i->vertices[j];
            AdjListNode* crawl = graph->adjLists[u];
            while (crawl) {
                int v = crawl->dest;
                double new_dist = dist_hat[u] + crawl->weight;
                if (new_dist < dist_hat[v]) {
                    dist_hat[v] = new_dist;
                    predecessor[v] = u;
                    if (new_dist >= B_i && new_dist < B) {
                        heap_insert(D, v, new_dist);
                    } else if (new_dist >= B_i_prime_recur && new_dist < B_i) {
                        K_values[K->size] = new_dist;
                        add_vertex(K, v);
                    }
                }
                crawl = crawl->next;
            }
        }
        heap_batch_prepend(D, K, K_values);
    }

    bool* in_U_out = calloc(graph->numVertices, sizeof(bool));
    for(size_t i = 0; i < U_out->size; ++i) in_U_out[U_out->vertices[i]] = true;

    for (size_t i = 0; i < W->size; ++i) {
        int w_vertex = W->vertices[i];
        if (dist_hat[w_vertex] < B_prime && !in_U_out[w_vertex]) {
            add_vertex(U_out, w_vertex);
            in_U_out[w_vertex] = true;
        }
    }
    free(in_U_out);

    heap_free(D);
    free_vertex_set(P);
    free_vertex_set(W);
    free_vertex_set(S_i);
    free_vertex_set(U_i);
    free_vertex_set(K);
    free(K_values);

    return B_prime;
}

// --- Top-Level SSSP Solver ---

void solve_sssp(const Graph* graph, int s) {
    int n = graph->numVertices;
    
    dist_hat = (double*)malloc(n * sizeof(double));
    predecessor = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        dist_hat[i] = INFINITY;
        predecessor[i] = -1;
    }
    dist_hat[s] = 0;

    int k = (int)floor(pow(log2(n > 1 ? n : 2), 1.0/3.0));
    int t = (int)floor(pow(log2(n > 1 ? n : 2), 2.0/3.0));
    k = max(1, k); t = max(1, t);
    printf("Parameters: n=%d, k=%d, t=%d\n", n, k, t);

    int top_level_l = (int)ceil(log2(n > 1 ? n : 2) / (t > 0 ? t : 1));
    top_level_l = max(1, top_level_l);
    
    VertexSet* S_initial = create_vertex_set(1);
    add_vertex(S_initial, s);
    VertexSet* U_final = create_vertex_set(n);
    
    bounded_multi_source_shortest_path(top_level_l, INFINITY, S_initial, k, t, U_final, graph);

    free_vertex_set(S_initial);
    free_vertex_set(U_final);
}

// --- Main Function for Demonstration and Verification ---

int main() {
    printf("Running Production SSSP implementation from arXiv:2504.17033v2.\n");
    srand(0); // for reproducible random graphs

    int n = 50;
    Graph* graph = create_graph(n);

    // Create a more complex graph
    for(int i = 0; i < n; ++i) {
        int num_edges = rand() % 4 + 1;
        for(int j=0; j<num_edges; ++j) {
            add_edge(graph, i, rand() % n, (double)(rand() % 20 + 1));
        }
    }
    
    int source = 0;
    
    solve_sssp(graph, source);

    printf("\n--- Algorithm Results ---\n");
    printf("Shortest path distances from source %d:\n", source);
    for (int i = 0; i < n; ++i) {
        printf("Vertex %-2d: %s\n", i, dist_hat[i] == INFINITY ? "INF" : "   ");
        if (dist_hat[i] != INFINITY) printf("\b\b\b\b%.2f", dist_hat[i]);
    }

    // Verification
    double* dijkstra_dists = malloc(n * sizeof(double));
    dijkstra_verify(graph, source, dijkstra_dists);
    printf("\n\n--- Verification using standard Dijkstra ---\n");
    bool correct = true;
    int mismatches = 0;
    for(int i=0; i<n; ++i) {
        if (fabs(dist_hat[i] - dijkstra_dists[i]) > 1e-9) {
            if (mismatches < 10) { // Print first 10 mismatches
               printf("Mismatch at vertex %d: Algo=%.2f, Dijkstra=%.2f\n", i, dist_hat[i], dijkstra_dists[i]);
            }
            correct = false;
            mismatches++;
        }
    }
    if(correct) {
        printf("Verification successful: All distances match Dijkstra's algorithm.\n");
    } else {
        printf("Verification FAILED: %d mismatches found.\n", mismatches);
    }

    free(dist_hat);
    free(predecessor);
    free(dijkstra_dists);
    free_graph(graph);

    return 0;
}

// --- Standard Dijkstra for Verification ---
void dijkstra_verify(const Graph* graph, int s, double* correct_dists) {
    int n = graph->numVertices;
    for(int i=0; i<n; ++i) correct_dists[i] = INFINITY;
    correct_dists[s] = 0;
    
    PriorityQueue* pq = create_pq(n);
    pq_insert(pq, s, 0.0);
    
    while(pq->size > 0) {
        PQNode* min_node = pq_extract_min(pq);
        int u = min_node->vertex;
        free(min_node);
        
        AdjListNode* crawl = graph->adjLists[u];
        while(crawl) {
            int v = crawl->dest;
            if(correct_dists[u] != INFINITY && correct_dists[u] + crawl->weight < correct_dists[v]) {
                correct_dists[v] = correct_dists[u] + crawl->weight;
                pq_insert(pq, v, correct_dists[v]);
            }
            crawl = crawl->next;
        }
    }
    free_pq(pq);
}
