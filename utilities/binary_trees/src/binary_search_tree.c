#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binary_search_tree.h"


/**
 * Private function declarations
 */
static void binary_search_tree__insert_helper(bst_s *bst, bst_node_s *node, const void *obj);
static bst_node_s *binary_search_tree__delete_helper(bst_s *bst, bst_node_s *node, const void *obj);
static bst_node_s *binary_search_tree__min_helper(bst_node_s *node);
static bst_node_s *binary_search_tree__max_helper(bst_node_s *node);
static bst_node_s *binary_search_tree__find_helper(bst_s *bst, bst_node_s *node, const void *obj);

/**
 * Public function definitions
 */
int binary_search_tree__init(bst_s *bst, const unsigned int element_size, compare_function_t compare_function)
{
    int retval = 0;

    if (bst && !bst->size && element_size && compare_function) {

        bst->root = NULL;
        bst->element_size = element_size;
        bst->compare_function = compare_function;
        bst->size = 0;

        retval = 1;
    }

    return retval;
}

int binary_search_tree__insert(bst_s *bst, const void *obj)
{
    int retval = 0;

    if (bst && bst->element_size && bst->compare_function) {

        binary_search_tree__insert_helper(bst, bst->root, obj);
        retval = 1;
    }

    return retval;
}

int binary_search_tree__delete(bst_s *bst, const void *obj)
{
    int retval = 0;

    if (bst && bst->root && bst->compare_function) {

        bst->root = binary_search_tree__delete_helper(bst, bst->root, obj);
        retval = 1;
    }

    return retval;
}

int binary_search_tree__min(bst_s *bst, bst_node_s *min)
{
    int retval = 0;

    if (bst && bst->root && bst->compare_function) {
     
        min = binary_search_tree__min_helper(bst->root);
        retval = 1;
    }

    return retval;
}

int binary_search_tree__max(bst_s *bst, bst_node_s *max)
{
    int retval = 0;

    if (bst && bst->root && bst->compare_function) {
     
        max = binary_search_tree__max_helper(bst->root);
        retval = 1;
    }

    return retval;
}

int binary_search_tree__find(bst_s *bst, const void *obj, bst_node_s *node)
{
    int retval = 0;

    if (bst && bst->root && bst->compare_function && obj) {

        node = binary_search_tree__find_helper(bst, bst->root, obj);
        if (node) retval = 1;
    }

    return retval;
}


/**
 * Private function definitions
 */
static void binary_search_tree__insert_helper(bst_s *bst, bst_node_s *node, const void *obj)
{
    bst_node_s *new_node = malloc(sizeof(bst_node_s));
    bst_node_s *cur, *parent;

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

            if (bst->compare_function(obj, cur->obj) < 0)
                cur = cur->left;
            else
                cur = cur->right;
        }

        if (bst->compare_function(obj, parent->obj) < 0)
            parent->left = new_node;
        else
            parent->right = new_node;
    }

    bst->size += 1;
}

static bst_node_s *binary_search_tree__delete_helper(bst_s *bst, bst_node_s *node, const void *obj)
{
    if (node) {

        if (bst->compare_function(obj, node->obj) < 0)
            node->left = binary_search_tree__delete_helper(bst, node->left, obj);

        else if (bst->compare_function(obj, node->obj) > 0)
            node->right = binary_search_tree__delete_helper(bst, node->right, obj);

        else {

            bst_node_s *node_to_delete = node;

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
                // node_to_delete = binary_search_tree__min_helper(node->right);
                // node->obj = node_to_delete->obj;
                // node->right = binary_search_tree__delete_helper(node->right, node->obj);

                /* Replace with predecessor approach */
                node_to_delete = binary_search_tree__max_helper(node->left);
                memcpy(node->obj, node_to_delete->obj, bst->element_size);
                node->left = binary_search_tree__delete_helper(bst, node->left, node->obj);
            }
        }
    }

    return node;
}

static bst_node_s *binary_search_tree__min_helper(bst_node_s *node)
{
    if (node) while (node->left) node = node->left;

    return node; 
}

static bst_node_s *binary_search_tree__max_helper(bst_node_s *node)
{
    if (node) while (node->right) node = node->right;

    return node;   
}

static bst_node_s *binary_search_tree__find_helper(bst_s *bst, bst_node_s *node, const void *obj)
{
    if (node && bst->compare_function(obj, node->obj)) {

        if (bst->compare_function(obj, node->obj) < 0)
            node = binary_search_tree__find_helper(bst, node->left, obj);
        else
            node = binary_search_tree__find_helper(bst, node->right, obj);
    }

    return node;
}
