/**
 * @file sssp_common.h
 * @brief Common definitions and types for the SSSP algorithm implementation
 * 
 * This file contains shared definitions, types, and constants used across
 * the production-grade implementation of the SSSP algorithm from arXiv:2504.17033v2.
 * 
 * @author Sambit Chakraborty
 * @date 2025
 * @version 1.0
 */

#ifndef SSSP_COMMON_H
#define SSSP_COMMON_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

// Version information
#define SSSP_VERSION_MAJOR 1
#define SSSP_VERSION_MINOR 0
#define SSSP_VERSION_PATCH 0

// Compilation flags and compatibility
#ifndef SSSP_INLINE
#  ifdef __GNUC__
#    define SSSP_INLINE __inline__ __attribute__((always_inline))
#  elif defined(_MSC_VER)
#    define SSSP_INLINE __forceinline
#  else
#    define SSSP_INLINE inline
#  endif
#endif

#ifndef SSSP_LIKELY
#  ifdef __GNUC__
#    define SSSP_LIKELY(x) __builtin_expect(!!(x), 1)
#    define SSSP_UNLIKELY(x) __builtin_expect(!!(x), 0)
#  else
#    define SSSP_LIKELY(x) (x)
#    define SSSP_UNLIKELY(x) (x)
#  endif
#endif

// Memory alignment
#ifndef SSSP_ALIGN
#  ifdef __GNUC__
#    define SSSP_ALIGN(x) __attribute__((aligned(x)))
#  elif defined(_MSC_VER)
#    define SSSP_ALIGN(x) __declspec(align(x))
#  else
#    define SSSP_ALIGN(x)
#  endif
#endif

// Constants
#define SSSP_INITIAL_CAPACITY 16
#define SSSP_MAX_VERTICES 0x7FFFFFFF
#define SSSP_DEFAULT_BLOCK_SIZE 1024
#define SSSP_CACHE_LINE_SIZE 64

// Error codes
typedef enum {
    SSSP_SUCCESS = 0,
    SSSP_ERROR_NULL_POINTER = -1,
    SSSP_ERROR_INVALID_ARGUMENT = -2,
    SSSP_ERROR_INVALID_PARAMETER = -2,  // Alias for compatibility
    SSSP_ERROR_OUT_OF_MEMORY = -3,
    SSSP_ERROR_OVERFLOW = -4,
    SSSP_ERROR_GRAPH_INVALID = -5,
    SSSP_ERROR_IO = -6,
    SSSP_ERROR_NOT_IMPLEMENTED = -7,
    SSSP_ERROR_ALGORITHM = -8,
    SSSP_ERROR_INTERNAL = -99
} sssp_error_t;

// Vertex and weight types
typedef uint32_t vertex_id_t;
typedef double weight_t;
typedef double edge_weight_t;       // Alias for edge weights  
typedef double distance_t;          // Same as weight_t for consistency
typedef uint32_t vertex_count_t;
typedef uint32_t edge_count_t;      // Count of edges

// Special constants
#define SSSP_INVALID_VERTEX UINT32_MAX
#define SSSP_INVALID_POSITION UINT32_MAX

// Distance value with infinity support
#ifndef SSSP_INFINITY
#  ifdef INFINITY
#    define SSSP_INFINITY ((distance_t)INFINITY)
#  else
#    define SSSP_INFINITY ((distance_t)1e308)
#  endif
#endif

// Utility macros
#define SSSP_MAX(a, b) ((a) > (b) ? (a) : (b))
#define SSSP_MIN(a, b) ((a) < (b) ? (a) : (b))
#define SSSP_ABS(x) ((x) < 0 ? -(x) : (x))

// Memory management
typedef struct sssp_allocator {
    void* (*alloc)(size_t size, void* context);
    void* (*realloc)(void* ptr, size_t new_size, void* context);
    void (*free)(void* ptr, void* context);
    void* context;
} sssp_allocator_t;

// Default allocator using standard library
extern const sssp_allocator_t* sssp_default_allocator(void);
extern const sssp_allocator_t SSSP_DEFAULT_ALLOCATOR;

// Error handling
typedef void (*sssp_error_handler_t)(sssp_error_t error, const char* message, void* context);

// Set global error handler
void sssp_set_error_handler(sssp_error_handler_t handler, void* context);

// Get error string
const char* sssp_error_string(sssp_error_t error);

// Logging levels
typedef enum {
    SSSP_LOG_NONE = 0,
    SSSP_LOG_ERROR = 1,
    SSSP_LOG_WARN = 2,
    SSSP_LOG_INFO = 3,
    SSSP_LOG_DEBUG = 4,
    SSSP_LOG_TRACE = 5
} sssp_log_level_t;

// Logging function type
typedef void (*sssp_log_func_t)(sssp_log_level_t level, const char* file, int line, 
                                const char* func, const char* format, ...);

// Set logging function and level
void sssp_set_log_function(sssp_log_func_t func);
void sssp_set_log_level(sssp_log_level_t level);

// Logging macros
#define SSSP_LOG(level, ...) sssp_log((level), __FILE__, __LINE__, __func__, __VA_ARGS__)
#define SSSP_LOG_ERROR(...) SSSP_LOG(SSSP_LOG_ERROR, __VA_ARGS__)
#define SSSP_LOG_WARN(...) SSSP_LOG(SSSP_LOG_WARN, __VA_ARGS__)
#define SSSP_LOG_INFO(...) SSSP_LOG(SSSP_LOG_INFO, __VA_ARGS__)
#define SSSP_LOG_DEBUG(...) SSSP_LOG(SSSP_LOG_DEBUG, __VA_ARGS__)
#define SSSP_LOG_TRACE(...) SSSP_LOG(SSSP_LOG_TRACE, __VA_ARGS__)

// Internal logging function
void sssp_log(sssp_log_level_t level, const char* file, int line, 
              const char* func, const char* format, ...);

// Internal error reporting
void sssp_report_error(sssp_error_t error, const char* message);

// Safe arithmetic operations
bool sssp_safe_add_vertex_count(vertex_count_t a, vertex_count_t b, vertex_count_t* result);
bool sssp_safe_mul_vertex_count(vertex_count_t a, vertex_count_t b, vertex_count_t* result);

// Memory allocation wrappers
void* sssp_alloc(const sssp_allocator_t* allocator, size_t size);
void* sssp_realloc(const sssp_allocator_t* allocator, void* ptr, size_t new_size);
void sssp_free(const sssp_allocator_t* allocator, void* ptr);

// Performance profiling
typedef struct sssp_timer {
    uint64_t start_time;
    uint64_t end_time;
    bool is_running;
} sssp_timer_t;

// Timer functions
void sssp_timer_start(sssp_timer_t* timer);
void sssp_timer_stop(sssp_timer_t* timer);
double sssp_timer_elapsed_ms(const sssp_timer_t* timer);
uint64_t sssp_get_timestamp_ns(void);

// Memory usage tracking
typedef struct sssp_memory_stats {
    size_t current_bytes;
    size_t peak_bytes;
    size_t total_allocations;
    size_t total_deallocations;
} sssp_memory_stats_t;

void sssp_memory_stats_reset(sssp_memory_stats_t* stats);
void sssp_memory_stats_add_allocation(sssp_memory_stats_t* stats, size_t bytes);
void sssp_memory_stats_add_deallocation(sssp_memory_stats_t* stats, size_t bytes);

// Thread safety (if needed in future)
#ifdef SSSP_THREAD_SAFE
#include <pthread.h>
typedef pthread_mutex_t sssp_mutex_t;
#define SSSP_MUTEX_INIT PTHREAD_MUTEX_INITIALIZER
#define sssp_mutex_lock pthread_mutex_lock
#define sssp_mutex_unlock pthread_mutex_unlock
#define sssp_mutex_init pthread_mutex_init
#define sssp_mutex_destroy pthread_mutex_destroy
#else
typedef int sssp_mutex_t;
#define SSSP_MUTEX_INIT 0
#define sssp_mutex_lock(m) ((void)(m))
#define sssp_mutex_unlock(m) ((void)(m))
#define sssp_mutex_init(m, a) ((void)(m), (void)(a))
#define sssp_mutex_destroy(m) ((void)(m))
#endif

#ifdef __cplusplus
}
#endif

#endif // SSSP_COMMON_H
