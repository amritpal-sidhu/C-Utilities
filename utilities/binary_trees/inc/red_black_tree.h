/**
 * Red Black Tree implementation in C
 */

#pragma once

#include "binary_tree_types.h"

typedef enum {
    RED,
    BLACK
} rb_node_color_t;

typedef struct rb_node_s {

    void *obj;
    struct rb_node_s *parent;
    struct rb_node_s *left;
    struct rb_node_s *right;
    rb_node_color_t color;

} rb_node_t;

typedef struct rb_s {

    rb_node_t *root;
    unsigned int element_size;
    compare_function_t cmp_f;
    unsigned int size;

} rb_t;


/**
 *  Compare function should return:
 *      < 0 when a < b
 *        0 when a == b
 *      > 0 when a > b
 * 
 *  @param rb: reference to rb tree handle
 *  @param element_size: size of objects/elements to be stored in bst nodes
 *  @param cmp_f: function used to compare bst objects/elements
 *  @return True (1) when bst handle can be initialized
 *          False (0) in the case bst handle doesn't exist or objects have been put
 *          into the tree already.
 */
rb_t *red_black_tree__new(const unsigned int element_size, compare_function_t cmp_f);
void red_black_tree__delete(rb_t *rb);
int red_black_tree__insert(rb_t *rb, const void *obj);
int red_black_tree__remove(rb_t *rb, const void *obj);
int red_black_tree__min(rb_t *rb, rb_node_t *min);
int red_black_tree__max(rb_t *rb, rb_node_t *max);
int red_black_tree__find(rb_t *rb, const void *obj, rb_node_t *node);
