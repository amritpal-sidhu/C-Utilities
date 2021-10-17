C_COMPILER = gcc

CFLAGS=-std=c89
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wpointer-arith
CFLAGS += -Wcast-align
CFLAGS += -Wwrite-strings
CFLAGS += -Wswitch-default
CFLAGS += -Wunreachable-code
CFLAGS += -Winit-self
CFLAGS += -Wmissing-field-initializers
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
CFLAGS += -Wold-style-definition

UNITY_ROOT=../throwtheswitch/unity
TREE_ROOT=../../binary_trees

TARGET1=test_binary_search_tree.out
DIR1=$(TREE_ROOT)/binary_search_tree
INC_DIRS1=-I$(DIR1) -I$(UNITY_ROOT)/src
SRC_FILES1=$(UNITY_ROOT)/src/unity.c src/test_binary_search_tree.c src/test_runners/test_binary_search_tree.c
OBJ_FILES1=$(DIR1)/binary_tree.o

TARGET2=test_red_black_tree.out
DIR2=$(TREE_ROOT)/red_black_tree
INC_DIRS2=-I$(DIR2) -I$(UNITY_ROOT)/src
SRC_FILES2=$(UNITY_ROOT)/src/unity.c src/test_red_black_tree.c src/test_runners/test_red_black_tree.c
OBJ_FILES2=$(DIR2)/red_black_tree.o

SYMBOLS=

all: clean default

default: $(SRC_FILES1) $(SRC_FILES2)
	make -C $(DIR1) -f makefile
	make -C $(DIR2) -f makefile
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS1) $(SYMBOLS) $(SRC_FILES1) $(OBJ_FILES1) -o $(TARGET1)
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS2) $(SYMBOLS) $(SRC_FILES2) $(OBJ_FILES2) -o $(TARGET2)
	- ./$(TARGET1)
	- ./$(TARGET2)

src/test_runners/test_binary_search_tree.c: src/test_binary_search_tree.c
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb src/test_binary_search_tree.c src/test_runners/test_binary_search_tree.c
src/test_runners/test_red_black_tree.c: src/test_red_black_tree.c
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb src/test_red_black_tree.c src/test_runners/test_red_black_tree.c

clean:
	rm -f $(TARGET1) $(TARGET2) 
	make -C $(DIR1) clean
	make -C $(DIR2) clean

ci: CFLAGS += -Werror
ci: default
