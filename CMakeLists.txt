cmake_minimum_required (VERSION 3.22)
project(c_utilities C)

include(cmake/config.cmake)

add_subdirectory(Third-Party/Unity)
target_compile_definitions(unity PUBLIC UNITY_INCLUDE_CONFIG_H)

option(SKIP_BINARY_TREES_LIB "Skip building the binary trees library" OFF)
option(SKIP_LINKED_LISTS_LIB "Skip building the linked lists library" OFF)
option(SKIP_VECTOR_LIB "Skip building the vector library" OFF)

message(STATUS "skip binary trees is equal to ${SKIP_BINARY_TREES_LIB}")
message(STATUS "skip linked lists is equal to ${SKIP_LINKED_LISTS_LIB}")
message(STATUS "skip vector is equal to ${SKIP_VECTOR_LIB}")

if (NOT SKIP_BINARY_TREES_LIB)
    add_subdirectory(utilities/binary_trees)
endif()

if (NOT SKIP_LINKED_LISTS_LIB)
    add_subdirectory(utilities/linked_lists)
endif()

if (NOT SKIP_VECTOR_LIB)
    add_subdirectory(utilities/vector)
endif()
