cmake_minimum_required (VERSION 3.22)
project(C-Utilities)

include_directories(Third-Party)
add_definitions(-DUNITY_INCLUDE_CONFIG_H)

add_subdirectory(Third-Party/Unity)

add_subdirectory(utilities/binary_trees)
add_subdirectory(utilities/linked_lists)
