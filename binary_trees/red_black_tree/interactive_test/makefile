CXX = gcc
CXXFLAGS = -c -g -Wall -pedantic
LDFLAGS =

INC_DIR=../

test_tree: test_tree.o $(INC_DIR)/red_black_tree.o
	make -C $(INC_DIR) -f makefile
	$(CXX) -I$(INC_DIR) test_tree.o $(INC_DIR)red_black_tree.o -o test_tree $(LDFLAGS)

test_tree.o: test_tree.c $(INC_DIR)red_black_tree.h
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) test_tree.c

clean:
	rm -f *o test_tree
	make -C ../ clean
