#pragma once

#include "binary_tree_types.h"

typedef struct avl_node_s {
    
    void *obj;
    struct avl_node_s *left;
    struct avl_node_s *right;
    unsigned height;

} avl_node_t;

typedef struct avl_s {

    avl_node_t *root;
    unsigned int element_size;
    compare_function_t cmp_f;
    unsigned int size;

} avl_t;


/**
 *  Compare function should return:
 *      < 0 when a < b
 *        0 when a == b
 *      > 0 when a > b
 * 
 *  @param avl: reference to avl tree handle
 *  @param element_size: size of objects/elements to be stored in bst nodes
 *  @param cmp_f: function used to compare bst objects/elements
 *  @return True (1) when bst handle can be initialized
 *          False (0) in the case bst handle doesn't exist or objects have been put
 *          into the tree already.
 */
avl_t *avl_tree__new(const unsigned int element_size, compare_function_t cmp_f);
void avl_tree__delete(avl_t *avl);
int avl_tree__insert(avl_t *avl, const void *obj);
int avl_tree__remove(avl_t *avl, const void *obj);
int avl_tree__min(avl_t *avl, avl_node_t *min);
int avl_tree__max(avl_t *avl, avl_node_t *max);
int avl_tree__find(avl_t *avl, const void *obj, avl_node_t *node);
