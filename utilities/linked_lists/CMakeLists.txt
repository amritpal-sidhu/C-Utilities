project(linked_lists)

file(GLOB LOCAL_SOURCES src/*.c)

add_library(${PROJECT_NAME} STATIC ${LOCAL_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC inc)

run_tests_macro()
