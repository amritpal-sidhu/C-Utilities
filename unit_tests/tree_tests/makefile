C_COMPILER = gcc

CFLAGS=-Wall
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

GLOBAL_INC=-I$(UNITY_ROOT)/src -I$(UNITY_ROOT)
GLOBAL_SRC=$(UNITY_ROOT)/src/unity.c

TREE1=binary_search_tree
TARGET_BASE1=test_$(TREE1)
TARGET1=$(TARGET_BASE1).out
DIR1=$(TREE_ROOT)/$(TREE1)
INC_DIRS1=-I$(DIR1) $(GLOBAL_INC)
SRC_FILES1=$(GLOBAL_SRC) src/$(TARGET_BASE1).c src/test_runners/$(TARGET_BASE1).c
OBJ_FILES1=$(DIR1)/$(TREE1).o

TREE2=red_black_tree
TARGET_BASE2=test_$(TREE2)
TARGET2=$(TARGET_BASE2).out
DIR2=$(TREE_ROOT)/$(TREE2)
INC_DIRS2=-I$(DIR2) $(GLOBAL_INC)
SRC_FILES2=$(GLOBAL_SRC) src/$(TARGET_BASE2).c src/test_runners/$(TARGET_BASE2).c
OBJ_FILES2=$(DIR2)/$(TREE2).o

TREE3=avl_tree
TARGET_BASE3=test_$(TREE3)
TARGET3=$(TARGET_BASE3).out
DIR3=$(TREE_ROOT)/$(TREE3)
INC_DIRS3=-I$(DIR3) $(GLOBAL_INC)
SRC_FILES3=$(GLOBAL_SRC) src/$(TARGET_BASE3).c src/test_runners/$(TARGET_BASE3).c
OBJ_FILES3=$(DIR3)/$(TREE3).o

SYMBOLS=
DEF=-DUNITY_INCLUDE_CONFIG_H

all: clean default

default: $(SRC_FILES1) $(SRC_FILES2) $(SRC_FILES3)
	make -C $(DIR1) -f makefile
	$(C_COMPILER) $(CFLAGS) $(DEF) $(INC_DIRS1) $(SYMBOLS) $(SRC_FILES1) $(OBJ_FILES1) -o $(TARGET1)
	- ./$(TARGET1)

	make -C $(DIR2) -f makefile
	$(C_COMPILER) $(CFLAGS) $(DEF) $(INC_DIRS2) $(SYMBOLS) $(SRC_FILES2) $(OBJ_FILES2) -o $(TARGET2)
	- ./$(TARGET2)

	make -C $(DIR3) -f makefile
	$(C_COMPILER) $(CFLAGS) $(DEF) $(INC_DIRS3) $(SYMBOLS) $(SRC_FILES3) $(OBJ_FILES3) -o $(TARGET3)
	- ./$(TARGET3)

src/test_runners/$(TARGET_BASE1).c: src/$(TARGET_BASE1).c
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb src/$(TARGET_BASE1).c src/test_runners/$(TARGET_BASE1).c
src/test_runners/$(TARGET_BASE2).c: src/$(TARGET_BASE2).c
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb src/$(TARGET_BASE2).c src/test_runners/$(TARGET_BASE2).c
src/test_runners/$(TARGET_BASE3).c: src/$(TARGET_BASE3).c
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb src/$(TARGET_BASE3).c src/test_runners/$(TARGET_BASE3).c

clean:
	rm -f $(TARGET1) $(TARGET2) $(TARGET3)
	make -C $(DIR1) clean
	make -C $(DIR2) clean
	make -C $(DIR3) clean

ci: CFLAGS += -Werror
ci: default
