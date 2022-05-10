cmake_minimum_required (VERSION 3.22)
project(c_utilities C)

include(cmake/config.cmake)

add_subdirectory(Third-Party/Unity)
target_compile_definitions(unity PUBLIC UNITY_INCLUDE_CONFIG_H)

add_subdirectory(utilities/binary_trees)
add_subdirectory(utilities/linked_lists)
