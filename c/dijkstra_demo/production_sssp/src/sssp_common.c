/**
 * @file sssp_common.c
 * @brief Implementation of common utilities and error handling
 * 
 * @author Sambit Chakraborty
 * @date 21-08-2025
 * @version 1.0
 */

#define _POSIX_C_SOURCE 199309L

#include "../include/sssp_common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <errno.h>

#if defined(__linux__) || defined(__APPLE__)
    #include <unistd.h>
    #include <sys/time.h>
#elif defined(_WIN32)
    #include <windows.h>
#endif

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

// Global state
static sssp_error_handler_t g_error_handler = NULL;
static void* g_error_context = NULL;
static sssp_log_func_t g_log_func = NULL;
static sssp_log_level_t g_log_level = SSSP_LOG_WARN;

// Default allocator implementation
static void* default_alloc(size_t size, void* context) {
    (void)context;
    return malloc(size);
}

static void* default_realloc(void* ptr, size_t new_size, void* context) {
    (void)context;
    return realloc(ptr, new_size);
}

static void default_free(void* ptr, void* context) {
    (void)context;
    free(ptr);
}

// Default allocator constant
const sssp_allocator_t SSSP_DEFAULT_ALLOCATOR = {
    .alloc = default_alloc,
    .realloc = default_realloc,
    .free = default_free,
    .context = NULL
};

static const sssp_allocator_t default_allocator_impl = {
    .alloc = default_alloc,
    .realloc = default_realloc,
    .free = default_free,
    .context = NULL
};

const sssp_allocator_t* sssp_default_allocator(void) {
    return &default_allocator_impl;
}

// Error handling
void sssp_set_error_handler(sssp_error_handler_t handler, void* context) {
    g_error_handler = handler;
    g_error_context = context;
}

const char* sssp_error_string(sssp_error_t error) {
    switch (error) {
        case SSSP_SUCCESS:
            return "Success";
        case SSSP_ERROR_NULL_POINTER:
            return "Null pointer";
        case SSSP_ERROR_INVALID_ARGUMENT:
            return "Invalid argument";
        case SSSP_ERROR_OUT_OF_MEMORY:
            return "Out of memory";
        case SSSP_ERROR_OVERFLOW:
            return "Numeric overflow";
        case SSSP_ERROR_GRAPH_INVALID:
            return "Invalid graph";
        case SSSP_ERROR_NOT_IMPLEMENTED:
            return "Not implemented";
        case SSSP_ERROR_INTERNAL:
            return "Internal error";
        default:
            return "Unknown error";
    }
}

// Logging
void sssp_set_log_function(sssp_log_func_t func) {
    g_log_func = func;
}

void sssp_set_log_level(sssp_log_level_t level) {
    g_log_level = level;
}

static void default_log_func(sssp_log_level_t level, const char* file, int line,
                           const char* func, const char* format, ...) {
    if (level > g_log_level) return;
    
    const char* level_str;
    switch (level) {
        case SSSP_LOG_ERROR: level_str = "ERROR"; break;
        case SSSP_LOG_WARN:  level_str = "WARN";  break;
        case SSSP_LOG_INFO:  level_str = "INFO";  break;
        case SSSP_LOG_DEBUG: level_str = "DEBUG"; break;
        case SSSP_LOG_TRACE: level_str = "TRACE"; break;
        default:             level_str = "LOG";   break;
    }
    
    fprintf(stderr, "[%s] %s:%d in %s(): ", level_str, file, line, func);
    
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    
    fprintf(stderr, "\n");
    fflush(stderr);
}

void sssp_log(sssp_log_level_t level, const char* file, int line,
              const char* func, const char* format, ...) {
    if (level > g_log_level) return;
    
    sssp_log_func_t log_func = g_log_func ? g_log_func : default_log_func;
    
    va_list args;
    va_start(args, format);
    
    // Unfortunately, we need to format the string first since we can't pass va_list
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);
    
    log_func(level, file, line, func, "%s", buffer);
    
    va_end(args);
}

// Timer functions
void sssp_timer_start(sssp_timer_t* timer) {
    if (!timer) return;
    timer->start_time = sssp_get_timestamp_ns();
    timer->is_running = true;
}

void sssp_timer_stop(sssp_timer_t* timer) {
    if (!timer || !timer->is_running) return;
    timer->end_time = sssp_get_timestamp_ns();
    timer->is_running = false;
}

double sssp_timer_elapsed_ms(const sssp_timer_t* timer) {
    if (!timer) return 0.0;
    
    uint64_t end_time = timer->is_running ? sssp_get_timestamp_ns() : timer->end_time;
    uint64_t elapsed_ns = end_time - timer->start_time;
    return (double)elapsed_ns / 1000000.0; // Convert to milliseconds
}

uint64_t sssp_get_timestamp_ns(void) {
#ifdef _WIN32
    LARGE_INTEGER frequency, counter;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&counter);
    return (uint64_t)((counter.QuadPart * 1000000000ULL) / frequency.QuadPart);
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
#endif
}

// Memory statistics
void sssp_memory_stats_reset(sssp_memory_stats_t* stats) {
    if (!stats) return;
    memset(stats, 0, sizeof(*stats));
}

void sssp_memory_stats_add_allocation(sssp_memory_stats_t* stats, size_t bytes) {
    if (!stats) return;
    stats->current_bytes += bytes;
    if (stats->current_bytes > stats->peak_bytes) {
        stats->peak_bytes = stats->current_bytes;
    }
    stats->total_allocations++;
}

void sssp_memory_stats_add_deallocation(sssp_memory_stats_t* stats, size_t bytes) {
    if (!stats) return;
    if (stats->current_bytes >= bytes) {
        stats->current_bytes -= bytes;
    }
    stats->total_deallocations++;
}

// Internal error reporting
void sssp_report_error(sssp_error_t error, const char* message) {
    if (g_error_handler) {
        g_error_handler(error, message, g_error_context);
    } else {
        SSSP_LOG_ERROR("Error %d: %s", error, message ? message : sssp_error_string(error));
    }
}

// Utility functions for safe arithmetic
bool sssp_safe_add_vertex_count(vertex_count_t a, vertex_count_t b, vertex_count_t* result) {
    if (a > SSSP_MAX_VERTICES - b) {
        return false; // Overflow
    }
    *result = a + b;
    return true;
}

bool sssp_safe_mul_vertex_count(vertex_count_t a, vertex_count_t b, vertex_count_t* result) {
    if (a != 0 && b > SSSP_MAX_VERTICES / a) {
        return false; // Overflow
    }
    *result = a * b;
    return true;
}

// Memory allocation wrappers
void* sssp_alloc(const sssp_allocator_t* allocator, size_t size) {
    if (!allocator) allocator = sssp_default_allocator();
    return allocator->alloc(size, allocator->context);
}

void* sssp_realloc(const sssp_allocator_t* allocator, void* ptr, size_t new_size) {
    if (!allocator) allocator = sssp_default_allocator();
    return allocator->realloc(ptr, new_size, allocator->context);
}

void sssp_free(const sssp_allocator_t* allocator, void* ptr) {
    if (!allocator) allocator = sssp_default_allocator();
    allocator->free(ptr, allocator->context);
}
