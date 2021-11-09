
set(UNITY_DIR ${CMAKE_SOURCE_DIR}/throwtheswitch/unity)
set(TEST_RUNNER_DIR ${CMAKE_BINARY_DIR}/utilities/linked_lists/CMakeFiles)

file(GLOB SOURCES src/*.c)
file(GLOB GENERATE_TEST_RUNNER ${UNITY_DIR}/auto/generate_test_runner.rb)


if(NOT EXISTS ${TEST_RUNNER_DIR})
    file(MAKE_DIRECTORY ${TEST_RUNNER_DIR})
endif(NOT EXISTS ${TEST_RUNNER_DIR})


add_definitions(-DUNITY_INCLUDE_CONFIG_H)
include_directories(inc ${UNITY_DIR} ${UNITY_DIR}/src)


foreach(SRC_FILE ${SOURCES})

    get_filename_component(FILENAME ${SRC_FILE} NAME_WE)


    execute_process(COMMAND ruby ${GENERATE_TEST_RUNNER} 
                                 ${CMAKE_CURRENT_LIST_DIR}/unit_tests/test_${FILENAME}.c
                                 ${TEST_RUNNER_DIR}/test_${FILENAME}_runner.c)


    add_library(${FILENAME} OBJECT ${SRC_FILE})
    
    add_library(test_${FILENAME} OBJECT ${CMAKE_CURRENT_LIST_DIR}/unit_tests/test_${FILENAME}.c)
    target_link_libraries(test_${FILENAME} PUBLIC unity ${FILENAME})

    add_executable(test_${FILENAME}_runner ${TEST_RUNNER_DIR}/test_${FILENAME}_runner.c)
    target_link_libraries(test_${FILENAME}_runner PUBLIC unity ${FILENAME} test_${FILENAME})
    
    add_custom_command(TARGET test_${FILENAME}_runner POST_BUILD
                       WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/unit_tests
                       COMMAND $<TARGET_FILE:test_${FILENAME}_runner>)

endforeach(SRC_FILE ${SOURCES})

