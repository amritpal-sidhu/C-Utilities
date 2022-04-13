/**
 * Red Black Tree implementation in C
 */

#pragma once

#include "binary_tree_types.h"

typedef enum {
    RED,
    BLACK
} rb_node_color_e;

typedef struct rb_node_s {

    void *obj;
    struct rb_node_s *parent;
    struct rb_node_s *left;
    struct rb_node_s *right;
    rb_node_color_e color;

} rb_node_s;

typedef struct rb_s {

    rb_node_s *root;
    unsigned int element_size;
    compare_function_t compare_function;
    unsigned int size;

} rb_s;


int red_black_tree__init(rb_s *rb, const unsigned int element_size, compare_function_t compare_function);
int red_black_tree__insert(rb_s *rb, const void *obj);
int red_black_tree__delete(rb_s *rb, const void *obj);
int red_black_tree__min(rb_s *rb, rb_node_s *min);
int red_black_tree__max(rb_s *rb, rb_node_s *max);
int red_black_tree__find(rb_s *rb, const void *obj, rb_node_s *node);
