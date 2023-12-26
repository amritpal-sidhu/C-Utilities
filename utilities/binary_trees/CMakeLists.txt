project(binary_trees)

set(LOCAL_SOURCES avl_tree.c binary_search_tree.c red_black_tree.c)
list(TRANSFORM LOCAL_SOURCES PREPEND "${CMAKE_CURRENT_LIST_DIR}/src/")

add_library(${PROJECT_NAME} STATIC ${LOCAL_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC inc)

if (NOT ${SKIP_C_UTILITIES_TESTS})
    run_tests_macro()
endif()
