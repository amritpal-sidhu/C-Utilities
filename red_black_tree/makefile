CXX = gcc
CXXFLAGS = -c -g -Wall -pedantic
LDFLAGS =

test_tree: test_tree.o red_black_tree.o
	$(CXX) test_tree.o red_black_tree.o -o test_tree $(LDFLAGS)

test_tree.o: test_tree.c red_black_tree.h
	$(CXX) $(CXXFLAGS) test_tree.c

red_black_tree.o: red_black_tree.c red_black_tree.h
	$(CXX) $(CXXFLAGS) red_black_tree.c

clean:
	rm -f *o test_tree
