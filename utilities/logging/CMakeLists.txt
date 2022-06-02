project(logging)

set(LOCAL_SOURCES logging.c)
list(TRANSFORM LOCAL_SOURCES PREPEND ${CMAKE_CURRENT_LIST_DIR}/src/)

add_library(${PROJECT_NAME} STATIC ${LOCAL_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC inc)

run_tests_macro()
