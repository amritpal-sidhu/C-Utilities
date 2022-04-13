#pragma once

#include "binary_tree_types.h"

typedef struct avl_node_s {
    
    void *obj;
    struct avl_node_s *left;
    struct avl_node_s *right;
    unsigned height;

} avl_node_s;

typedef struct avl_s {

    avl_node_s *root;
    unsigned int element_size;
    compare_function_t compare_function;
    unsigned int size;

} avl_s;


/**
 *  Initialize the bst handle to 0 or NULL
 *      e.g. avl_s bst = {0};
 * 
 *  Compare function should return:
 *      < 0 when a < b
 *        0 when a == b
 *      > 0 when a > b
 * 
 *  @param avl: reference to avl tree handle
 *  @param element_size: size of objects/elements to be stored in bst nodes
 *  @param compare_function: function used to compare bst objects/elements
 *  @return True (1) when bst handle can be initialized
 *          False (0) in the case bst handle doesn't exist or objects have been put
 *          into the tree already.
 */
int avl_tree__init(avl_s *avl, const unsigned int element_size, compare_function_t compare_function);
int avl_tree__insert(avl_s *avl, const void *obj);
int avl_tree__delete(avl_s *avl, const void *obj);
int avl_tree__min(avl_s *avl, avl_node_s *min);
int avl_tree__max(avl_s *avl, avl_node_s *max);
int avl_tree__find(avl_s *avl, const void *obj, avl_node_s *node);
