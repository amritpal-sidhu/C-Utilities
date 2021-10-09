#include <stdio.h>
#include <stdlib.h>

#include "red_black_tree.h"


enum {
    RED,
    BLACK
};

/**
 * Private helper functions
 */

/**
 * Return a pointer to the minimum valued node from the
 * provided node.
 * 
 * @param  node: pointer to starting node
 * @retval Pointer to the minimum valued node
 */
static rb_node_t *min_value_node(rb_node_t *node) {

    if (node) while (node->left) node = node->left;

    return node;
}

/**
 * Return a pointer to the maximum valued node from the
 * provided node.
 * 
 * @param  node: pointer to starting node
 * @retval Pointer to the maximum valued node
 */
static rb_node_t *max_value_node(rb_node_t *node) {

    if (node) while (node->right) node = node->right;

    return node;
}

/**
 * @param  node: pointer to starting node
 * @retval Pointer to the successor node
 */
static rb_node_t *successor(rb_node_t *node) {

    rb_node_t *successor;

    if (node->right)
        successor = min_value_node(node->right);
    else {

        successor = node->parent;

        while (successor && successor->right == node) {
            node = successor;
            successor = node->parent;
        }
    }

    return successor;
}

/**
 * @param  node: pointer to starting node
 * @retval Pointer to the predecessor node
 */
static rb_node_t *predecessor(rb_node_t *node) {
    
    rb_node_t *predecessor;

    if (node->left)
        predecessor = max_value_node(node->left);
    else {

        predecessor = node->parent;

        while (predecessor && predecessor->left == node) {
            node = predecessor;
            predecessor = node->parent;
        }
    }

    return predecessor;
}

/**
 * @param  root: reference to a pointer to the root of the tree
 * @param  pivot: pointer to the starting pivot node
 * @retval Pointer to the ending pivot node
 */
static rb_node_t *left_rotate(rb_node_t **root, rb_node_t *pivot) {

    rb_node_t *pivot_child = pivot->right;

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
 * @param  root: reference to a pointer to the root of the tree
 * @param  pivot: pointer to the starting pivot node
 * @retval Pointer to the ending pivot node
 */
static rb_node_t *right_rotate(rb_node_t **root, rb_node_t *pivot) {

    rb_node_t *pivot_child = pivot->left;

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
 * Recolors and balances nodes after insertion.
 * 
 * @param  root: reference to a pointer to the root of the tree
 * @param  node: pointer to the starting node
 */
static void insert_fixup(rb_node_t **root, rb_node_t *node) {

    while (node->parent && node->parent->color == RED) {

        rb_node_t *grandparent = node->parent->parent;

        if (grandparent->left == node->parent) {

            rb_node_t *aunt = grandparent->right;

            if (aunt && aunt->color == RED) {

                node->parent->color = BLACK;
                aunt->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            }
            else {

                if (node->parent->right == node) {
                    node = node->parent;
                    left_rotate(root, node);
                }

                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                right_rotate(root, node->parent->parent);
            }
        }
        else {

            rb_node_t *aunt = grandparent->left;

            if (aunt && aunt->color == RED) {

                node->parent->color = BLACK;
                aunt->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            }
            else {

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
 * @param  root: reference to a pointer to the root of the tree
 * @param  node: pointer to the starting node
 */
static void delete_fixup(rb_node_t **root, rb_node_t *node) {
    
}

/**
 * Public function definitions
 */
rb_node_t *red_black_tree__insert(rb_node_t *root, const int val) {

    rb_node_t *new_node = malloc(sizeof(rb_node_t));
    rb_node_t *cur, *parent;

    new_node->val = val;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->color = RED;

    if (!root) {
        root = new_node;
        root->color = BLACK;
    }
    else {

        cur = root;

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

    insert_fixup(&root, new_node);

    return root;
}

rb_node_t *red_black_tree__delete(rb_node_t *root, const int val) {

    if (root) {

        if (val < root->val)
            root->left = red_black_tree__delete(root->left, val);

        else if (val > root->val)
            root->right = red_black_tree__delete(root->right, val);

        else {

            rb_node_t *node_to_delete = root;

            if ( !node_to_delete->left && !node_to_delete->right ) {
                root = NULL;
                free(node_to_delete);
            }
            else if ( !node_to_delete->left ) {
                root = node_to_delete->right;
                free(node_to_delete);
            }
            else if ( !node_to_delete->right ) {
                root = node_to_delete->left;
                free(node_to_delete);
            }
            else {
                /* Replace with successor approach */
                // node_to_delete = min_value_node(root->right);
                // root->val = node_to_delete->val;
                // root->right = red_black_tree__delete(root->right, root->val);

                /* Replace with predecessor approach */
                node_to_delete = max_value_node(root->left);
                root->val = node_to_delete->val;
                root->left = red_black_tree__delete(root->left, root->val);
            }
        }
    }

    return root;
}

rb_node_t *red_black_tree__find(rb_node_t *root, const int val) {

    if (root && root->val != val) {

        if (val < root->val)
            root = red_black_tree__find(root->left, val);
        else
            root = red_black_tree__find(root->right, val);
    }

    return root;
}

void red_black_tree__print(const rb_node_t *root) {

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
