/**
 * Simple binary search tree implementation in C for practice and
 * future reference.
 */
#pragma once

#include "binary_tree_types.h"

typedef struct bst_node_s {

    void *obj;
    struct bst_node_s *left;
    struct bst_node_s *right;

} bst_node_t;

typedef struct bst_s {

    bst_node_t *root;
    unsigned int element_size;
    compare_function_t cmp_f;
    unsigned int size;
    
} bst_t;


/**
 *  Compare function should return:
 *      < 0 when a < b
 *        0 when a == b
 *      > 0 when a > b
 * 
 *  @param bst: reference to binary search tree handle
 *  @param element_size: size of objects/elements to be stored in bst nodes
 *  @param cmp_f: function used to compare bst objects/elements
 *  @return True (1) when bst handle can be initialized
 *          False (0) in the case bst handle doesn't exist or objects have been put
 *          into the tree already.
 */
bst_t *binary_search_tree__new(const unsigned int element_size, compare_function_t cmp_f);
void binary_search_tree__delete(bst_t *bst);
int binary_search_tree__insert(bst_t *bst, const void *obj);
int binary_search_tree__remove(bst_t *bst, const void *obj);
int binary_search_tree__min(bst_t *bst, bst_node_t *min);
int binary_search_tree__max(bst_t *bst, bst_node_t *max);
int binary_search_tree__find(bst_t *bst, const void *obj, bst_node_t *node);
