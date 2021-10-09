CXX = gcc
CXXFLAGS = -c -g -Wall -pedantic
LDFLAGS =

test_tree: test_tree.o binary_tree.o
	$(CXX) test_tree.o binary_tree.o -o test_tree $(LDFLAGS)

test_tree.o: test_tree.c binary_tree.h
	$(CXX) $(CXXFLAGS) test_tree.c

binary_tree.o: binary_tree.c binary_tree.h
	$(CXX) $(CXXFLAGS) binary_tree.c

clean:
	rm -f *o test_tree
