cmake_minimum_required(VERSION 3.16)
project(production_sssp 
        VERSION 1.0.0 
        DESCRIPTION "Production-grade SSSP algorithm implementation"
        LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags
set(CMAKE_C_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Wpedantic -Wformat=2 -Wno-unused-parameter")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG -Wall -Wextra -march=native -flto")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG -Wall -Wextra -march=native")

# Options
option(SSSP_BUILD_TESTS "Build tests" ON)
option(SSSP_BUILD_BENCHMARKS "Build benchmarks" ON)
option(SSSP_ENABLE_PROFILING "Enable profiling support" OFF)
option(SSSP_THREAD_SAFE "Enable thread safety" OFF)
option(SSSP_ENABLE_SANITIZERS "Enable address and undefined behavior sanitizers" OFF)

# Find packages
find_package(Threads REQUIRED)

if(SSSP_BUILD_TESTS)
    # Try to find a testing framework
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(CHECK check)
    endif()
endif()

# Include directories
include_directories(include)

# Compile definitions
if(SSSP_THREAD_SAFE)
    add_definitions(-DSSSP_THREAD_SAFE)
endif()

if(SSSP_ENABLE_PROFILING)
    add_definitions(-DSSSP_ENABLE_PROFILING)
endif()

# Sanitizers
if(SSSP_ENABLE_SANITIZERS AND CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address -fsanitize=undefined")
endif()

# Source files
set(SSSP_SOURCES
    src/sssp_common.c
    src/vertex_set.c
    src/graph.c
    src/partitioning_heap.c
    src/find_pivots.c
    src/sssp_algorithm.c
)

set(SSSP_HEADERS
    include/sssp_common.h
    include/vertex_set.h
    include/graph.h
    include/partitioning_heap.h
    include/find_pivots.h
    include/sssp_algorithm.h
)

# Create the main library
add_library(sssp STATIC ${SSSP_SOURCES} ${SSSP_HEADERS})
target_link_libraries(sssp PRIVATE Threads::Threads m)

# Set library properties
set_target_properties(sssp PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "${SSSP_HEADERS}"
)

# Create shared library variant
add_library(sssp_shared SHARED ${SSSP_SOURCES} ${SSSP_HEADERS})
target_link_libraries(sssp_shared PRIVATE Threads::Threads m)
set_target_properties(sssp_shared PROPERTIES
    OUTPUT_NAME sssp
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Demo executable
add_executable(sssp_demo demo.c)
target_link_libraries(sssp_demo PRIVATE sssp m)

# Test executable
add_executable(test_sssp test_sssp.c)
target_link_libraries(test_sssp PRIVATE sssp m)

# Tests
if(SSSP_BUILD_TESTS)
    enable_testing()
    add_test(NAME comprehensive_tests COMMAND test_sssp)
endif()

# Note: Example programs and benchmarks would go in separate directories
# This is a simplified structure with just the core demo and test programs

# Installation
include(GNUInstallDirs)

install(TARGETS sssp sssp_shared
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sssp
)

install(TARGETS sssp_demo test_sssp
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Create pkg-config file
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/sssp.pc.in"
    "${CMAKE_CURRENT_BINARY_DIR}/sssp.pc"
    @ONLY
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/sssp.pc"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)

# Documentation
find_package(Doxygen QUIET)
if(Doxygen_FOUND)
    set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/docs")
    set(DOXYGEN_PROJECT_NAME "Production SSSP")
    set(DOXYGEN_PROJECT_BRIEF "Production-grade SSSP algorithm implementation")
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_LATEX NO)
    
    doxygen_add_docs(docs
        ${SSSP_HEADERS} ${SSSP_SOURCES}
        COMMENT "Generating documentation"
    )
endif()

# Print configuration summary
message(STATUS "")
message(STATUS "Configuration Summary:")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C Compiler: ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "  Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "  Thread safety: ${SSSP_THREAD_SAFE}")
message(STATUS "  Profiling: ${SSSP_ENABLE_PROFILING}")
message(STATUS "  Sanitizers: ${SSSP_ENABLE_SANITIZERS}")
message(STATUS "  Build tests: ${SSSP_BUILD_TESTS}")
message(STATUS "  Build benchmarks: ${SSSP_BUILD_BENCHMARKS}")
message(STATUS "")
