#pragma once
/**
 * Simple binary search tree implementation in C for practice and
 * future reference.
 */

typedef int (*compare_function_t)(const void *a, const void *b);

typedef struct bst_node_s {

    void *obj;
    struct bst_node_s *left;
    struct bst_node_s *right;

} bst_node_s;

typedef struct bst_s {

    bst_node_s *root;
    unsigned int element_size;
    compare_function_t compare_function;
    unsigned int size;
    
} bst_s;

/**
 *  Initialize the bst handle to 0 or NULL
 *      e.g. bst_s bst = {0};
 * 
 *  Compare function should return:
 *      < 0 when a < b
 *        0 when a == b
 *      > 0 when a > b
 * 
 *  @param bst: reference to binary search tree handle
 *  @param element_size: size of objects/elements to be stored in bst nodes
 *  @param compare_function: function used to compare bst objects/elements
 *  @return True (1) when bst handle can be initialized
 *          False (0) in the case bst handle doesn't exist or objects have been put
 *          into the tree already.
 */
int binary_search_tree__init(bst_s *bst, const unsigned int element_size, compare_function_t compare_function);
int binary_search_tree__insert(bst_s *bst, const void *obj);
int binary_search_tree__delete(bst_s *bst, const void *obj);
int binary_search_tree__min(bst_s *bst, bst_node_s *min);
int binary_search_tree__max(bst_s *bst, bst_node_s *max);
int binary_search_tree__find(bst_s *bst, const void *obj, bst_node_s *node);
