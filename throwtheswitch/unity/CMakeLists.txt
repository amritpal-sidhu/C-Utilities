
add_library(unity SHARED src/unity.c)
target_include_directories(unity 
                            PUBLIC .
                            PUBLIC src)
