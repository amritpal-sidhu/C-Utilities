
add_definitions(-DUNITY_INCLUDE_CONFIG_H)
include_directories(. src)
add_library(unity OBJECT src/unity.c)
