
file(GLOB SOURCES src/*.c)
# file(GLOB TESTS unit_tests/*.c)

include_directories(inc)

add_library(binary_trees STATIC ${SOURCES})

# foreach(TEST ${TESTS})
#     execute_process(COMMAND ruby ${TEST}
#                     OUTPUT_FILE ${}/test_${TEST}_runner.c)
# endforeach(TEST ${TESTS})

# add_executable(test__trees ${TESTS})
# target_link_libraries(test_binary_trees binary_trees unity)

add_executable(run_rb_test)
target_sources(run_rb_test unity binary_trees unit_tests/test_red_black_tree_runner.c )
