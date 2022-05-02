cmake_minimum_required (VERSION 3.22)
project(C_Utilities)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
include(cmake/config.cmake)
include_guard(GLOBAL)

add_subdirectory(Third-Party/Unity)
target_compile_definitions(unity PUBLIC UNITY_INCLUDE_CONFIG_H)

add_subdirectory(utilities/binary_trees)
add_subdirectory(utilities/linked_lists)
