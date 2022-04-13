#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "red_black_tree.h"


/**
 * Private functions declarations
 */
static rb_node_s *left_rotate(rb_node_s **root, rb_node_s *pivot);
static rb_node_s *right_rotate(rb_node_s **root, rb_node_s *pivot);
static void insert_fixup(rb_node_s **root, rb_node_s *node);
static void delete_fixup(rb_node_s **root, rb_node_s *node);
static void transplant(rb_node_s **root, const rb_node_s *old_node, rb_node_s *new_node);
static void insert_helper(rb_s *rb, rb_node_s **root, rb_node_s *new_node);
static void delete_helper(rb_s *rb, rb_node_s **root, const void *obj);
static rb_node_s *min_helper(rb_node_s *node);
static rb_node_s *max_helper(rb_node_s *node);
static rb_node_s *find_helper(rb_s *rb, rb_node_s *root, const void *obj);



/**
 * Public function definitions
 */
int red_black_tree__init(rb_s *rb, const unsigned int element_size, compare_function_t compare_function)
{
    int valid = rb && !rb->size && element_size && compare_function;

    if (valid) {

        rb->root = NULL;
        rb->element_size = element_size;
        rb->compare_function = compare_function;
        rb->size = 0;
    }

    return valid;
}

int red_black_tree__insert(rb_s *rb, const void *obj)
{
    int valid = rb && rb->element_size && rb->compare_function && obj;

    if (valid) {

        rb_node_s *new_node = malloc(sizeof(rb_node_s));

        new_node->obj = malloc(sizeof(rb->element_size));
        memcpy(new_node->obj, obj, rb->element_size);
        new_node->parent = NULL;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->color = RED;
        insert_helper(rb, &rb->root, new_node);
        rb->size += 1;
    }

    return valid;
}

int red_black_tree__delete(rb_s *rb, const void *obj)
{
    int valid = rb && rb->root && rb->compare_function && obj;

    if (valid)
        delete_helper(rb, &rb->root, obj);
    
    return valid;
}

int red_black_tree__min(rb_s *rb, rb_node_s *min)
{
    int valid = rb && rb->root && rb->compare_function && min;

    if (valid)
        min = min_helper(rb->root);
    
    return valid;
}

int red_black_tree__max(rb_s *rb, rb_node_s *max)
{
    int valid = rb && rb->root && rb->compare_function && max;

    if (valid)
        max = max_helper(rb->root);
    
    return valid;
}

int red_black_tree__find(rb_s *rb, const void *obj, rb_node_s *node)
{
    int valid = rb && rb->compare_function && obj && node;

    if (valid)
        node = find_helper(rb, rb->root, obj);

    return valid;
}


/**
 * Private functions definitions
 */
static rb_node_s *left_rotate(rb_node_s **root, rb_node_s *pivot)
{
    rb_node_s *new_pivot = pivot->right;

    pivot->right = new_pivot->left;
    if (pivot->right) pivot->right->parent = pivot;
    
    new_pivot->parent = pivot->parent;
    
    if (!new_pivot->parent)
        *root = new_pivot;
    else if (new_pivot->parent->left == pivot)
        new_pivot->parent->left = new_pivot;
    else
        new_pivot->parent->right = new_pivot;

    new_pivot->left = pivot;
    pivot->parent = new_pivot;

    return new_pivot;
}

static rb_node_s *right_rotate(rb_node_s **root, rb_node_s *pivot)
{
    rb_node_s *new_pivot = pivot->left;

    pivot->left = new_pivot->right;
    if (pivot->left) pivot->left->parent = pivot;
    
    new_pivot->parent = pivot->parent;
    
    if (!new_pivot->parent)
        *root = new_pivot;
    else if (new_pivot->parent->left == pivot)
        new_pivot->parent->left = new_pivot;
    else
        new_pivot->parent->right = new_pivot;

    new_pivot->right = pivot;
    pivot->parent = new_pivot;

    return new_pivot;
}

/**
 * Recolors and balances nodes after insertion in the case
 * the newly inserted node has a parent colored red.
 * 
 * @param  root: reference pointer to the root of the tree
 * @param  node: pointer to the starting node
 */
static void insert_fixup(rb_node_s **root, rb_node_s *node)
{
    while (node->parent && node->parent->color == RED) {

        rb_node_s *grandparent = node->parent->parent;

        if (grandparent->left == node->parent) {

            rb_node_s *parents_sibling = grandparent->right;

            if (parents_sibling && parents_sibling->color == RED) {

                node->parent->color = BLACK;
                parents_sibling->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            
            } else {

                if (node->parent->right == node) {
                    node = node->parent;
                    left_rotate(root, node);
                }

                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                right_rotate(root, node->parent->parent);
            }
        
        } else {

            rb_node_s *parents_sibling = grandparent->left;

            if (parents_sibling && parents_sibling->color == RED) {

                node->parent->color = BLACK;
                parents_sibling->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            
            } else {

                if (node->parent->left == node) {
                    node = node->parent;
                    right_rotate(root, node);
                }

                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                left_rotate(root, node->parent->parent);
            }
        }
    }

    (*root)->color = BLACK;
}

/**
 * Recolors and balances nodes after deletion.
 * 
 * @param  root: reference pointer to the root of the tree
 * @param  node: pointer to the starting node
 */
static void delete_fixup(rb_node_s **root, rb_node_s *node)
{
    while (node && node != *root && node->color == BLACK) {

        if (node->parent->left == node) {

            rb_node_s *sibling = node->parent->right;

            if (sibling) {

                if (sibling->color == RED) {
                    
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    left_rotate(root, node->parent);
                    sibling = node->parent->right;
                }

                if ( (!sibling->left || sibling->left->color == BLACK)
                    && (!sibling->right || sibling->right->color == BLACK) ) {

                    sibling->color = RED;
                    node = node->parent;
                
                } else {

                    if (!sibling->right || sibling->right->color == BLACK) {

                        sibling->left->color = BLACK;
                        sibling->color = RED;
                        right_rotate(root, sibling);
                        sibling = node->parent->right;
                    }

                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    sibling->right->color = BLACK;
                    left_rotate(root, node->parent);
                    node = *root;
                }
            }
        
        } else {

            rb_node_s *sibling = node->parent->left;

            if (sibling) {

                if (sibling->color == RED) {
                    
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    right_rotate(root, node->parent);
                    sibling = node->parent->left;
                }

                if ( (!sibling->left || sibling->left->color == BLACK) 
                    && (!sibling->right || sibling->right->color == BLACK) ) {

                    sibling->color = RED;
                    node = node->parent;
                
                } else {

                    if (!sibling->left || sibling->left->color == BLACK) {

                        sibling->right->color = BLACK;
                        sibling->color = RED;
                        left_rotate(root, sibling);
                        sibling = node->parent->left;
                    }

                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    sibling->left->color = BLACK;
                    right_rotate(root, node->parent);
                    node = *root;
                }
            }
        }
    }

    node->color = BLACK;
}

/**
 * @param  root: reference pointer to the root of the tree
 * @param  old_node: pointer to the node to be transplanted
 * @param  new_node: pointer to the node to transplant with
 */
static void transplant(rb_node_s **root, const rb_node_s *old_node, rb_node_s *new_node)
{
    if (*root && old_node) {

        if (old_node->parent == NULL)
            *root = new_node;
        else if (old_node->parent->left == old_node)
            old_node->parent->left = new_node;
        else
            old_node->parent->right = new_node;

        if (new_node)
            new_node->parent = old_node->parent;
    }
}

static void insert_helper(rb_s *rb, rb_node_s **root, rb_node_s *new_node)
{
    rb_node_s *cur, *parent;

    if (!(*root)) {
        *root = new_node;
        (*root)->color = BLACK;

    } else {

        cur = *root;

        while (cur) {

            parent = cur;

            if (rb->compare_function(new_node->obj, cur->obj) < 0)
                cur = cur->left;
            else
                cur = cur->right;
        }

        new_node->parent = parent;

        if (rb->compare_function(new_node->obj, parent->obj) < 0)
            parent->left = new_node;
        else
            parent->right = new_node;
    }

    insert_fixup(root, new_node);
}

static void delete_helper(rb_s *rb, rb_node_s **root, const void *obj)
{
    if (*root) {

        rb_node_s *node_to_delete = *root;

        /* search for a matching node */
        while (node_to_delete && rb->compare_function(obj, node_to_delete->obj)) {
            if (rb->compare_function(obj, node_to_delete->obj) < 0)
                node_to_delete = node_to_delete->left;
            else
                node_to_delete = node_to_delete->right;
        }

        if (node_to_delete) {

            rb_node_color_e original_color = node_to_delete->color;
            rb_node_s *fixup_node;
            int free_mem_flag = 0;

            if ( !node_to_delete->left ) {
                
                fixup_node = node_to_delete->right;
                if (!fixup_node) {
                    fixup_node = malloc(sizeof(rb_node_s));
                    fixup_node->color = BLACK;
                    fixup_node->parent = node_to_delete;
                    fixup_node->left = NULL;
                    fixup_node->right = NULL;
                    node_to_delete->right = fixup_node;
                    free_mem_flag = 1;
                }
                transplant(root, node_to_delete, node_to_delete->right);
            
            } else if ( !node_to_delete->right ) {
                
                fixup_node = node_to_delete->left;
                if (!fixup_node) {
                    fixup_node = malloc(sizeof(rb_node_s));
                    fixup_node->color = BLACK;
                    fixup_node->parent = node_to_delete;
                    fixup_node->left = NULL;
                    fixup_node->right = NULL;
                    node_to_delete->left = fixup_node;
                    free_mem_flag = 1;
                }
                transplant(root, node_to_delete, node_to_delete->left);
            
            } else {

                rb_node_s *predecessor = max_helper(node_to_delete->left);
                
                original_color = predecessor->color;
                fixup_node = predecessor->left;
                if (!fixup_node) {
                    fixup_node = malloc(sizeof(rb_node_s));
                    fixup_node->color = BLACK;
                    fixup_node->parent = predecessor;
                    fixup_node->left = NULL;
                    fixup_node->right = NULL;
                    predecessor->left = fixup_node;
                    free_mem_flag = 1;
                }

                if (predecessor->parent != node_to_delete) {
                    transplant(root, predecessor, predecessor->left);
                    predecessor->left = node_to_delete->left;
                    predecessor->left->parent = predecessor;
                }

                transplant(root, node_to_delete, predecessor);
                predecessor->right = node_to_delete->right;
                if (predecessor->right)
                    predecessor->right->parent = predecessor;
                predecessor->color = node_to_delete->color;
            }

            free(node_to_delete);
            rb->size -= 1;

            if (original_color == BLACK)
                delete_fixup(root, fixup_node);

            if (free_mem_flag) {
                
                if (!fixup_node->parent)
                    *root = NULL;
                else if (fixup_node->parent->left == fixup_node)
                    fixup_node->parent->left = NULL;
                else
                    fixup_node->parent->right = NULL;
                
                free(fixup_node);
            }
        }
    }
}

static rb_node_s *min_helper(rb_node_s *node)
{
    if (node) while (node->left) node = node->left;

    return node;
}

static rb_node_s *max_helper(rb_node_s *node)
{
    if (node) while (node->right) node = node->right;

    return node;
}

static rb_node_s *find_helper(rb_s *rb, rb_node_s *root, const void *obj)
{
    int valid_and_not_found = root && rb->compare_function(obj, root->obj);

    if (valid_and_not_found) {

        if (rb->compare_function(obj, root->obj) < 0)
            root = find_helper(rb, root->left, obj);
        else
            root = find_helper(rb, root->right, obj);
    }

    return root;
}
