#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binary_search_tree.h"


/**
 * Private function declarations
 */
static void insert_helper(bst_t *bst, bst_node_t *node, const void *obj);
static bst_node_t *delete_helper(bst_t *bst, bst_node_t *node, const void *obj);
static bst_node_t *min_helper(bst_node_t *node);
static bst_node_t *max_helper(bst_node_t *node);
static bst_node_t *find_helper(bst_t *bst, bst_node_t *node, const void *obj);

/**
 * Public function definitions
 */
int binary_search_tree__init(bst_t *bst, const unsigned int element_size, compare_function_t cmp_f)
{
    int valid = bst && !bst->size && element_size && cmp_f;

    if (valid) {

        /**
         * TODO: Might need to recursivly delete previously allocated nodes
         *       in the case of compiler using the same address.
         */
        bst->root = NULL;
        bst->element_size = element_size;
        bst->cmp_f = cmp_f;
        bst->size = 0;
    }

    return valid;
}

int binary_search_tree__insert(bst_t *bst, const void *obj)
{
    int valid = bst && bst->element_size && bst->cmp_f && obj;

    if (valid)
        insert_helper(bst, bst->root, obj);

    return valid;
}

int binary_search_tree__delete(bst_t *bst, const void *obj)
{
    int valid = bst && bst->root && bst->cmp_f && obj;

    if (valid)
        bst->root = delete_helper(bst, bst->root, obj);

    return valid;
}

int binary_search_tree__min(bst_t *bst, bst_node_t *min)
{
    int valid = bst && bst->root && bst->cmp_f && min;

    if (valid)
        min = min_helper(bst->root);

    return valid;
}

int binary_search_tree__max(bst_t *bst, bst_node_t *max)
{
    int valid = bst && bst->root && bst->cmp_f && max;

    if (valid)
        max = max_helper(bst->root);

    return valid;
}

int binary_search_tree__find(bst_t *bst, const void *obj, bst_node_t *node)
{
    int valid = bst && bst->cmp_f && obj && node;

    if (valid)
        node = find_helper(bst, bst->root, obj);

    return valid;
}


/**
 * Private function definitions
 */
static void insert_helper(bst_t *bst, bst_node_t *node, const void *obj)
{
    bst_node_t *new_node = malloc(sizeof(bst_node_t));
    bst_node_t *cur, *parent;

    new_node->obj = malloc(sizeof(bst->element_size));
    memcpy(new_node->obj, obj, bst->element_size);
    new_node->left = NULL;
    new_node->right = NULL;

    if (!bst->root) {
        bst->root = new_node;
    
    } else {

        cur = bst->root;

        while (cur) {

            parent = cur;

            if (bst->cmp_f(obj, cur->obj) < 0)
                cur = cur->left;
            else
                cur = cur->right;
        }

        if (bst->cmp_f(obj, parent->obj) < 0)
            parent->left = new_node;
        else
            parent->right = new_node;
    }

    bst->size += 1;
}

static bst_node_t *delete_helper(bst_t *bst, bst_node_t *node, const void *obj)
{
    if (node) {

        if (bst->cmp_f(obj, node->obj) < 0)
            node->left = delete_helper(bst, node->left, obj);

        else if (bst->cmp_f(obj, node->obj) > 0)
            node->right = delete_helper(bst, node->right, obj);

        else {

            bst_node_t *node_to_delete = node;

            if ( !node_to_delete->left && !node_to_delete->right ) {
                node = NULL;
                free(node_to_delete->obj);
                free(node_to_delete);
                bst->size -= 1;
            
            } else if ( !node_to_delete->left ) {
                node = node_to_delete->right;
                free(node_to_delete->obj);
                free(node_to_delete);
                bst->size -= 1;
            
            } else if ( !node_to_delete->right ) {
                node = node_to_delete->left;
                free(node_to_delete->obj);
                free(node_to_delete);
                bst->size -= 1;
            
            } else {
                /* Replace with successor approach */
                // node_to_delete = min_helper(node->right);
                // node->obj = node_to_delete->obj;
                // node->right = delete_helper(node->right, node->obj);

                /* Replace with predecessor approach */
                node_to_delete = max_helper(node->left);
                memcpy(node->obj, node_to_delete->obj, bst->element_size);
                node->left = delete_helper(bst, node->left, node->obj);
            }
        }
    }

    return node;
}

static bst_node_t *min_helper(bst_node_t *node)
{
    if (node) while (node->left) node = node->left;

    return node; 
}

static bst_node_t *max_helper(bst_node_t *node)
{
    if (node) while (node->right) node = node->right;

    return node;   
}

static bst_node_t *find_helper(bst_t *bst, bst_node_t *node, const void *obj)
{
    int valid_and_not_found = node && bst->cmp_f(obj, node->obj);

    if (valid_and_not_found) {

        if (bst->cmp_f(obj, node->obj) < 0)
            node = find_helper(bst, node->left, obj);
        else
            node = find_helper(bst, node->right, obj);
    }

    return node;
}
