#include <stdio.h>
#include <stdlib.h>

#include "red_black_tree.h"


// static const rb_node_s nil = {

//     .val = 0,
//     .parent = NULL,
//     .left = NULL,
//     .right = NULL,
//     .color = BLACK
// };

/**
 * Private helper functions
 */

/**
 * @param  root: reference pointer to the root of the tree
 * @param  pivot: pointer to the starting pivot node
 * @retval Pointer to the ending pivot node
 */
static rb_node_s *left_rotate(rb_node_s **root, rb_node_s *pivot)
{

    rb_node_s *pivot_child = pivot->right;

    pivot->right = pivot_child->left;
    if (pivot->right) pivot->right->parent = pivot;
    
    pivot_child->parent = pivot->parent;
    
    if (!pivot_child->parent)
        *root = pivot_child;
    else if (pivot_child->parent->left == pivot)
        pivot_child->parent->left = pivot_child;
    else
        pivot_child->parent->right = pivot_child;

    pivot_child->left = pivot;
    pivot->parent = pivot_child;

    return pivot_child;
}

/**
 * @param  root: reference pointer to the root of the tree
 * @param  pivot: pointer to the starting pivot node
 * @retval Pointer to the ending pivot node
 */
static rb_node_s *right_rotate(rb_node_s **root, rb_node_s *pivot)
{

    rb_node_s *pivot_child = pivot->left;

    pivot->left = pivot_child->right;
    if (pivot->left) pivot->left->parent = pivot;
    
    pivot_child->parent = pivot->parent;
    
    if (!pivot_child->parent)
        *root = pivot_child;
    else if (pivot_child->parent->left == pivot)
        pivot_child->parent->left = pivot_child;
    else
        pivot_child->parent->right = pivot_child;

    pivot_child->right = pivot;
    pivot->parent = pivot_child;

    return pivot_child;
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

/**
 * Public function definitions
 */
int red_black_tree__insert(rb_node_s **root, const int val)
{

    int success = 1;
    rb_node_s *new_node = malloc(sizeof(rb_node_s));
    rb_node_s *cur, *parent;

    if (!new_node)
        success = 0;
    else {

        new_node->val = val;
        new_node->parent = NULL;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->color = RED;

        if (!(*root)) {
            *root = new_node;
            (*root)->color = BLACK;
        
        } else {

            cur = *root;

            while (cur) {

                parent = cur;

                if (val < cur->val)
                    cur = cur->left;
                else
                    cur = cur->right;
            }

            new_node->parent = parent;

            if (val < parent->val)
                parent->left = new_node;
            else
                parent->right = new_node;
        }

        insert_fixup(root, new_node);
    }

    return success;
}

int red_black_tree__delete(rb_node_s **root, const int val)
{

    int success = 0;

    if (*root) {

        rb_node_s *node_to_delete = *root;

        /* search for a matching node */
        while (node_to_delete && node_to_delete->val != val) {
            if (val < node_to_delete->val)
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

                rb_node_s *predecessor = red_black_tree__max(node_to_delete->left);
                
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
            success = 1;

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
    
    return success;
}

rb_node_s *red_black_tree__min(rb_node_s *node)
{

    if (node) while (node->left) node = node->left;

    return node;
}

rb_node_s *red_black_tree__max(rb_node_s *node)
{

    if (node) while (node->right) node = node->right;

    return node;
}

rb_node_s *red_black_tree__find(rb_node_s *root, const int val)
{

    if (root && root->val != val) {

        if (val < root->val)
            root = red_black_tree__find(root->left, val);
        else
            root = red_black_tree__find(root->right, val);
    }

    return root;
}

void red_black_tree__print(const rb_node_s *root)
{

    static int depth;

    if (root) {

        ++depth;

        red_black_tree__print(root->right);

        for (int i = 1; i < depth; ++i) printf("\t");
        printf("%i:%c\n", root->val, root->color == RED ? 'R' : 'B');

        red_black_tree__print(root->left);

        --depth;
    }
}
