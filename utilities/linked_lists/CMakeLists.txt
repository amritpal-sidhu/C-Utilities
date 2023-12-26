project(linked_lists)

set(LOCAL_SOURCES queue.c stack.c)
list(TRANSFORM LOCAL_SOURCES PREPEND "${CMAKE_CURRENT_LIST_DIR}/src/")

add_library(${PROJECT_NAME} STATIC ${LOCAL_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC inc)

if (NOT ${SKIP_C_UTILITIES_TESTS})
    run_tests_macro()
endif()
